#ifndef CLFE_CLMATH_MATUTILS_H
#define CLFE_CLMATH_MATUTILS_H

#include "math.h"
#include "mdef.h"
#include "vec.h"
#include "mat.h"

// All the non-generic (3d related) stuff is here

namespace clfe
{

	using matdefault_t = float;

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mtranslate(T x, T y, T z)
	{
		return clmmat<4, 4, T>(
			(T)1, (T)0, (T)0, x,
			(T)0, (T)1, (T)0, y,
			(T)0, (T)0, (T)1, z,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mtranslate(const clmvec<4, T>& vec)
	{
		return mtranslate<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	//

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mscale3(T sx, T sy, T sz)
	{
		return clmmat<3, 3, T>(
			sx, (T)0, (T)0,
			(T)0, sy, (T)0,
			(T)0, (T)0, sz
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mscale3(const clmvec<3, T>& vec)
	{
		return mscale3<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mscale4(T sx, T sy, T sz)
	{
		return clmmat<4, 4, T>(
			sx, (T)0, (T)0, (T)0,
			(T)0, sy, (T)0, (T)0,
			(T)0, (T)0, sz, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mscale4(const clmvec<3, T>& vec)
	{
		return mscale4<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mscale(T sx, T sy, T sz)
	{
		return mscale4<T>(sx, sy, sz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mscale(const clmvec<3, T>& vec)
	{
		return mscale4<T>(vec);
	}

	//

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatex3(T rx)
	{
		T c = cos(rx);
		T s = sin(rx);
		return clmmat<3, 3, T>(
			(T)1, (T)0, (T)0,
			(T)0, c, -s,
			(T)0, s, c
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatex4(T rx)
	{
		T c = cos(rx);
		T s = sin(rx);
		return clmmat<4, 4, T>(
			(T)1, (T)0, (T)0, (T)0,
			(T)0, c, -s, (T)0,
			(T)0, s, c, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatex(T rx)
	{
		return mrotatex4<T>(rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatey3(T ry)
	{
		T c = cos(ry);
		T s = sin(ry);
		return clmmat<3, 3, T>(
			c, (T)0, s,
			(T)0, (T)1, (T)0,
			-s, (T)0, c
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatey4(T ry)
	{
		T c = cos(ry);
		T s = sin(ry);
		return clmmat<4, 4, T>(
			c, (T)0, s, (T)0,
			(T)0, (T)1, (T)0, (T)0,
			-s, (T)0, c, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatey(T ry)
	{
		return mrotatey4<T>(ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatez3(T rz)
	{
		T c = cos(rz);
		T s = sin(rz);
		return clmmat<3, 3, T>(
			c, -s, (T)0,
			s, c, (T)0,
			(T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatez4(T rz)
	{
		T c = cos(rz);
		T s = sin(rz);
		return clmmat<4, 4, T>(
			c, -s, (T)0, (T)0,
			s, c, (T)0, (T)0,
			(T)0, (T)0, (T)1, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatez(T rz)
	{
		return mrotatez4<T>(rz);
	}

	//

	// Rotates around x first, then y
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatexy3(T rx, T ry)
	{
		T cx = cos(rx);
		T sx = sin(rx);
		T cy = cos(ry);
		T sy = sin(ry);
		return clmmat<3, 3, T>(
			cy, sx * sy, cx * sy,
			(T)0, cx, -sx,
			-sy, cy * sx, cx * cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatexy3(const clmvec<2, T>& vec)
	{
		return mrotatexy3<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatexy4(T rx, T ry)
	{
		T cx = cos(rx);
		T sx = sin(rx);
		T cy = cos(ry);
		T sy = sin(ry);
		return clmmat<4, 4, T>(
			cy, sx * sy, cx * sy, (T)0,
			(T)0, cx, -sx, (T)0,
			-sy, cy * sx, cx * cy, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexy4(const clmvec<2, T>& vec)
	{
		return mrotatexy4<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexy(T rx, T ry)
	{
		return mrotatexy4<T>(rx, ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexy(const clmvec<2, T>& vec)
	{
		return mrotatexy4<T>(vec);
	}

	// Rotates around x first, then z
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatexz3(T rx, T rz)
	{
		T cx = cos(rx);
		T sx = sin(rx);
		T cz = cos(rz);
		T sz = sin(rz);
		return clmmat<3, 3, T>(
			cz, -cx * sz, sx * sz,
			sz, cx * cz, -cz * sx,
			(T)0, sx, cx
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatexz3(const clmvec<2, T>& vec)
	{
		return mrotatexz3<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatexz4(T rx, T rz)
	{
		T cx = cos(rx);
		T sx = sin(rx);
		T cz = cos(rz);
		T sz = sin(rz);
		return clmmat<4, 4, T>(
			cz, -cx * sz, sx * sz, (T)0,
			sz, cx * cz, -cz * sx, (T)0,
			(T)0, sx, cx, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexz4(const clmvec<2, T>& vec)
	{
		return mrotatexz4<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexz(T rx, T rz)
	{
		return mrotatexz4<T>(rx, rz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexz(const clmvec<2, T>& vec)
	{
		return mrotatexz4<T>(vec);
	}

	// Rotates around y first, then x
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotateyx3(T ry, T rx)
	{
		T cy = cos(ry);
		T sy = sin(ry);
		T cx = cos(rx);
		T sx = sin(rx);
		return clmmat<3, 3, T>(
			cy, (T)0, sy,
			sx * sy, cx, -cy * sx,
			-cx * sy, sx, cx * cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotateyx3(const clmvec<2, T>& vec)
	{
		return mrotateyx3<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotateyx4(T ry, T rx)
	{
		T cy = cos(ry);
		T sy = sin(ry);
		T cx = cos(rx);
		T sx = sin(rx);
		return clmmat<4, 4, T>(
			cy, (T)0, sy, (T)0,
			sx * sy, cx, -cy * sx, (T)0,
			-cx * sy, sx, cx * cy, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyx4(const clmvec<2, T>& vec)
	{
		return mrotateyx4<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyx(T ry, T rx)
	{
		return mrotateyx4<T>(ry, rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyx(const clmvec<2, T>& vec)
	{
		return mrotateyx4<T>(vec);
	}

	// Rotates around y first, then z
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotateyz3(T ry, T rz)
	{
		T cy = cos(ry);
		T sy = sin(ry);
		T cz = cos(rz);
		T sz = sin(rz);
		return clmmat<3, 3, T>(
			cy * cz, -sz, cz * sy,
			cy * sz, cz, sy * sz,
			-sy, (T)0, cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotateyz3(const clmvec<2, T>& vec)
	{
		return mrotateyz3<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotateyz4(T ry, T rz)
	{
		T cy = cos(ry);
		T sy = sin(ry);
		T cz = cos(rz);
		T sz = sin(rz);
		return clmmat<4, 4, T>(
			cy * cz, -sz, cz * sy, (T)0,
			cy * sz, cz, sy * sz, (T)0,
			-sy, (T)0, cy, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyz4(const clmvec<2, T>& vec)
	{
		return mrotateyz4<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyz(T ry, T rz)
	{
		return mrotateyz4<T>(ry, rz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyz(const clmvec<2, T>& vec)
	{
		return mrotateyz4<T>(vec);
	}

	// Rotates around z first, then x
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatezx3(T rz, T rx)
	{
		T cz = cos(rz);
		T sz = sin(rz);
		T cx = cos(rx);
		T sx = sin(rx);
		return clmmat<3, 3, T>(
			cz, -sz, (T)0,
			cx * sz, cx * cz, -sx,
			sx * sz, cz * sx, cx
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatezx3(const clmvec<2, T>& vec)
	{
		return mrotatezx3<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatezx4(T rz, T rx)
	{
		T cz = cos(rz);
		T sz = sin(rz);
		T cx = cos(rx);
		T sx = sin(rx);
		return clmmat<4, 4, T>(
			cz, -sz, (T)0, (T)0,
			cx * sz, cx * cz, -sx, (T)0,
			sx * sz, cz * sx, cx, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezx4(const clmvec<2, T>& vec)
	{
		return mrotatezx4<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezx(T rz, T rx)
	{
		return mrotatezx4<T>(rz, rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezx(const clmvec<2, T>& vec)
	{
		return mrotatezx4<T>(vec);
	}

	// Rotates around z first, then y
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatezy3(T rz, T ry)
	{
		T cz = cos(rz);
		T sz = sin(rz);
		T cy = cos(ry);
		T sy = sin(ry);
		return clmmat<3, 3, T>(
			cy * cz, -cy * sz, sy,
			sz, cz, (T)0,
			-cz * sy, sy * sz, cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatezy3(const clmvec<2, T>& vec)
	{
		return mrotatezy3<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatezy4(T rz, T ry)
	{
		T cz = cos(rz);
		T sz = sin(rz);
		T cy = cos(ry);
		T sy = sin(ry);
		return clmmat<4, 4, T>(
			cy * cz, -cy * sz, sy, (T)0,
			sz, cz, (T)0, (T)0,
			-cz * sy, sy * sz, cy, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezy4(const clmvec<2, T>& vec)
	{
		return mrotatezy4<T>(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezy(T rz, T ry)
	{
		return mrotatezy4<T>(rz, ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezy(const clmvec<2, T>& vec)
	{
		return mrotatezy4<T>(vec);
	}

	//
	
	// Rotates around x first, then y, then z
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatexyz3(T rx, T ry, T rz)
	{
		T cx = cos(rx);
		T sx = sin(rx);
		T cy = cos(ry);
		T sy = sin(ry);
		T cz = cos(rz);
		T sz = sin(rz);
		return clmmat<3, 3, T>(
			cy * cz, cz * sx * sy - cx * sz, sx * sz + cx * cz * sy,
			cy * sz, cx * cz + sx * sy * sz, cx * sy * sz - cz * sx,
			-sy, cy * sx, cx * cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatexyz3(const clmvec<3, T>& vec)
	{
		return mrotatexyz3<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatexyz4(T rx, T ry, T rz)
	{
		T cx = cos(rx);
		T sx = sin(rx);
		T cy = cos(ry);
		T sy = sin(ry);
		T cz = cos(rz);
		T sz = sin(rz);
		return clmmat<4, 4, T>(
			cy * cz, cz * sx * sy - cx * sz, sx * sz + cx * cz * sy, (T)0,
			cy * sz, cx * cz + sx * sy * sz, cx * sy * sz - cz * sx, (T)0,
			-sy, cy * sx, cx * cy, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyz4(const clmvec<3, T>& vec)
	{
		return mrotatexyz4<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyz(T rx, T ry, T rz)
	{
		return mrotatexyz4<T>(rx, ry, rz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyz(const clmvec<3, T>& vec)
	{
		return mrotatexyz4<T>(vec);
	}

	// Rotates around x first, then z, then y
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatexzy3(T rx, T rz, T ry)
	{
		T cx = cos(rx);
		T sx = sin(rx);
		T cz = cos(rz);
		T sz = sin(rz);
		T cy = cos(ry);
		T sy = sin(ry);
		return clmmat<3, 3, T>(
			cy * cz, sx * sy - cx * cy * sz, cx * sy + cy * sx * sz,
			sz, cx * cz, -cz * sx,
			-cz * sy, cy * sx + cx * sy * sz, cx * cy - sx * sy * sz
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatexzy3(const clmvec<3, T>& vec)
	{
		return mrotatexzy3<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatexzy4(T rx, T rz, T ry)
	{
		T cx = cos(rx);
		T sx = sin(rx);
		T cz = cos(rz);
		T sz = sin(rz);
		T cy = cos(ry);
		T sy = sin(ry);
		return clmmat<4, 4, T>(
			cy * cz, sx * sy - cx * cy * sz, cx * sy + cy * sx * sz, (T)0,
			sz, cx * cz, -cz * sx, (T)0,
			-cz * sy, cy * sx + cx * sy * sz, cx * cy - sx * sy * sz, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzy4(const clmvec<3, T>& vec)
	{
		return mrotatexzy4<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzy(T rx, T rz, T ry)
	{
		return mrotatexzy4<T>(rx, rz, ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzy(const clmvec<3, T>& vec)
	{
		return mrotatexzy4<T>(vec);
	}

	// Rotates around y first, then x, then z
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotateyxz3(T ry, T rx, T rz)
	{
		T cy = cos(ry);
		T sy = sin(ry);
		T cx = cos(rx);
		T sx = sin(rx);
		T cz = cos(rz);
		T sz = sin(rz);
		return clmmat<3, 3, T>(
			cy * cz - sx * sy * sz, -cx * sz, cz * sy + cy * sx * sz,
			cy * sz + cz * sx * sy, cx * cz, sy * sz - cy * cz * sx,
			-cx * sy, sx, cx * cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotateyxz3(const clmvec<3, T>& vec)
	{
		return mrotateyxz3<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotateyxz4(T ry, T rx, T rz)
	{
		T cy = cos(ry);
		T sy = sin(ry);
		T cx = cos(rx);
		T sx = sin(rx);
		T cz = cos(rz);
		T sz = sin(rz);
		return clmmat<4, 4, T>(
			cy * cz - sx * sy * sz, -cx * sz, cz * sy + cy * sx * sz, (T)0,
			cy * sz + cz * sx * sy, cx * cz, sy * sz - cy * cz * sx, (T)0,
			-cx * sy, sx, cx * cy, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxz4(const clmvec<3, T>& vec)
	{
		return mrotateyxz4<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxz(T ry, T rx, T rz)
	{
		return mrotateyxz4<T>(ry, rx, rz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxz(const clmvec<3, T>& vec)
	{
		return mrotateyxz4<T>(vec);
	}

	// Rotates around y first, then z, then x
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotateyzx3(T ry, T rz, T rx)
	{
		T cy = cos(ry);
		T sy = sin(ry);
		T cz = cos(rz);
		T sz = sin(rz);
		T cx = cos(rx);
		T sx = sin(rx);
		return clmmat<3, 3, T>(
			cy * cz, -sz, cz * sy,
			sx * sy + cx * cy * sz, cx * cz, cx * sy * sz - cy * sx,
			cy * sx * sz - cx * sy, cz * sx, cx * cy + sx * sy * sz
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotateyzx3(const clmvec<3, T>& vec)
	{
		return mrotateyzx3<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotateyzx4(T ry, T rz, T rx)
	{
		T cy = cos(ry);
		T sy = sin(ry);
		T cz = cos(rz);
		T sz = sin(rz);
		T cx = cos(rx);
		T sx = sin(rx);
		return clmmat<4, 4, T>(
			cy * cz, -sz, cz * sy, (T)0,
			sx * sy + cx * cy * sz, cx * cz, cx * sy * sz - cy * sx, (T)0,
			cy * sx * sz - cx * sy, cz * sx, cx * cy + sx * sy * sz, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzx4(const clmvec<3, T>& vec)
	{
		return mrotateyzx4<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzx(T ry, T rz, T rx)
	{
		return mrotateyzx4<T>(ry, rz, rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzx(const clmvec<3, T>& vec)
	{
		return mrotateyzx4<T>(vec);
	}

	// Rotates around z first, then x, then y
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatezxy3(T rz, T rx, T ry)
	{
		T cz = cos(rz);
		T sz = sin(rz);
		T cx = cos(rx);
		T sx = sin(rx);
		T cy = cos(ry);
		T sy = sin(ry);
		return clmmat<3, 3, T>(
			cy * cz + sx * sy * sz, cz * sx * sy - cy * sz, cx * sy,
			cx * sz, cx * cz, -sx,
			cy * sx * sz - cz * sy, sy * sz + cy * cz * sx, cx * cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatezxy3(const clmvec<3, T>& vec)
	{
		return mrotatezxy3<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatezxy4(T rz, T rx, T ry)
	{
		T cz = cos(rz);
		T sz = sin(rz);
		T cx = cos(rx);
		T sx = sin(rx);
		T cy = cos(ry);
		T sy = sin(ry);
		return clmmat<4, 4, T>(
			cy * cz + sx * sy * sz, cz * sx * sy - cy * sz, cx * sy, (T)0,
			cx * sz, cx * cz, -sx, (T)0,
			cy * sx * sz - cz * sy, sy * sz + cy * cz * sx, cx * cy, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxy4(const clmvec<3, T>& vec)
	{
		return mrotatezxy4<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxy(T rz, T rx, T ry)
	{
		return mrotatezxy4<T>(rz, rx, ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxy(const clmvec<3, T>& vec)
	{
		return mrotatezxy4<T>(vec);
	}

	// Rotates around z first, then y, then x
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatezyx3(T rz, T ry, T rx)
	{
		T cz = cos(rz);
		T sz = sin(rz);
		T cy = cos(ry);
		T sy = sin(ry);
		T cx = cos(rx);
		T sx = sin(rx);
		return clmmat<3, 3, T>(
			cy * cz, -cy * sz, sy,
			cx * sz + cz * sx * sy, cx * cz - sx * sy * sz, -cy * sx,
			sx * sz - cx * cz * sy, cz * sx + cx * sy * sz, cx * cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatezyx3(const clmvec<3, T>& vec)
	{
		return mrotatezyx3<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatezyx4(T rz, T ry, T rx)
	{
		T cz = cos(rz);
		T sz = sin(rz);
		T cy = cos(ry);
		T sy = sin(ry);
		T cx = cos(rx);
		T sx = sin(rx);
		return clmmat<4, 4, T>(
			cy * cz, -cy * sz, sy, (T)0,
			cx * sz + cz * sx * sy, cx * cz - sx * sy * sz, -cy * sx, (T)0,
			sx * sz - cx * cz * sy, cz * sx + cx * sy * sz, cx * cy, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyx4(const clmvec<3, T>& vec)
	{
		return mrotatezyx4<T>(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyx(T rz, T ry, T rx)
	{
		return mrotatezyx4<T>(rz, ry, rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyx(const clmvec<3, T>& vec)
	{
		return mrotatezyx4<T>(vec);
	}

	//

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<2, 2, T> mrotate2(T rot)
	{
		T c = cos(rot);
		T s = sin(rot);
		return clmmat<2, 2, T>(
			c, -s,
			s, c
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<2, 2, T> mrotate(T rot)
	{
		return mrotate2<T>(rot);
	}

	//

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotate3(T rot, T x, T y, T z)
	{
		T c = cos(rot);
		T s = sin(rot);
		T t = (T)1 - c;
		return clmmat<3, 3, T>(
			t * x * x + c, t * x * y - s * z, t * x * z + s * y,
			t * x * y + s * z, t * y * y + c, t * y * z - s * x,
			t * x * z - s * y, t * y * z + s * x, t * z * z + c
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotate3(T rot, const clmvec<3, T>& axis)
	{
		return mrotate3<T>(rot, axis.get(0), axis.get(1), axis.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotate4(T rot, T x, T y, T z)
	{
		T c = cos(rot);
		T s = sin(rot);
		T t = (T)1 - c;
		return clmmat<4, 4, T>(
			t * x * x + c, t * x * y - s * z, t * x * z + s * y, (T)0,
			t * x * y + s * z, t * y * y + c, t * y * z - s * x, (T)0,
			t * x * z - s * y, t * y * z + s * x, t * z * z + c, (T)0,
			(T)0, (T)0, (T)0, (T)1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotate4(T rot, const clmvec<3, T>& axis)
	{
		return mrotate4<T>(rot, axis.get(0), axis.get(1), axis.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotate4(const clmvec<4, T>& axis)
	{
		return mrotate4<T>(axis.get(0), axis.get(1), axis.get(2), axis.get(3));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotate(T rot, T x, T y, T z)
	{
		return mrotate4<T>(rot, x, y, z);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotate(T rot, const clmvec<3, T>& axis)
	{
		return mrotate4<T>(rot, axis);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotate(const clmvec<4, T>& axis)
	{
		return mrotate4<T>(axis);
	}

}

#endif // CLFE_CLMATH_MATUTILS_H