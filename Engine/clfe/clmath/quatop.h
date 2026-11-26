#ifndef CLFE_CLMATH_QUATOP_H
#define CLFE_CLMATH_QUATOP_H

#include "math.h"
#include "mdef.h"
#include "mconst.h"
#include "quat.h"
#include "vec.h"
#include "vecop.h"

namespace clfe
{

	// Cast to another quaternion type (Note: this function is somewhat redundant)
	template <typename T, typename U>
		requires mcompat<T, U>
	constexpr inline clmquat<T> vcast(const clmquat<U>& quat)
	{
		return clmquat<T>(quat);
	}

	// Basic operations
	// Note: a couple operations such as adding and scaling are already defined by vector operations

	// Adds rotations togethor
	template <typename T, typename U>
		requires arithmetic<T, U>
	constexpr auto qmul(const clmquat<T>& quat1, const clmquat<U>& quat2) -> clmquat<decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		return clmquat<decltype(static_cast<T>(0) * static_cast<U>(0))>(
			quat1.get(3) * quat2.get(0) + quat1.get(0) * quat2.get(3) + quat1.get(1) * quat2.get(2) - quat1.get(2) * quat2.get(1),
			quat1.get(3) * quat2.get(1) - quat1.get(0) * quat2.get(2) + quat1.get(1) * quat2.get(3) + quat1.get(2) * quat2.get(0),
			quat1.get(3) * quat2.get(2) + quat1.get(0) * quat2.get(1) - quat1.get(1) * quat2.get(0) + quat1.get(2) * quat2.get(3),
			quat1.get(3) * quat2.get(3) - quat1.get(0) * quat2.get(0) - quat1.get(1) * quat2.get(1) - quat1.get(2) * quat2.get(2)
		);
	}

	// quat * quat (adds rotations togethor)
	template <typename T, typename U>
		requires arithmetic<T, U>
	constexpr inline auto operator*(const clmquat<T>& quat1, const clmquat<U>& quat2) -> clmquat<decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		return qmul<T, U>(quat1, quat2);
	}

	// quat *= quat (adds rotations togethor)
	// Equals quat1 = quat2 * quat1
	template <typename T, typename U>
		requires arithmetic<T, U>
	constexpr clmquat<T>& operator*=(clmquat<T>& quat1, const clmquat<U>& quat2)
	{
		quat1 = qmul<U, T>(quat2, quat1);
		return quat1;
	}

	// Added for local utility
	// Same as [clmquat<T>] + [clmquat<T>]
	template <typename T, typename U>
		requires arithmetic<T, U>
	constexpr inline auto qadd(const clmquat<T>& quat1, const clmquat<U>& quat2) -> clmquat<decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		return clmquat<decltype(static_cast<T>(0) + static_cast<U>(0))>(quat1.get(0) + quat2.get(0), quat1.get(1) + quat2.get(1), quat1.get(2) + quat2.get(2), quat1.get(3) + quat2.get(3));
	}

	// Added for local utility
	// Same as [clmquat<T>] * [T]
	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> qscale(const clmquat<T>& quat, T scale)
	{
		return clmquat<T>(quat.get(0) * scale, quat.get(1) * scale, quat.get(2) * scale, quat.get(3) * scale);
	}

	// Scales rotation

	// Same rotation, but values flipped
	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> qneg(const clmquat<T>& quat)
	{
		return clmquat<T>(-quat.get(0), -quat.get(1), -quat.get(2), -quat.get(3));
	}

	// Flip rotation
	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> qconj(const clmquat<T>& quat)
	{
		return clmquat<T>(-quat.get(0), -quat.get(1), -quat.get(2), quat.get(3));
	}

	// -quat (flips rotation)
	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> operator-(const clmquat<T>& quat)
	{
		return qconj<T>(quat);
	}

	// Utility

	// Dot product
	template <typename T, typename U>
		requires arithmetic<T, U>
	constexpr inline auto qdot(const clmquat<T>& quat1, const clmquat<U>& quat2) -> decltype(static_cast<T>(0)* static_cast<U>(0))
	{
		return quat1.get(0) * quat2.get(0) + quat1.get(1) * quat2.get(1) + quat1.get(2) * quat2.get(2) + quat1.get(3) * quat2.get(3);
	}

	// Returns rotation with non-negative scalar part
	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> qcanon(const clmquat<T>& quat)
	{
		return (quat.get(3) < static_cast<T>(0)) ? qneg<T>(quat) : clmquat<T>(quat);
	}

	// Relative rotation from quat1 to quat2
	template <typename T, typename U>
		requires arithmetic<T, U>
	constexpr inline auto qrel(const clmquat<T>& quat1, const clmquat<U>& quat2) -> clmquat<decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		return qmul<T, U>(qconj<T>(quat1), quat2);
	}

	// Shortest arc angle between quat1 and quat2
	template <typename T, typename U>
		requires floating_point<T>
	constexpr auto qarc_len(const clmquat<T>& quat1, const clmquat<U>& quat2) -> decltype(static_cast<T>(0) * static_cast<U>(0))
	{
		clmquat<decltype(static_cast<T>(0) * static_cast<U>(0))> r = qrel<T, U>(quat1, quat2);
		decltype(static_cast<T>(0) * static_cast<U>(0)) w = (r.get(3) < static_cast<decltype(static_cast<T>(0) * static_cast<U>(0))>(0)) ? -r.get(3) : r.get(3);
		return static_cast<T>(atan2(sqrt(r.get(0) * r.get(0) + r.get(1) * r.get(1) + r.get(2) * r.get(2)), w));
	}

	// Normals

	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> qidentity()
	{
		return clmquat<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	}

	// Normalize without checking length
	template <typename T>
		requires floating_point<T>
	constexpr clmquat<T> qnormalize(const clmquat<T>& quat)
	{
		T ilen = static_cast<T>(1) / static_cast<T>(sqrt(quat.get(0) * quat.get(0) + quat.get(1) * quat.get(1) + quat.get(2) * quat.get(2) + quat.get(3) * quat.get(3)));
		return clmquat<T>(quat.get(0) * ilen, quat.get(1) * ilen, quat.get(2) * ilen, quat.get(3) * ilen);
	}

	// Safe normalize with default unit quaternion as exception
	template <typename T>
		requires floating_point<T>
	constexpr clmquat<T> qsnormalize(const clmquat<T>& quat, T thres2 = _CLFE_DEF_THRES2_VALUE)
	{
		T l2 = quat.get(0) * quat.get(0) + quat.get(1) * quat.get(1) + quat.get(2) * quat.get(2) + quat.get(3) * quat.get(3);
		if (l2 <= thres2)
		{
			return qidentity<T>();
		}

		T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
		return clmquat<T>(quat.get(0) * invlen, quat.get(1) * invlen, quat.get(2) * invlen, quat.get(3) * invlen);
	}

	// Safe normalize with exception
	template <typename T>
		requires floating_point<T>
	constexpr clmquat<T> qsnormalize(const clmquat<T>& quat, const clmquat<T>& ex, T thres2 = _CLFE_DEF_THRES2_VALUE)
	{
		T l2 = quat.get(0) * quat.get(0) + quat.get(1) * quat.get(1) + quat.get(2) * quat.get(2) + quat.get(3) * quat.get(3);
		if (l2 <= thres2)
		{
			return clmquat<T>(ex);
		}

		T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
		return clmquat<T>(quat.get(0) * invlen, quat.get(1) * invlen, quat.get(2) * invlen, quat.get(3) * invlen);
	}

	// Axis-angles related

	// Quaternion from axis-angle rotation, needs normalized axis
	template <typename T>
		requires floating_point<T>
	constexpr clmquat<T> qfromaxisangle(T angle, const clmvec<3, T>& axis)
	{
		T h = angle * static_cast<T>(0.5);
		T s = static_cast<T>(sin(h));
		return clmquat<T>(axis.get(0) * s, axis.get(1) * s, axis.get(2) * s, static_cast<T>(cos(h)));
	}

	// Rotation angle in [0, pi] (sign-agnostic)
	template <typename T>
		requires floating_point<T>
	constexpr inline T qangle(const clmquat<T>& quat)
	{
		return static_cast<T>(static_cast<T>(2) * static_cast<T>(atan2(sqrt(quat.get(0) * quat.get(0) + quat.get(1) * quat.get(1) + quat.get(2) * quat.get(2)), abs(quat.get(3)))));
	}

	// Unit rotation axis from quaternion
	template <typename T>
		requires floating_point<T>
	constexpr clmvec<3, T> qaxis(const clmquat<T>& quat, T thres2 = _CLFE_DEF_THRES2_VALUE)
	{
		T l2 = quat.get(0) * quat.get(0) + quat.get(1) * quat.get(1) + quat.get(2) * quat.get(2);
		if (l2 <= thres2)
		{
			return clmvec<3, T>((T)0, (T)0, (T)0);
		}

		T inv = static_cast<T>(1) / static_cast<T>(sqrt(l2));
		return clmvec<3, T>(quat.get(0) * inv, quat.get(1) * inv, quat.get(2) * inv);
	}

	// Quaternion log
	// Quaternion -> Scaled Axis + Angle
	template <typename T>
		requires arithmetic<T>
	constexpr clmquat<T> qlog(const clmquat<T>& quat, T thres2 = _CLFE_DEF_THRES2_VALUE)
	{
		T vl2 = quat.get(0) * quat.get(0) + quat.get(1) * quat.get(1) + quat.get(2) * quat.get(2);
		T ln = static_cast<T>(log(quat.get(3)));
		if (vl2 <= thres2)
		{
			return clmquat<T>((T)0, (T)0, (T)0, ln);
		}

		T vl = static_cast<T>(sqrt(vl2));
		T k = static_cast<T>(atan2(vl, quat.get(3))) / vl;
		return clmquat<T>(quat.get(0) * k, quat.get(1) * k, quat.get(2) * k, ln);
	}

	// Quaternion exponent
	// Scaled Axis + Angle -> Quaternion
	template <typename T>
		requires arithmetic<T>
	constexpr clmquat<T> qexp(const clmquat<T>& quat, T thres2 = _CLFE_DEF_THRES2_VALUE)
	{
		T vl2 = quat.get(0) * quat.get(0) + quat.get(1) * quat.get(1) + quat.get(2) * quat.get(2);
		T e = static_cast<T>(exp(quat.get(3)));
		if (vl2 <= thres2)
		{
			return clmquat<T>(T(0), T(0), T(0), e);
		}

		T vl = static_cast<T>(sqrt(vl2));
		const T k = e * static_cast<T>(sin(vl)) / vl;
		return clmquat<T>(quat.get(0) * k, quat.get(1) * k, quat.get(2) * k, static_cast<T>(cos(vl)) * e);
	}

	// Quaternion power
	// Fractional rotation
	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> qpow(const clmquat<T>& quat, T t)
	{
		return qexp<T>(qscale<T>(qlog<T>(quat), t));
	}

	// Quaternion power with normalization
	// Fractional rotation
	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> qupow(const clmquat<T>& quat, T t)
	{
		return qnormalize<T>(qexp<T>(qscale<T>(qlog<T>(quat), t)));
	}

	// Interpolation

	// Linear interpolation (angular velocity not constant)
	template <typename T>
		requires floating_point<T>
	constexpr inline clmquat<T> qnlerp(const clmquat<T>& quat1, const clmquat<T>& quat2, T t)
	{
		clmquat<T> q2 = (qdot<T, T>(quat1, quat2) < static_cast<T>(0)) ? qneg<T>(quat2) : quat2;
		return qnormalize<T>(qadd<T, T>(qscale<T>(quat1, static_cast<T>(1) - t), qscale<T>(q2, t)));
	}

	// Spherical linear interpolation (constant angular velocity)
	template <typename T>
		requires floating_point<T>
	constexpr inline clmquat<T> qslerp(const clmquat<T>& quat1, const clmquat<T>& quat2, T t, T thres2 = _CLFE_DEF_THRES2_VALUE)
	{
		clmquat<T> r = qrel<T, T>(quat1, quat2);
		clmquat<T> q2 = quat2;
		if (r.get(3) < static_cast<T>(0))
		{
			r = qneg<T>(r);
			q2 = qneg<T>(q2);
		}

		T s2 = r.get(0) * r.get(0) + r.get(1) * r.get(1) + r.get(2) * r.get(2);
		if (s2 <= thres2)
		{
			return clmquat<T>(quat1); // Identical rotations
		}

		T s = static_cast<T>(sqrt(s2));
		T c = r.get(3);

		T th = atan2(s, c); // == fabs(acos(clamp(dot,-1,1)))
		T t1 = sin(t * th) / s;
		T t0 = cos(t * th) - c * t1;
		return qadd<T, T>(qscale<T>(quat1, t0), qscale<T>(q2, t1));
	}

	// Spherical linear interpolation (constant angular velocity)
	// Interpolate a relative rotation
	template <typename T>
		requires arithmetic<T>
	constexpr inline clmquat<T> qslerp(const clmquat<T>& quat, T t, T thres2 = _CLFE_DEF_THRES2_VALUE)
	{
		clmquat<T> r = quat;
		if (r.get(3) < static_cast<T>(0))
		{
			r = qneg<T>(r);
		}

		T s2 = r.get(0) * r.get(0) + r.get(1) * r.get(1) + r.get(2) * r.get(2);
		if (s2 <= thres2)
		{
			return qidentity<T>(); // Basically no rotation
		}

		T s = static_cast<T>(sqrt(s2));
		T c = r.get(3);

		T th = atan2(s, c);
		T t1 = sin(t * th) / s;
		T t0 = cos(t * th) - c * t1;
		return qadd<T, T>(qscale<T>(qidentity<T>(), t0), qscale<T>(r, t1));
	}

}

#endif // CLFE_CLMATH_QUATOP_H