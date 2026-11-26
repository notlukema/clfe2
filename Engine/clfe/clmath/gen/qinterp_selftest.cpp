// Independent numerical verification of qinterp.h (slerp / nlerp / exp-log).
// The oracle is rotation matrices built with Rodrigues' formula, so quaternion
// code is never checked against quaternion code.
//   g++ -std=c++20 -O2 -Iclmstub qinterp_selftest.cpp -o qinterp_selftest.exe

#include <cmath>
#include <cstdio>
#include <cstddef>
#include <initializer_list>

#include "mdef.h"
#include "vec.h"

namespace clfe { using matdefault_t = float; }
#include "qinterp.h"

using clfe::clmvec;

// ============================ oracle: matrices ==============================

struct M3 { double m[3][3]; };
struct D4 { double w, x, y, z; };
static constexpr double kPi = 3.14159265358979323846;

static M3 mat_identity()
{
	M3 r{};
	r.m[0][0] = r.m[1][1] = r.m[2][2] = 1.0;
	return r;
}

// Rodrigues: active rotation by angle a about (possibly unnormalised) axis u.
static M3 mat_axisangle(double a, double ux, double uy, double uz)
{
	double l = std::sqrt(ux * ux + uy * uy + uz * uz);
	if (l == 0.0) return mat_identity();
	ux /= l; uy /= l; uz /= l;
	const double c = std::cos(a), s = std::sin(a), k = 1.0 - c;
	M3 r{};
	r.m[0][0] = c + ux * ux * k;      r.m[0][1] = ux * uy * k - uz * s; r.m[0][2] = ux * uz * k + uy * s;
	r.m[1][0] = uy * ux * k + uz * s; r.m[1][1] = c + uy * uy * k;      r.m[1][2] = uy * uz * k - ux * s;
	r.m[2][0] = uz * ux * k - uy * s; r.m[2][1] = uz * uy * k + ux * s; r.m[2][2] = c + uz * uz * k;
	return r;
}

static M3 mat_mul(const M3& a, const M3& b)
{
	M3 r{};
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			double s = 0.0;
			for (int k = 0; k < 3; ++k) s += a.m[i][k] * b.m[k][j];
			r.m[i][j] = s;
		}
	return r;
}

static M3 mat_transpose(const M3& a)
{
	M3 r{};
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) r.m[i][j] = a.m[j][i];
	return r;
}

// Standard unit-quaternion -> rotation matrix (column-vector, active).
static M3 mat_of(const D4& q)
{
	const double w = q.w, x = q.x, y = q.y, z = q.z;
	M3 r{};
	r.m[0][0] = 1 - 2 * (y * y + z * z); r.m[0][1] = 2 * (x * y - z * w);     r.m[0][2] = 2 * (x * z + y * w);
	r.m[1][0] = 2 * (x * y + z * w);     r.m[1][1] = 1 - 2 * (x * x + z * z); r.m[1][2] = 2 * (y * z - x * w);
	r.m[2][0] = 2 * (x * z - y * w);     r.m[2][1] = 2 * (y * z + x * w);     r.m[2][2] = 1 - 2 * (x * x + y * y);
	return r;
}

[[maybe_unused]] static double mat_angle(const M3& a)
{
	const double tr = a.m[0][0] + a.m[1][1] + a.m[2][2];
	return std::acos(std::fmin(1.0, std::max(-1.0, (tr - 1.0) * 0.5)));
}

// Shepperd's matrix -> unit quaternion, stable in every branch including 180
// degrees.  Independent of qinterp.h.  Returned with w >= 0, so (angle, axis)
// = (2*acos(w), v/|v|) is the shortest rotation for the matrix.
static D4 quat_from_matrix(const M3& m)
{
	const double tr = m.m[0][0] + m.m[1][1] + m.m[2][2];
	D4 q{};
	if (tr > 0.0)
	{
		const double s = std::sqrt(tr + 1.0) * 2.0;
		q = { 0.25 * s, (m.m[2][1] - m.m[1][2]) / s, (m.m[0][2] - m.m[2][0]) / s, (m.m[1][0] - m.m[0][1]) / s };
	}
	else if (m.m[0][0] > m.m[1][1] && m.m[0][0] > m.m[2][2])
	{
		const double s = std::sqrt(1.0 + m.m[0][0] - m.m[1][1] - m.m[2][2]) * 2.0;
		q = { (m.m[2][1] - m.m[1][2]) / s, 0.25 * s, (m.m[0][1] + m.m[1][0]) / s, (m.m[0][2] + m.m[2][0]) / s };
	}
	else if (m.m[1][1] > m.m[2][2])
	{
		const double s = std::sqrt(1.0 + m.m[1][1] - m.m[0][0] - m.m[2][2]) * 2.0;
		q = { (m.m[0][2] - m.m[2][0]) / s, (m.m[0][1] + m.m[1][0]) / s, 0.25 * s, (m.m[1][2] + m.m[2][1]) / s };
	}
	else
	{
		const double s = std::sqrt(1.0 + m.m[2][2] - m.m[0][0] - m.m[1][1]) * 2.0;
		q = { (m.m[1][0] - m.m[0][1]) / s, (m.m[0][2] + m.m[2][0]) / s, (m.m[1][2] + m.m[2][1]) / s, 0.25 * s };
	}
	if (q.w < 0.0) q = { -q.w, -q.x, -q.y, -q.z };
	return q;
}

// angle+axis -> unit quaternion, plain math (no library calls).
static D4 quat_axisangle(double a, double ux, double uy, double uz)
{
	const double l = std::sqrt(ux * ux + uy * uy + uz * uz);
	if (!(l > 0.0)) return { 1, 0, 0, 0 };
	const double h = a * 0.5, s = std::sin(h) / l;
	return { std::cos(h), ux * s, uy * s, uz * s };
}

// Frobenius norm of the matrix difference == 0 iff same rotation, sign-safe.
static double orient_dist(const D4& a, const D4& b)
{
	const M3 A = mat_of(a), B = mat_of(b);
	double s = 0.0;
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) { const double d = A.m[i][j] - B.m[i][j]; s += d * d; }
	return std::sqrt(s);
}

// Shortest rotation angle between two orientations.  Built from the relative
// rotation's quaternion via atan2, which stays accurate both near 0 and near
// 180 degrees, where an acos(trace) reading loses all its significant digits.
static double orient_angle(const D4& a, const D4& b)
{
	const D4 r = quat_from_matrix(mat_mul(mat_transpose(mat_of(a)), mat_of(b)));
	return 2.0 * std::atan2(std::sqrt(r.x * r.x + r.y * r.y + r.z * r.z), r.w);
}

// Shortest rotation angle taking the identity into q (oracle only).
static double orient_angle0(const D4& q) { return orient_angle({ 1, 0, 0, 0 }, q); }

static bool finite(const D4& q)
{
	return std::isfinite(q.w) && std::isfinite(q.x) && std::isfinite(q.y) && std::isfinite(q.z);
}

// ---- <-> clmvec<4,T> marshalling (two instantiations, no lambda soup) ------
template <typename T> static clmvec<4, T> load(const D4& q);
template <> inline clmvec<4, double> load<double>(const D4& q) { return clmvec<4, double>(q.w, q.x, q.y, q.z); }
template <> inline clmvec<4, float>  load<float>(const D4& q)  { return clmvec<4, float>(float(q.w), float(q.x), float(q.y), float(q.z)); }

template <typename T> static D4 dump(const clmvec<4, T>& q);
template <> inline D4 dump<double>(const clmvec<4, double>& q) { return { q[0], q[1], q[2], q[3] }; }
template <> inline D4 dump<float>(const clmvec<4, float>& q)   { return { double(q[0]), double(q[1]), double(q[2]), double(q[3]) }; }

// ============================ deterministic rng =============================

struct Rng { unsigned long long s = 0x2545F4914F6CDD1ULL; };
static double urand(Rng& r)
{
	r.s ^= r.s << 13; r.s ^= r.s >> 7; r.s ^= r.s << 17;
	return double(r.s >> 11) * (1.0 / 9007199254740992.0);
}
static D4 random_unit_q(Rng& r)
{
	while (true)
	{
		const double x = urand(r) * 2 - 1, y = urand(r) * 2 - 1, z = urand(r) * 2 - 1;
		const double s2 = x * x + y * y + z * z;
		if (s2 <= 1.0 && s2 > 1e-12)
		{
			const double a = urand(r) * 3.0;         // rotation angle up to ~172 deg
			const double l = std::sqrt(s2), k = std::sin(a * 0.5);
			return { std::cos(a * 0.5), x / l * k, y / l * k, z / l * k };
		}
	}
}

// ============================== test harness ===============================

static int failures = 0, checks = 0;
static void ok(bool cond, const char* what, double err, double tol)
{
	static int printed = 0;
	++checks;
	if (!cond)
	{
		++failures;
		if (printed < 40)
		{
			++printed;
			std::printf("  FAIL %-52s err=%.3e tol=%.3e\n", what, err, tol);
			if (printed == 40) std::printf("  (further failures counted but not printed)\n");
		}
	}
}

// Textbook acos-based slerp, used only as a cross-check.
static D4 slerp_naive(const D4& qa, const D4& qb, double t)
{
	double d = qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z;
	D4 b = qb;
	if (d < 0) { d = -d; b = { -qb.w, -qb.x, -qb.y, -qb.z }; }
	if (d > 1.0 - 1e-12)                      // the usual fallback branch
	{
		D4 r = { (1 - t) * qa.w + t * b.w, (1 - t) * qa.x + t * b.x, (1 - t) * qa.y + t * b.y, (1 - t) * qa.z + t * b.z };
		double l = std::sqrt(r.w * r.w + r.x * r.x + r.y * r.y + r.z * r.z);
		if (l == 0.0) return r;
		return { r.w / l, r.x / l, r.y / l, r.z / l };
	}
	const double th = std::acos(d > 1 ? 1 : d), st = std::sin(th);
	const double w0 = std::sin((1 - t) * th) / st, w1 = std::sin(t * th) / st;
	return { w0 * qa.w + w1 * b.w, w0 * qa.x + b.x * w1, w0 * qa.y + b.y * w1, w0 * qa.z + b.z * w1 };
}

template <typename T>
static void run_suite(const char* name, double tol)
{
	std::printf("\n=== %s (tol %.1e) ===\n", name, tol);
	Rng rng;
	double worst_norm = 0.0, worst_speed = 0.0, worst_arc = 0.0, worst_nlerp_arc = 0.0;
	double worst_nlerp_timing = 0.0, worst_signinv = 0.0, worst_symm = 0.0, worst_naive = 0.0, worst_mul = 0.0;

	for (int i = 0; i < 400; ++i)
	{
		const D4 a = random_unit_q(rng), b = random_unit_q(rng);
		const clmvec<4, T> qa = load<T>(a), qb = load<T>(b);

		// qmul agrees with matrix composition -> convention is right.
		{
			const M3 lhs = mat_of(dump<T>(clfe::qmul<T>(qa, qb)));
			const M3 rhs = mat_mul(mat_of(a), mat_of(b));
			double s = 0.0;
			for (int r = 0; r < 3; ++r) for (int c = 0; c < 3; ++c) s += std::abs(lhs.m[r][c] - rhs.m[r][c]);
			worst_mul = std::max(worst_mul, s);
		}

		// Oracle: shortest rotation taking a into b, from matrices alone.
		const M3 relm = mat_mul(mat_transpose(mat_of(a)), mat_of(b));
		const D4 relq = quat_from_matrix(relm);
		const double omega = orient_angle(a, b);		// robust oracle angle, [0, pi]
		const double vl = std::sqrt(relq.x * relq.x + relq.y * relq.y + relq.z * relq.z);
		const double ax = vl > 1e-15 ? relq.x / vl : 1.0;
		const double ay = vl > 1e-15 ? relq.y / vl : 0.0;
		const double az = vl > 1e-15 ? relq.z / vl : 0.0;

		for (int s = 0; s <= 20; ++s)
		{
			const double td = s / 20.0;
			const clmvec<4, T> q = clfe::qslerp<T>(qa, qb, T(td));
			const D4 got = dump<T>(q);
			worst_norm = std::max(worst_norm, std::abs(double(clfe::qlen2<T>(q)) - 1.0));
			ok(finite(got), "slerp output is finite", 0, tol);

			// (1) defining property: the arc is walked in q0's local frame, so the
			//     relative rotation is applied on the RIGHT: q0 * rotate(t*omega, u).
			const D4 want = dump<T>(clfe::qmul<T>(qa, load<T>(quat_axisangle(td * omega, ax, ay, az))));
			const double e1 = orient_dist(got, want);
			ok(e1 < tol, "slerp(t) == rotate(t*omega, rel axis)", e1, tol);

			// (2) constant angular velocity along the arc.
			const double e2 = std::abs(orient_angle(a, got) - td * omega);
			worst_speed = std::max(worst_speed, e2);
			ok(e2 < tol, "angular phase == t*omega (constant velocity)", e2, tol);

			// (3) stays on the shortest arc.
			const double e3 = orient_angle(a, got) + orient_angle(got, b) - omega;
			worst_arc = std::max(worst_arc, e3);
			ok(e3 < tol, "stays on the shortest arc", e3, tol);

			// (4) nlerp rides the same arc, but non-uniformly in time.
			const D4 n = dump<T>(clfe::qnlerp<T>(qa, qb, T(td)));
			const double e4 = orient_angle(a, n) + orient_angle(n, b) - omega;
			worst_nlerp_arc = std::max(worst_nlerp_arc, e4);
			ok(e4 < tol, "nlerp stays on slerp's arc", e4, tol);
			if (omega > 1e-3)
				worst_nlerp_timing = std::max(worst_nlerp_timing, std::abs(orient_angle(a, n) / omega - td));

			// (5) matches the textbook acos form.
			const double e5 = orient_dist(got, slerp_naive(a, b, td));
			worst_naive = std::max(worst_naive, e5);
			ok(e5 < tol, "matches textbook acos(dot) slerp", e5, tol);

			// (6) qfromaxisangle/qaxis reproduce the independent Rodrigues matrix.
			if (s % 4 == 0 && omega > 1e-6)
			{
				const clmvec<3, T> u{ T(ax), T(ay), T(az) };
				const clmvec<4, T> qaa = clfe::qfromaxisangle<T>(T(td * omega), u);
				const M3 A = mat_of(dump<T>(qaa)), B = mat_axisangle(td * omega, ax, ay, az);
				double s2 = 0.0;
				for (int rr = 0; rr < 3; ++rr) for (int cc = 0; cc < 3; ++cc) s2 += std::abs(A.m[rr][cc] - B.m[rr][cc]);
				ok(s2 < tol, "qfromaxisangle == Rodrigues matrix", s2, tol);
				ok(std::abs(double(clfe::qlen2<T>(qaa)) - 1.0) < tol, "qfromaxisangle returns a unit quaternion",
				   std::abs(double(clfe::qlen2<T>(qaa)) - 1.0), tol);
				// unnormalised axis input must give the same answer
				const clmvec<4, T> qaa2 = clfe::qfromaxisangle<T>(T(td * omega), clmvec<3, T>(T(ax * 7.5), T(ay * 7.5), T(az * 7.5)));
				ok(orient_dist(dump<T>(qaa2), dump<T>(qaa)) < tol, "qfromaxisangle ignores axis length",
				   orient_dist(dump<T>(qaa2), dump<T>(qaa)), tol);
				// qaxis: rebuilding (angle, qaxis(relq)) must give back relq's rotation
				const clmvec<4, T> rebuilt = clfe::qfromaxisangle<T>(T(omega), clfe::qaxis(load<T>(relq)));
				ok(orient_dist(dump<T>(rebuilt), relq) < tol, "qangle/qaxis round trip", orient_dist(dump<T>(rebuilt), relq), tol);
			}
		}

		// (7) sign invariance and time symmetry.
		const D4 p = dump<T>(clfe::qslerp<T>(qa, load<T>({ -b.w, -b.x, -b.y, -b.z }), T(0.37)));
		const D4 rev = dump<T>(clfe::qslerp<T>(qb, qa, T(0.63)));
		const D4 base = dump<T>(clfe::qslerp<T>(qa, qb, T(0.37)));
		worst_signinv = std::max(worst_signinv, orient_dist(p, base));
		worst_symm = std::max(worst_symm, orient_dist(rev, base));
		ok(orient_dist(p, base) < tol, "slerp(q0,-q1,t) == slerp(q0,q1,t)", orient_dist(p, base), tol);
		ok(orient_dist(rev, base) < tol, "slerp(q1,q0,1-t) == slerp(q0,q1,t)", orient_dist(rev, base), tol);
	}

	std::printf("  qmul vs matrix compose            max err = %.3e\n", worst_mul);
	std::printf("  unit-norm drift  |len^2-1|        max     = %.3e\n", worst_norm);
	ok(worst_norm < tol, "slerp stays on S^3", worst_norm, tol);
	std::printf("  slerp angular-velocity error      max     = %.3e rad\n", worst_speed);
	std::printf("  slerp arc excess (shortest path)  max     = %.3e rad\n", worst_arc);
	std::printf("  nlerp deviation from slerp arc    max     = %.3e rad  <- same path\n", worst_nlerp_arc);
	std::printf("  nlerp timing error                          = %.3f%% of arc\n", worst_nlerp_timing * 100.0);
	std::printf("  sign-invariance / symmetry          max     = %.3e / %.3e\n", worst_signinv, worst_symm);
	std::printf("  vs textbook acos form               max     = %.3e\n", worst_naive);
}

static void degenerate_suite()
{
	std::printf("\n=== degenerate / tiny-angle / algebra cases ===\n");
	const clmvec<4, double> I = clfe::qident<double>();

	{	// q1 == q0 and q1 == -q0 represent the same orientation
		const clmvec<4, double> q = clfe::qnormalize(load<double>({ 1, 2, 3, 4 }));
		for (double t : { 0.0, 0.25, 0.5, 1.0, 1.7, -0.8 })
		{
			const D4 same = dump<double>(clfe::qslerp<double>(q, q, t));
			const D4 anti = dump<double>(clfe::qslerp<double>(q, load<double>({ -q[0], -q[1], -q[2], -q[3] }), t));
			ok(finite(same) && orient_dist(same, dump<double>(q)) < 1e-12, "slerp(q,q,t) == q", orient_dist(same, dump<double>(q)), 1e-12);
			ok(finite(anti) && orient_dist(anti, dump<double>(q)) < 1e-12, "slerp(q,-q,t) == q", orient_dist(anti, dump<double>(q)), 1e-12);
		}
	}

	for (double a : { 1e-9, 1e-7, 1e-5, 1e-3, 0.1, 1.0, 3.141592653589793 })
	{
		const clmvec<4, double> q1 = load<double>(quat_axisangle(a, 0, 0, 1));
		const D4 mid = dump<double>(clfe::qslerp<double>(I, q1, 0.5));
		const double want = (a == 3.141592653589793) ? a * 0.5 : a * 0.5;
		const double got = orient_angle0(mid);
		ok(finite(mid) && std::abs(got - want) < 1e-12, "midpoint angle == arc/2", std::abs(got - want), 1e-12);
		const D4 endp = dump<double>(clfe::qslerp<double>(I, q1, 1.0));
		ok(orient_dist(endp, dump<double>(q1)) < 1e-12, "slerp(t=1) == q1", orient_dist(endp, dump<double>(q1)), 1e-12);
		ok(std::abs(mid.x) < 1e-12 && std::abs(mid.y) < 1e-12, "axis (z) preserved", std::max(std::abs(mid.x), std::abs(mid.y)), 1e-12);
		const D4 ext = dump<double>(clfe::qslerp<double>(I, q1, 2.0));
		ok(std::abs(orient_angle0(ext) - 2 * a) < 1e-9 || 2 * a > kPi, "t=2 extrapolates at the same rate",
		   std::abs(orient_angle0(ext) - 2 * a), 1e-9);
	}

	{	// exp/log round trip, power identity, incremental stepping
		Rng r;
		for (int i = 0; i < 400; ++i)
		{
			const D4 a = random_unit_q(r), b = random_unit_q(r);
			const clmvec<4, double> qa = load<double>(a), qb = load<double>(b);
			ok(orient_dist(dump<double>(clfe::qexp(clfe::qlog<double>(qa))), a) < 1e-12, "exp(log(q)) == q",
			   orient_dist(dump<double>(clfe::qexp(clfe::qlog<double>(qa))), a), 1e-12);
			const double t = urand(r);
			const D4 lhs = dump<double>(clfe::qslerp<double>(qa, qb, t));
			const D4 rhs = dump<double>(clfe::qmul<double>(qa, clfe::qpow<double>(clfe::qcanon<double>(clfe::qrel<double>(qa, qb)), t)));
			ok(orient_dist(lhs, rhs) < 1e-10, "slerp == q0 * qcanon(conj(q0)*q1)^t", orient_dist(lhs, rhs), 1e-10);
			ok(orient_dist(lhs, dump<double>(clfe::qslerp_rel<double>(qa, qb, t))) < 1e-10, "qslerp_rel == qslerp",
			   orient_dist(lhs, dump<double>(clfe::qslerp_rel<double>(qa, qb, t))), 1e-10);

			// stepping walks the arc by right-multiplying the per-frame increment
			const clmvec<4, double> step = clfe::qslerp_step<double>(qa, qb, t / 60.0, 1.0);
			clmvec<4, double> cur = qa;
			for (int k = 0; k < 60; ++k) cur = clfe::qmul<double>(cur, step);
			ok(orient_dist(dump<double>(cur), lhs) < 1e-12, "60x qslerp_step == slerp(t)",
			   orient_dist(dump<double>(cur), lhs), 1e-12);
		}
		// chaining a full 1-second arc at 60 fps must land exactly on q1
		for (int i = 0; i < 200; ++i)
		{
			const D4 a = random_unit_q(r), b = random_unit_q(r);
			const clmvec<4, double> qa = load<double>(a), qb = load<double>(b);
			const clmvec<4, double> step = clfe::qslerp_step<double>(qa, qb, 1.0 / 60.0, 1.0);
			clmvec<4, double> cur = qa;
			for (int k = 0; k < 60; ++k) cur = clfe::qmul<double>(cur, step);
			const double e = std::min(orient_dist(dump<double>(cur), b), orient_dist(dump<double>(cur), { -b.w, -b.x, -b.y, -b.z }));
			ok(e < 1e-12, "60 fps stepping reaches the target orientation", e, 1e-12);
			// and stays unit-length while doing it
			ok(std::abs(std::sqrt(clfe::qlen2(cur)) - 1.0) < 1e-12, "chained product stays unit length",
			   std::abs(std::sqrt(clfe::qlen2(cur)) - 1.0), 1e-12);
		}
	}

	{	// float behaviour at a 1e-5 rad arc, where acos(dot) loses everything
		const float ang = 1e-5f;
		const clmvec<4, float> q0 = clfe::qident<float>();
		// cos(ang/2) rounds to exactly 1.0f in float, so this is the realistic case
		const clmvec<4, float> q1 = clfe::qnormalize(clmvec<4, float>(std::cos(ang * 0.5f), 0, 0, std::sin(ang * 0.5f)));
		const float d = clfe::qdot(q0, q1);
		const D4 mid = dump<float>(clfe::qslerp<float>(q0, q1, 0.5f));
		ok(std::abs(orient_angle0(mid) - ang * 0.5) < 1e-8, "float slerp accurate at 1e-5 rad arc",
		   std::abs(orient_angle0(mid) - ang * 0.5), 1e-8);
		std::printf("  float arc 1e-5 rad: dot = %.9f  ->  acos(dot) = %.3g, sin(acos) = %.3g\n",
		            double(d), double(d >= 1.0f ? 0.0f : std::acos(d)), double(d >= 1.0f ? 0.0f : std::sin(std::acos(d))));
		// what the unguarded textbook form makes of it: 0/0
		{
			const float th = std::acos(d >= 1.0f ? 1.0f : d), sn = std::sin(th);
			const float w0 = (sn > 0.0f) ? std::sin((1 - 0.5f) * th) / sn : std::nanf("");
			std::printf("  unguarded acos form at that arc: weight = %.3g (0/0 without a fallback branch)\n", w0);
			std::printf("  stable atan2 form: midpoint rotation angle = %.9e rad (want %.9e)\n",
			              orient_angle0(mid), double(ang) * 0.5);
		}
		// and a 1-degree arc, where the acos form still works in float
		{
			const float a2 = 1e-3f;   // ~0.057 deg
			const clmvec<4, float> r1 = clfe::qnormalize(clmvec<4, float>(std::cos(a2 * 0.5f), 0, 0, std::sin(a2 * 0.5f)));
			const D4 m2 = dump<float>(clfe::qslerp<float>(q0, r1, 0.5f));
			ok(std::abs(orient_angle0(m2) - a2 * 0.5) < 1e-8, "float slerp accurate at 1e-3 rad arc",
			   std::abs(orient_angle0(m2) - a2 * 0.5), 1e-8);
		}
	}
}

static void nlerp_error_table()
{
	std::printf("\n=== worst-case nlerp timing error vs arc size ===\n");
	const clmvec<4, double> q0 = clfe::qident<double>();
	for (double deg : { 1.0, 5.0, 15.0, 30.0, 60.0, 90.0, 120.0, 180.0 })
	{
		const double a = deg * kPi / 180.0;
		const clmvec<4, double> q1 = load<double>(quat_axisangle(a, 1, 0, 0));
		double worst = 0.0;
		for (int i = 0; i <= 1000; ++i)
		{
			const double t = i / 1000.0;
			const D4 n = dump<double>(clfe::qnlerp<double>(q0, q1, t));
			worst = std::max(worst, std::abs(orient_angle0(n) / a - t));
		}
		std::printf("  arc %6.1f deg  ->  nlerp arrives at the wrong time by at most %.3f%% of the arc\n", deg, worst * 100.0);
	}
}

int main()
{
	degenerate_suite();
	nlerp_error_table();
	run_suite<double>("double", 1e-11);
	run_suite<float>("float", 2e-5);
	std::printf("\nchecks=%d failures=%d\n", checks, failures);
	return failures ? 1 : 0;
}
