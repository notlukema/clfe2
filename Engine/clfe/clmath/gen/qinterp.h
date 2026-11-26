#ifndef CLFE_CLMATH_QINTERP_H
#define CLFE_CLMATH_QINTERP_H

#include "math.h"
#include "mdef.h"
#include "vec.h"

#include <limits>

// ---------------------------------------------------------------------------
// Unit quaternions: construction, composition and interpolation (slerp/nlerp).
//
// Storage: clmvec<4, T> with component 0 = w (scalar) and 1..3 = (x, y, z),
// i.e. q = ( cos(a/2), u * sin(a/2) ) for a rotation by angle a about the unit
// axis u.  Right-handed, active (v' = q v conj(q)), column-vector convention,
// same as the mrotate*/mrotate4* builders in matutils.h.
//
// If your project packs (x, y, z, w), only qident/qfromaxisangle/qconj/qmul/
// qaxis/qscalar read components by position -- adjust those and everything
// else keeps working.
//
// matdefault_t is expected from matutils.h.  Inputs are assumed to be unit
// (or within a few ulp of unit); nothing here normalises the endpoints.
// ---------------------------------------------------------------------------

namespace clfe
{
	// -- component helpers ----------------------------------------------------
	// Drop these if your clmvec already has element-wise +, -, * scalar.

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qadd(const clmvec<4, T>& a, const clmvec<4, T>& b)
	{
		return clmvec<4, T>(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qscale(const clmvec<4, T>& a, T s)
	{
		return clmvec<4, T>(a[0] * s, a[1] * s, a[2] * s, a[3] * s);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qneg(const clmvec<4, T>& a)
	{
		return qscale(a, T(-1));
	}

	// q and -q are the same rotation; this returns whichever representative has
	// a non-negative scalar part.  Feed it to qpow/qexp when you want the short
	// arc: (q1*conj(q0))^t follows whichever representative you hand it.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qcanon(const clmvec<4, T>& q)
	{
		return (q[0] < T(0)) ? qneg(q) : q;
	}

	// -- basics ---------------------------------------------------------------

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qident()
	{
		return clmvec<4, T>(T(1), T(0), T(0), T(0));
	}

	// q and -q are the SAME rotation (S^3 double-covers SO(3)), so the sign of
	// a quaternion carries no information.  qdot is the plain R^4 inner product.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline T qdot(const clmvec<4, T>& a, const clmvec<4, T>& b)
	{
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline T qlen2(const clmvec<4, T>& q)
	{
		return qdot(q, q);
	}

	// Returns the zero quaternion for zero input (no NaNs).
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qnormalize(const clmvec<4, T>& q)
	{
		const T l2 = qlen2(q);
		if (l2 <= T(0))
			return clmvec<4, T>(T(0), T(0), T(0), T(0));
		return qscale(q, T(1) / sqrt(l2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qconj(const clmvec<4, T>& q)
	{
		return clmvec<4, T>(q[0], -q[1], -q[2], -q[3]);
	}

	// Hamilton product.  With column vectors this composes right-to-left:
	// qmul(qa, qb) applies qb first, then qa.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qmul(const clmvec<4, T>& a, const clmvec<4, T>& b)
	{
		return clmvec<4, T>(
			a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3],
			a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2],
			a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1],
			a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0]
		);
	}

	// Rotation by `angle` radians about `axis`; the axis need not be normalised.
	// A zero-length axis or a zero angle yields the identity.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qfromaxisangle(T angle, const clmvec<3, T>& axis)
	{
		const T len2 = axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2];
		if (len2 <= T(0))
			return qident<T>();
		const T inv = T(1) / sqrt(len2);
		const T h = T(0.5) * angle;
		const T s = sin(h);
		return clmvec<4, T>(cos(h), axis[0] * inv * s, axis[1] * inv * s, axis[2] * inv * s);
	}

	// Rotation angle in [0, pi] of the orientation q represents (sign-agnostic).
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline T qangle(const clmvec<4, T>& q)
	{
		return T(2) * atan2(sqrt(q[1] * q[1] + q[2] * q[2] + q[3] * q[3]), fabs(q[0]));
	}

	// Unit rotation axis.  Degenerate for the identity; a 180 deg rotation keeps
	// its axis, so that case is fine.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<3, T> qaxis(const clmvec<4, T>& q)
	{
		const T len2 = q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
		if (len2 <= T(0))
			return clmvec<3, T>(T(0), T(0), T(0));
		const T inv = T(1) / sqrt(len2);
		return clmvec<3, T>(q[1] * inv, q[2] * inv, q[3] * inv);
	}

	// Relative rotation carrying q0 into q1:  qmul(qrel(q0,q1), q0) == q1.
	// Its scalar part is exactly qdot(q0, q1) for unit inputs.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qrel(const clmvec<4, T>& q0, const clmvec<4, T>& q1)
	{
		return qmul(qconj(q0), q1);
	}

	// Shortest-arc angle between two orientations, in [0, pi/2] (half of the
	// rotation angle), already accounting for q == -q.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline T qarclen(const clmvec<4, T>& q0, const clmvec<4, T>& q1)
	{
		const clmvec<4, T> r = qrel(q0, q1);
		const T w = (r[0] < T(0)) ? -r[0] : r[0];
		return atan2(sqrt(r[1] * r[1] + r[2] * r[2] + r[3] * r[3]), w);
	}

	// --------------------------------------------------------------------------
	// Interpolation.  t is NOT clamped: t = 0 -> q0, t = 1 -> q1, other values
	// extend along the same great circle at the same rate.
	// --------------------------------------------------------------------------

	// nlerp: linear blend along the chord, projected back onto S^3.  Travels
	// the very same arc as slerp, just not at constant angular velocity.
	// Cost: 1 dot, 4 mul + 4 add, 1 sqrt-ish normalise.  No transcendentals.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qnlerp(const clmvec<4, T>& q0, const clmvec<4, T>& q1, T t)
	{
		const clmvec<4, T> b = (qdot(q0, q1) < T(0)) ? qneg(q1) : q1;	// shortest arc
		return qnormalize(qadd(qscale(q0, T(1) - t), qscale(b, t)));
	}

	// slerp: spherical linear interpolation -- constant angular velocity along
	// the shortest great-circle arc.
	//
	// Derived from the relative rotation r = conj(q0) * q1 = (cos(th), u*sin(th)),
	// so th is the half-angle and sin(th) is read off the vector part instead of
	// via acos(1 - x).  That keeps it accurate down to angles of ~1e-7 rad, where
	// the textbook `acos(dot)` form loses every significant digit and needs an
	// nlerp fallback.  Cost: 1 qmul, 1 atan2, 1 sin, 1 cos, no acos.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qslerp(const clmvec<4, T>& q0, const clmvec<4, T>& q1, T t)
	{
		clmvec<4, T> r = qrel(q0, q1);
		clmvec<4, T> b = q1;
		if (r[0] < T(0))			// q1 and -q1 are the same orientation; take the
		{							// nearer representative so the arc stays <= 180 deg.
			r = qneg(r);			// -conj(q0)*q1 == conj(q0)*(-q1), so flipping both
			b = qneg(b);			// keeps r == conj(q0)*b.
		}
		const T c = r[0];			// == cos(th) == qdot(q0, b)
		const T s = sqrt(r[1] * r[1] + r[2] * r[2] + r[3] * r[3]);	// == sin(th) >= 0
		if (s <= T(0))
			return qnormalize(q0);	// identical orientations: nothing to interpolate

		const T th = atan2(s, c);	// == fabs(acos(clamp(dot,-1,1))), but stable
		const T w1 = sin(t * th) / s;		// == sin(t*th)/sin(th)
		const T w0 = cos(t * th) - c * w1;	// == sin((1-t)*th)/sin(th)
		return qadd(qscale(q0, w0), qscale(b, w1));
	}

	// Interpolate through the relative rotation, so q0 stays authoritative and
	// only a fraction of the correction is applied (network smoothing, damping).
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qslerp_rel(const clmvec<4, T>& q0, const clmvec<4, T>& q1, T t)
	{
		return qmul(q0, qslerp(qident<T>(), qrel(q0, q1), t));
	}

	// -- exp/log: the general form, slerp(q0,q1,t) == q0 * (conj(q0)*q1)^t -----
	// Unit-quaternion log (pure quaternion); exp of a general quaternion.
	// Note on signs: q^t = exp(t*log q) follows the geodesic through the
	// representative you pass in.  Use qcanon() first if you want the short arc.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qlog(const clmvec<4, T>& q)
	{
		const T v = sqrt(q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
		if (v <= T(0))
			return clmvec<4, T>(T(0), T(0), T(0), T(0));
		const T k = atan2(v, q[0]) / v;
		return clmvec<4, T>(T(0), k * q[1], k * q[2], k * q[3]);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qexp(const clmvec<4, T>& q)
	{
		const T v = sqrt(q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
		const T e = exp(q[0]);
		if (v <= T(0))
			return clmvec<4, T>(e, T(0), T(0), T(0));
		const T k = e * sin(v) / v;
		return clmvec<4, T>(e * cos(v), k * q[1], k * q[2], k * q[3]);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qpow(const clmvec<4, T>& q, T t)
	{
		return qnormalize(qexp(qscale(qlog(q), t)));
	}

	// One frame's worth of a constant-rate slerp: advance along the q0 -> q1 arc
	// by right-multiplying it each frame, cur = qmul(cur, step), which walks the
	// arc in q0's local frame.  Amortises the transcendentals out of the loop.
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<4, T> qslerp_step(const clmvec<4, T>& q0, const clmvec<4, T>& q1,
	                                          T step, T duration)
	{
		if (duration <= T(0))
			return qident<T>();
		return qslerp(qident<T>(), qrel(q0, q1), step / duration);
	}
}

#endif // CLFE_CLMATH_QINTERP_H
