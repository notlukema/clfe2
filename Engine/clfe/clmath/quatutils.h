#ifndef CLFE_CLMATH_QUATUTILS_H
#define CLFE_CLMATH_QUATUTILS_H

#include "math.h"
#include "mdef.h"
#include "mconst.h"
#include "mat.h"
#include "quat.h"
#include "quatop.h"

// Partly an extension of matrix utils

namespace clfe
{

	using quatdefault_t = float;
	constexpr inline quatdefault_t Quat_Gimbal_Threshold = 8; // The threshold value (* epsilon) for gimbal lock vs normal axis calculations

	// Normalize without checking length
	template <typename T = quatdefault_t>
		requires floating_point<T>
	constexpr clmquat<T> qnormalize(T x, T y, T z, T w)
	{
		T ilen = static_cast<T>(1) / static_cast<T>(sqrt(x * x + y * y + z * z + w * w));
		return clmquat<T>(x * ilen, y * ilen, z * ilen, w * ilen);
	}

	// Safe normalize with default unit quaternion as exception
	template <typename T = quatdefault_t>
		requires floating_point<T>
	constexpr clmquat<T> qsnormalize(T x, T y, T z, T w, T thres2 = _CLFE_DEF_THRES2_VALUE)
	{
		T l2 = x * x + y * y + z * z + w * w;
		if (l2 <= thres2)
		{
			return qidentity<T>();
		}

		T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
		return clmquat<T>(x * invlen, y * invlen, z * invlen, w * invlen);
	}

	//

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> qrotate3(T x, T y, T z, T w)
	{
		return clmmat<3, 3, T>(
			static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z),
			static_cast<T>(2) * (x * y - w * z),
			static_cast<T>(2) * (x * z + w * y),
			static_cast<T>(2) * (x * y + w * z),
			static_cast<T>(1) - static_cast<T>(2) * (x * x + z * z),
			static_cast<T>(2) * (y * z - w * x),
			static_cast<T>(2) * (x * z - w * y),
			static_cast<T>(2) * (y * z + w * x),
			static_cast<T>(1) - static_cast<T>(2) * (x * x + y * y)
		);
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> qrotate4(T x, T y, T z, T w)
	{
		return clmmat<4, 4, T>(
			static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z),
			static_cast<T>(2) * (x * y - w * z),
			static_cast<T>(2) * (x * z + w * y), (T)0,
			static_cast<T>(2) * (x * y + w * z),
			static_cast<T>(1) - static_cast<T>(2) * (x * x + z * z),
			static_cast<T>(2) * (y * z - w * x), (T)0,
			static_cast<T>(2) * (x * z - w * y),
			static_cast<T>(2) * (y * z + w * x),
			static_cast<T>(1) - static_cast<T>(2) * (x * x + y * y), (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> qrotate(T x, T y, T z, T w)
	{
		return qrotate4<T>(x, y, z, w);
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> qrotate3(const clmquat<T>& quat)
	{
		return qrotate3<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> qrotate4(const clmquat<T>& quat)
	{
		return qrotate4<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> qrotate(const clmquat<T>& quat)
	{
		return qrotate4<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

	//

	// Rotates around x by rx
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> xtoquat(T rx)
	{
		T h = rx * static_cast<T>(0.5);
		return clmquat<T>(sin(h), (T)0, (T)0, cos(h));
	}

	// Rotates around y by ry
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> ytoquat(T ry)
	{
		T h = ry * static_cast<T>(0.5);
		return clmquat<T>((T)0, sin(h), (T)0, cos(h));
	}

	// Rotates around z by rz
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> ztoquat(T rz)
	{
		T h = rz * static_cast<T>(0.5);
		return clmquat<T>((T)0, (T)0, sin(h), cos(h));
	}

	//

	// Rotates around x first, then y
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> xytoquat(T rx, T ry)
	{
		return qmul<T, T>(ytoquat<T>(ry), xtoquat<T>(rx));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> xytoquat(const clmvec<2, T>& vec)
	{
		return xytoquat<T>(vec.get(0), vec.get(1));
	}

	// Rotates around x first, then z
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> xztoquat(T rx, T rz)
	{
		return qmul<T, T>(ztoquat<T>(rz), xtoquat<T>(rx));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> xztoquat(const clmvec<2, T>& vec)
	{
		return xztoquat<T>(vec.get(0), vec.get(1));
	}

	// Rotates around y first, then x
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> yxtoquat(T ry, T rx)
	{
		return qmul<T, T>(xtoquat<T>(rx), ytoquat<T>(ry));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> yxtoquat(const clmvec<2, T>& vec)
	{
		return yxtoquat<T>(vec.get(0), vec.get(1));
	}

	// Rotates around y first, then z
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> yztoquat(T ry, T rz)
	{
		return qmul<T, T>(ztoquat<T>(rz), ytoquat<T>(ry));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> yztoquat(const clmvec<2, T>& vec)
	{
		return yztoquat<T>(vec.get(0), vec.get(1));
	}

	// Rotates around z first, then x
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> zxtoquat(T rz, T rx)
	{
		return qmul<T, T>(xtoquat<T>(rx), ztoquat<T>(rz));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> zxtoquat(const clmvec<2, T>& vec)
	{
		return zxtoquat<T>(vec.get(0), vec.get(1));
	}

	// Rotates around z first, then y
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> zytoquat(T rz, T ry)
	{
		return qmul<T, T>(ytoquat<T>(ry), ztoquat<T>(rz));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> zytoquat(const clmvec<2, T>& vec)
	{
		return zytoquat<T>(vec.get(0), vec.get(1));
	}

	//

	// Rotates around x first, then y, then z
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> xyztoquat(T rx, T ry, T rz)
	{
		clmquat<T> qx = xtoquat<T>(rx);
		clmquat<T> qy = ytoquat<T>(ry);
		clmquat<T> qz = ztoquat<T>(rz);
		return qmul<T, T>(qz, qmul<T, T>(qy, qx));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> xyztoquat(const clmvec<3, T>& vec)
	{
		return xyztoquat<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	// Returns (rx, ry, rz), Gimbal lock at ry = +/-pi/2 returns rx = 0
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmvec<3, T> quattoxyz(T x, T y, T z, T w)
	{
		T l2 = x * x + y * y + z * z + w * w;
		if (l2 <= _CLFE_DEF_THRES2_VALUE)
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
			w = static_cast<T>(1);
		}
		else
		{
			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			x *= invlen;
			y *= invlen;
			z *= invlen;
			w *= invlen;
		}

		T m11 = static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z);
		T m12 = static_cast<T>(2) * (x * y - w * z);
		T m21 = static_cast<T>(2) * (x * y + w * z);
		T m22 = static_cast<T>(1) - static_cast<T>(2) * (x * x + z * z);
		T m31 = static_cast<T>(2) * (x * z - w * y);
		T m32 = static_cast<T>(2) * (y * z + w * x);
		T m33 = static_cast<T>(1) - static_cast<T>(2) * (x * x + y * y);
		T sy = static_cast<T>(0) - m31; // sin(ry)
		if (static_cast<T>(1) - (sy < static_cast<T>(0) ? static_cast<T>(0) - sy : sy) <= static_cast<T>(Quat_Gimbal_Threshold) * mconst<T>::epsilon())
		{
			// ry = +/-pi/2: only rx - rz (sy > 0) or rx + rz (sy < 0) survives
			T ry = (sy < static_cast<T>(0)) ? static_cast<T>(0) - mconst<T>::num::halfpi : mconst<T>::num::halfpi;
			return clmvec<3, T>(static_cast<T>(0), ry, static_cast<T>(0) - static_cast<T>(atan2(m12, m22)));
		}
		T ry = static_cast<T>(atan2(sy, sqrt(m11 * m11 + m21 * m21)));
		return clmvec<3, T>(static_cast<T>(atan2(m32, m33)), ry, static_cast<T>(atan2(m21, m11)));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<3, T> quattoxyz(const clmquat<T>& quat)
	{
		return quattoxyz<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

	//

	// Rotates around x first, then z, then y
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> xzytoquat(T rx, T rz, T ry)
	{
		clmquat<T> qx = xtoquat<T>(rx);
		clmquat<T> qy = ytoquat<T>(ry);
		clmquat<T> qz = ztoquat<T>(rz);
		return qmul<T, T>(qy, qmul<T, T>(qz, qx));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> xzytoquat(const clmvec<3, T>& vec)
	{
		return xzytoquat<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	// Returns (rx, rz, ry), Gimbal lock at rz = +/-pi/2 returns rx = 0
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmvec<3, T> quattoxzy(T x, T y, T z, T w)
	{
		T l2 = x * x + y * y + z * z + w * w;
		if (l2 <= _CLFE_DEF_THRES2_VALUE)
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
			w = static_cast<T>(1);
		}
		else
		{
			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			x *= invlen;
			y *= invlen;
			z *= invlen;
			w *= invlen;
		}

		T m11 = static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z);
		T m12 = static_cast<T>(2) * (x * y - w * z);
		T m13 = static_cast<T>(2) * (x * z + w * y);
		T m21 = static_cast<T>(2) * (x * y + w * z);
		T m22 = static_cast<T>(1) - static_cast<T>(2) * (x * x + z * z);
		T m23 = static_cast<T>(2) * (y * z - w * x);
		T m31 = static_cast<T>(2) * (x * z - w * y);
		T sz = m21; // sin(rz)
		if (static_cast<T>(1) - (sz < static_cast<T>(0) ? static_cast<T>(0) - sz : sz) <= static_cast<T>(Quat_Gimbal_Threshold) * mconst<T>::epsilon())
		{
			// rz = +/-pi/2: only rx + ry (sz > 0) or rx - ry (sz < 0) survives
			T rz = (sz < static_cast<T>(0)) ? static_cast<T>(0) - mconst<T>::num::halfpi : mconst<T>::num::halfpi;
			return clmvec<3, T>(static_cast<T>(0), rz, static_cast<T>(atan2(m13, static_cast<T>(0) - m21 * m12)));
		}
		T rz = static_cast<T>(atan2(sz, sqrt(m22 * m22 + m23 * m23)));
		return clmvec<3, T>(static_cast<T>(atan2(static_cast<T>(0) - m23, m22)), rz, static_cast<T>(atan2(static_cast<T>(0) - m31, m11)));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<3, T> quattoxzy(const clmquat<T>& quat)
	{
		return quattoxzy<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

	//

	// Rotates around y first, then x, then z
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> yxztoquat(T ry, T rx, T rz)
	{
		clmquat<T> qx = xtoquat<T>(rx);
		clmquat<T> qy = ytoquat<T>(ry);
		clmquat<T> qz = ztoquat<T>(rz);
		return qmul<T, T>(qz, qmul<T, T>(qx, qy));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> yxztoquat(const clmvec<3, T>& vec)
	{
		return yxztoquat<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	// Returns (ry, rx, rz), Gimbal lock at rx = +/-pi/2 returns ry = 0
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmvec<3, T> quattoyxz(T x, T y, T z, T w)
	{
		T l2 = x * x + y * y + z * z + w * w;
		if (l2 <= _CLFE_DEF_THRES2_VALUE)
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
			w = static_cast<T>(1);
		}
		else
		{
			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			x *= invlen;
			y *= invlen;
			z *= invlen;
			w *= invlen;
		}

		T m11 = static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z);
		T m12 = static_cast<T>(2) * (x * y - w * z);
		T m21 = static_cast<T>(2) * (x * y + w * z);
		T m22 = static_cast<T>(1) - static_cast<T>(2) * (x * x + z * z);
		T m31 = static_cast<T>(2) * (x * z - w * y);
		T m32 = static_cast<T>(2) * (y * z + w * x);
		T m33 = static_cast<T>(1) - static_cast<T>(2) * (x * x + y * y);
		T sx = m32; // sin(rx)
		if (static_cast<T>(1) - (sx < static_cast<T>(0) ? static_cast<T>(0) - sx : sx) <= static_cast<T>(Quat_Gimbal_Threshold) * mconst<T>::epsilon())
		{
			// rx = +/-pi/2: only ry + rz (sx > 0) or rz - ry (sx < 0) survives
			// both branches recover rz = atan2(m21, m11) once ry = 0
			T rx = (sx < static_cast<T>(0)) ? static_cast<T>(0) - mconst<T>::num::halfpi : mconst<T>::num::halfpi;
			return clmvec<3, T>(static_cast<T>(0), rx, static_cast<T>(atan2(m21, m11)));
		}
		T rx = static_cast<T>(atan2(sx, sqrt(m31 * m31 + m33 * m33)));
		return clmvec<3, T>(static_cast<T>(atan2(static_cast<T>(0) - m31, m33)), rx, static_cast<T>(atan2(static_cast<T>(0) - m12, m22)));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<3, T> quattoyxz(const clmquat<T>& quat)
	{
		return quattoyxz<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

	//

	// Rotates around y first, then z, then x
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> yzxtoquat(T ry, T rz, T rx)
	{
		clmquat<T> qx = xtoquat<T>(rx);
		clmquat<T> qy = ytoquat<T>(ry);
		clmquat<T> qz = ztoquat<T>(rz);
		return qmul<T, T>(qx, qmul<T, T>(qz, qy));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> yzxtoquat(const clmvec<3, T>& vec)
	{
		return yzxtoquat<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	// Returns (ry, rz, rx), Gimbal lock at rz = +/-pi/2 returns ry = 0
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmvec<3, T> quattoyzx(T x, T y, T z, T w)
	{
		T l2 = x * x + y * y + z * z + w * w;
		if (l2 <= _CLFE_DEF_THRES2_VALUE)
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
			w = static_cast<T>(1);
		}
		else
		{
			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			x *= invlen;
			y *= invlen;
			z *= invlen;
			w *= invlen;
		}

		T m11 = static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z);
		T m12 = static_cast<T>(2) * (x * y - w * z);
		T m13 = static_cast<T>(2) * (x * z + w * y);
		T m21 = static_cast<T>(2) * (x * y + w * z);
		T m22 = static_cast<T>(1) - static_cast<T>(2) * (x * x + z * z);
		T m31 = static_cast<T>(2) * (x * z - w * y);
		T m32 = static_cast<T>(2) * (y * z + w * x);
		T sz = static_cast<T>(0) - m12; // sin(rz)
		if (static_cast<T>(1) - (sz < static_cast<T>(0) ? static_cast<T>(0) - sz : sz) <= static_cast<T>(Quat_Gimbal_Threshold) * mconst<T>::epsilon())
		{
			// rz = +/-pi/2: only rx - ry (sz > 0) or rx + ry (sz < 0) survives
			// The two sign cases differ by pi, so branch on them explicitly
			T rz = (sz < static_cast<T>(0)) ? static_cast<T>(0) - mconst<T>::num::halfpi : mconst<T>::num::halfpi;
			T rx = (m12 < static_cast<T>(0)) ? static_cast<T>(atan2(m31, m21)) : static_cast<T>(atan2(static_cast<T>(0) - m31, static_cast<T>(0) - m21));
			return clmvec<3, T>(static_cast<T>(0), rz, rx);
		}
		T rz = static_cast<T>(atan2(sz, sqrt(m22 * m22 + m32 * m32)));
		return clmvec<3, T>(static_cast<T>(atan2(m13, m11)), rz, static_cast<T>(atan2(m32, m22)));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<3, T> quattoyzx(const clmquat<T>& quat)
	{
		return quattoyzx<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

	//

	// Rotates around z first, then x, then y
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> zxytoquat(T rz, T rx, T ry)
	{
		clmquat<T> qx = xtoquat<T>(rx);
		clmquat<T> qy = ytoquat<T>(ry);
		clmquat<T> qz = ztoquat<T>(rz);
		return qmul<T, T>(qy, qmul<T, T>(qx, qz));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> zxytoquat(const clmvec<3, T>& vec)
	{
		return zxytoquat<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	// Returns (rz, rx, ry), Gimbal lock at rx = +/-pi/2 returns rz = 0
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmvec<3, T> quattozxy(T x, T y, T z, T w)
	{
		T l2 = x * x + y * y + z * z + w * w;
		if (l2 <= _CLFE_DEF_THRES2_VALUE)
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
			w = static_cast<T>(1);
		}
		else
		{
			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			x *= invlen;
			y *= invlen;
			z *= invlen;
			w *= invlen;
		}

		T m11 = static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z);
		T m13 = static_cast<T>(2) * (x * z + w * y);
		T m21 = static_cast<T>(2) * (x * y + w * z);
		T m22 = static_cast<T>(1) - static_cast<T>(2) * (x * x + z * z);
		T m23 = static_cast<T>(2) * (y * z - w * x);
		T m31 = static_cast<T>(2) * (x * z - w * y);
		T m33 = static_cast<T>(1) - static_cast<T>(2) * (x * x + y * y);
		T sx = static_cast<T>(0) - m23; // sin(rx)
		if (static_cast<T>(1) - (sx < static_cast<T>(0) ? static_cast<T>(0) - sx : sx) <= static_cast<T>(Quat_Gimbal_Threshold) * mconst<T>::epsilon())
		{
			// rx = +/-pi/2: only ry - rz (sx > 0) or ry + rz (sx < 0) survives
			// with rz = 0 both give ry = atan2(-m31, m11)
			T rx = (sx < static_cast<T>(0)) ? static_cast<T>(0) - mconst<T>::num::halfpi : mconst<T>::num::halfpi;
			return clmvec<3, T>(static_cast<T>(0), rx, static_cast<T>(atan2(static_cast<T>(0) - m31, m11)));
		}
		T rx = static_cast<T>(atan2(sx, sqrt(m21 * m21 + m22 * m22)));
		return clmvec<3, T>(static_cast<T>(atan2(m21, m22)), rx, static_cast<T>(atan2(m13, m33)));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<3, T> quattozxy(const clmquat<T>& quat)
	{
		return quattozxy<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

	//

	// Rotates around z first, then y, then x
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmquat<T> zyxtoquat(T rz, T ry, T rx)
	{
		clmquat<T> qx = xtoquat<T>(rx);
		clmquat<T> qy = ytoquat<T>(ry);
		clmquat<T> qz = ztoquat<T>(rz);
		return qmul<T, T>(qx, qmul<T, T>(qy, qz));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmquat<T> zyxtoquat(const clmvec<3, T>& vec)
	{
		return zyxtoquat<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	// Returns (rz, ry, rx), Gimbal lock at ry = +/-pi/2 returns rz = 0
	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr clmvec<3, T> quattozyx(T x, T y, T z, T w)
	{
		T l2 = x * x + y * y + z * z + w * w;
		if (l2 <= _CLFE_DEF_THRES2_VALUE)
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
			w = static_cast<T>(1);
		}
		else
		{
			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			x *= invlen;
			y *= invlen;
			z *= invlen;
			w *= invlen;
		}

		T m11 = static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z);
		T m12 = static_cast<T>(2) * (x * y - w * z);
		T m13 = static_cast<T>(2) * (x * z + w * y);
		T m21 = static_cast<T>(2) * (x * y + w * z);
		T m22 = static_cast<T>(1) - static_cast<T>(2) * (x * x + z * z);
		T m23 = static_cast<T>(2) * (y * z - w * x);
		T m33 = static_cast<T>(1) - static_cast<T>(2) * (x * x + y * y);
		T sy = m13; // sin(ry)
		if (static_cast<T>(1) - (sy < static_cast<T>(0) ? static_cast<T>(0) - sy : sy) <= static_cast<T>(Quat_Gimbal_Threshold) * mconst<T>::epsilon())
		{
			// ry = +/-pi/2: only rx + rz (sy > 0) or rz - rx (sy < 0) survives
			// with rz = 0 the recovered rx flips sign between the two cases
			T ry = (sy < static_cast<T>(0)) ? static_cast<T>(0) - mconst<T>::num::halfpi : mconst<T>::num::halfpi;
			return clmvec<3, T>(static_cast<T>(0), ry, sy * static_cast<T>(atan2(m21, m22)));
		}
		T ry = static_cast<T>(atan2(sy, sqrt(m11 * m11 + m12 * m12)));
		return clmvec<3, T>(static_cast<T>(atan2(static_cast<T>(0) - m12, m11)), ry, static_cast<T>(atan2(static_cast<T>(0) - m23, m33)));
	}

	template <typename T = quatdefault_t>
		requires arithmetic<T>
	constexpr inline clmvec<3, T> quattozyx(const clmquat<T>& quat)
	{
		return quattozyx<T>(quat.get(0), quat.get(1), quat.get(2), quat.get(3));
	}

}

#endif // CLFE_CLMATH_QUATUTILS_H
