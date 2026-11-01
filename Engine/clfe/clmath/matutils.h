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
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mtranslate(const clmvec<4, T>& vec)
	{
		return mtranslate(vec.get(0), vec.get(1), vec.get(2));
	}

	//

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mscale3(T sx, T sy, T sz)
	{
		return clmmat<3, 3, T>(
			sx, 0, 0,
			0, sy, 0,
			0, 0, sz
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mscale3(const clmvec<3, T>& vec)
	{
		return mscale3(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mscale4(T sx, T sy, T sz)
	{
		return clmmat<4, 4, T>(
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mscale4(const clmvec<3, T>& vec)
	{
		return mscale4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mscale(T sx, T sy, T sz)
	{
		return mscale4(sx, sy, sz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mscale(const clmvec<3, T>& vec)
	{
		return mscale4(vec);
	}

	//

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatex3(T rx)
	{
		T c = cos(rx);
		T s = sin(rx);
		return clmmat<3, 3, T>(
			1, 0, 0,
			0, c, -s,
			0, s, c
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatex4(T rx)
	{
		T c = cos(rx);
		T s = sin(rx);
		return clmmat<4, 4, T>(
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatex(T rx)
	{
		return mrotatex4(rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatey3(T ry)
	{
		T c = cos(ry);
		T s = sin(ry);
		return clmmat<3, 3, T>(
			c, 0, s,
			0, 1, 0,
			-s, 0, c
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatey4(T ry)
	{
		T c = cos(ry);
		T s = sin(ry);
		return clmmat<4, 4, T>(
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatey(T ry)
	{
		return mrotatey4(ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatez3(T rz)
	{
		T c = cos(rz);
		T s = sin(rz);
		return clmmat<3, 3, T>(
			c, -s, 0,
			s, c, 0,
			0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatez4(T rz)
	{
		T c = cos(rz);
		T s = sin(rz);
		return clmmat<4, 4, T>(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatez(T rz)
	{
		return mrotatez4(rz);
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
			0, cx, -sx,
			-sy, cy * sx, cx * cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatexy3(const clmvec<2, T>& vec)
	{
		return mrotatexy3(vec.get(0), vec.get(1));
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
			cy, sx * sy, cx * sy, 0,
			0, cx, -sx, 0,
			-sy, cy * sx, cx * cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexy4(const clmvec<2, T>& vec)
	{
		return mrotatexy4(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexy(T rx, T ry)
	{
		return mrotatexy4(rx, ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexy(const clmvec<2, T>& vec)
	{
		return mrotatexy4(vec);
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
			0, sx, cx
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatexz3(const clmvec<2, T>& vec)
	{
		return mrotatexz3(vec.get(0), vec.get(1));
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
			cz, -cx * sz, sx * sz, 0,
			sz, cx * cz, -cz * sx, 0,
			0, sx, cx, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexz4(const clmvec<2, T>& vec)
	{
		return mrotatexz4(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexz(T rx, T rz)
	{
		return mrotatexz4(rx, rz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexz(const clmvec<2, T>& vec)
	{
		return mrotatexz4(vec);
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
			cy, 0, sy,
			sx * sy, cx, -cy * sx,
			-cx * sy, sx, cx * cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotateyx3(const clmvec<2, T>& vec)
	{
		return mrotateyx3(vec.get(0), vec.get(1));
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
			cy, 0, sy, 0,
			sx * sy, cx, -cy * sx, 0,
			-cx * sy, sx, cx * cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyx4(const clmvec<2, T>& vec)
	{
		return mrotateyx4(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyx(T ry, T rx)
	{
		return mrotateyx4(ry, rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyx(const clmvec<2, T>& vec)
	{
		return mrotateyx4(vec);
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
			-sy, 0, cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotateyz3(const clmvec<2, T>& vec)
	{
		return mrotateyz3(vec.get(0), vec.get(1));
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
			cy * cz, -sz, cz * sy, 0,
			cy * sz, cz, sy * sz, 0,
			-sy, 0, cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyz4(const clmvec<2, T>& vec)
	{
		return mrotateyz4(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyz(T ry, T rz)
	{
		return mrotateyz4(ry, rz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyz(const clmvec<2, T>& vec)
	{
		return mrotateyz4(vec);
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
			cz, -sz, 0,
			cx * sz, cx * cz, -sx,
			sx * sz, cz * sx, cx
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatezx3(const clmvec<2, T>& vec)
	{
		return mrotatezx3(vec.get(0), vec.get(1));
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
			cz, -sz, 0, 0,
			cx * sz, cx * cz, -sx, 0,
			sx * sz, cz * sx, cx, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezx4(const clmvec<2, T>& vec)
	{
		return mrotatezx4(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezx(T rz, T rx)
	{
		return mrotatezx4(rz, rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezx(const clmvec<2, T>& vec)
	{
		return mrotatezx4(vec);
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
			sz, cz, 0,
			-cz * sy, sy * sz, cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatezy3(const clmvec<2, T>& vec)
	{
		return mrotatezy3(vec.get(0), vec.get(1));
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
			cy * cz, -cy * sz, sy, 0,
			sz, cz, 0, 0,
			-cz * sy, sy * sz, cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezy4(const clmvec<2, T>& vec)
	{
		return mrotatezy4(vec.get(0), vec.get(1));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezy(T rz, T ry)
	{
		return mrotatezy4(rz, ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezy(const clmvec<2, T>& vec)
	{
		return mrotatezy4(vec);
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
		return mrotatexyz3(vec.get(0), vec.get(1), vec.get(2));
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
			cy * cz, cz * sx * sy - cx * sz, sx * sz + cx * cz * sy, 0,
			cy * sz, cx * cz + sx * sy * sz, cx * sy * sz - cz * sx, 0,
			-sy, cy * sx, cx * cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyz4(const clmvec<3, T>& vec)
	{
		return mrotatexyz4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyz(T rx, T ry, T rz)
	{
		return mrotatexyz4(rx, ry, rz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyz(const clmvec<3, T>& vec)
	{
		return mrotatexyz4(vec);
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
		return mrotatexzy3(vec.get(0), vec.get(1), vec.get(2));
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
			cy * cz, sx * sy - cx * cy * sz, cx * sy + cy * sx * sz, 0,
			sz, cx * cz, -cz * sx, 0,
			-cz * sy, cy * sx + cx * sy * sz, cx * cy - sx * sy * sz, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzy4(const clmvec<3, T>& vec)
	{
		return mrotatexzy4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzy(T rx, T rz, T ry)
	{
		return mrotatexzy4(rx, rz, ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzy(const clmvec<3, T>& vec)
	{
		return mrotatexzy4(vec);
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
		return mrotateyxz3(vec.get(0), vec.get(1), vec.get(2));
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
			cy * cz - sx * sy * sz, -cx * sz, cz * sy + cy * sx * sz, 0,
			cy * sz + cz * sx * sy, cx * cz, sy * sz - cy * cz * sx, 0,
			-cx * sy, sx, cx * cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxz4(const clmvec<3, T>& vec)
	{
		return mrotateyxz4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxz(T ry, T rx, T rz)
	{
		return mrotateyxz4(ry, rx, rz);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxz(const clmvec<3, T>& vec)
	{
		return mrotateyxz4(vec);
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
		return mrotateyzx3(vec.get(0), vec.get(1), vec.get(2));
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
			cy * cz, -sz, cz * sy, 0,
			sx * sy + cx * cy * sz, cx * cz, cx * sy * sz - cy * sx, 0,
			cy * sx * sz - cx * sy, cz * sx, cx * cy + sx * sy * sz, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzx4(const clmvec<3, T>& vec)
	{
		return mrotateyzx4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzx(T ry, T rz, T rx)
	{
		return mrotateyzx4(ry, rz, rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzx(const clmvec<3, T>& vec)
	{
		return mrotateyzx4(vec);
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
		return mrotatezxy3(vec.get(0), vec.get(1), vec.get(2));
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
			cy * cz + sx * sy * sz, cz * sx * sy - cy * sz, cx * sy, 0,
			cx * sz, cx * cz, -sx, 0,
			cy * sx * sz - cz * sy, sy * sz + cy * cz * sx, cx * cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxy4(const clmvec<3, T>& vec)
	{
		return mrotatezxy4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxy(T rz, T rx, T ry)
	{
		return mrotatezxy4(rz, rx, ry);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxy(const clmvec<3, T>& vec)
	{
		return mrotatezxy4(vec);
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
		return mrotatezyx3(vec.get(0), vec.get(1), vec.get(2));
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
			cy * cz, -cy * sz, sy, 0,
			cx * sz + cz * sx * sy, cx * cz - sx * sy * sz, -cy * sx, 0,
			sx * sz - cx * cz * sy, cz * sx + cx * sy * sz, cx * cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyx4(const clmvec<3, T>& vec)
	{
		return mrotatezyx4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyx(T rz, T ry, T rx)
	{
		return mrotatezyx4(rz, ry, rx);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyx(const clmvec<3, T>& vec)
	{
		return mrotatezyx4(vec);
	}

	/*

	// Rotates around x first, then y, then x
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatexyx3(T rx1, T ry, T rx2)
	{
		T cx1 = cos(rx1);
		T sx1 = sin(rx1);
		T cy = cos(ry);
		T sy = sin(ry);
		T cx2 = cos(rx2);
		T sx2 = sin(rx2);
		return clmmat<3, 3, T>(
			cy, sx1 * sy, cx1 * sy,
			sx2 * sy, cx1 * cx2 - cy * sx1 * sx2, -cx2 * sx1 - cx1 * cy * sx2,
			-cx2 * sy, cx1 * sx2 + cx2 * cy * sx1, cx1 * cx2 * cy - sx1 * sx2
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatexyx3(const clmvec<3, T>& vec)
	{
		return mrotatexyx3(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatexyx4(T rx1, T ry, T rx2)
	{
		T cx1 = cos(rx1);
		T sx1 = sin(rx1);
		T cy = cos(ry);
		T sy = sin(ry);
		T cx2 = cos(rx2);
		T sx2 = sin(rx2);
		return clmmat<4, 4, T>(
			cy, sx1 * sy, cx1 * sy, 0,
			sx2 * sy, cx1 * cx2 - cy * sx1 * sx2, -cx2 * sx1 - cx1 * cy * sx2, 0,
			-cx2 * sy, cx1 * sx2 + cx2 * cy * sx1, cx1 * cx2 * cy - sx1 * sx2, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyx4(const clmvec<3, T>& vec)
	{
		return mrotatexyx4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyx(T rx1, T ry, T rx2)
	{
		return mrotatexyx4(rx1, ry, rx2);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexyx(const clmvec<3, T>& vec)
	{
		return mrotatexyx4(vec);
	}

	// Rotates around x first, then z, then x
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatexzx3(T rx1, T rz, T rx2)
	{
		T cx1 = cos(rx1);
		T sx1 = sin(rx1);
		T cz = cos(rz);
		T sz = sin(rz);
		T cx2 = cos(rx2);
		T sx2 = sin(rx2);
		return clmmat<3, 3, T>(
			cz, -cx1 * sz, sx1 * sz,
			cx2 * sz, cx1 * cx2 * cz - sx1 * sx2, -cx1 * sx2 - cx2 * cz * sx1,
			sx2 * sz, cx2 * sx1 + cx1 * cz * sx2, cx1 * cx2 - cz * sx1 * sx2
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatexzx3(const clmvec<3, T>& vec)
	{
		return mrotatexzx3(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatexzx4(T rx1, T rz, T rx2)
	{
		T cx1 = cos(rx1);
		T sx1 = sin(rx1);
		T cz = cos(rz);
		T sz = sin(rz);
		T cx2 = cos(rx2);
		T sx2 = sin(rx2);
		return clmmat<4, 4, T>(
			cz, -cx1 * sz, sx1 * sz, 0,
			cx2 * sz, cx1 * cx2 * cz - sx1 * sx2, -cx1 * sx2 - cx2 * cz * sx1, 0,
			sx2 * sz, cx2 * sx1 + cx1 * cz * sx2, cx1 * cx2 - cz * sx1 * sx2, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzx4(const clmvec<3, T>& vec)
	{
		return mrotatexzx4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzx(T rx1, T rz, T rx2)
	{
		return mrotatexzx4(rx1, rz, rx2);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatexzx(const clmvec<3, T>& vec)
	{
		return mrotatexzx4(vec);
	}

	// Rotates around y first, then x, then y
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotateyxy3(T ry1, T rx, T ry2)
	{
		T cy1 = cos(ry1);
		T sy1 = sin(ry1);
		T cx = cos(rx);
		T sx = sin(rx);
		T cy2 = cos(ry2);
		T sy2 = sin(ry2);
		return clmmat<3, 3, T>(
			cy1 * cy2 - cx * sy1 * sy2, sx * sy2, cy2 * sy1 + cx * cy1 * sy2,
			sx * sy1, cx, -cy1 * sx,
			-cy1 * sy2 - cx * cy2 * sy1, cy2 * sx, cx * cy1 * cy2 - sy1 * sy2
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotateyxy3(const clmvec<3, T>& vec)
	{
		return mrotateyxy3(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotateyxy4(T ry1, T rx, T ry2)
	{
		T cy1 = cos(ry1);
		T sy1 = sin(ry1);
		T cx = cos(rx);
		T sx = sin(rx);
		T cy2 = cos(ry2);
		T sy2 = sin(ry2);
		return clmmat<4, 4, T>(
			cy1 * cy2 - cx * sy1 * sy2, sx * sy2, cy2 * sy1 + cx * cy1 * sy2, 0,
			sx * sy1, cx, -cy1 * sx, 0,
			-cy1 * sy2 - cx * cy2 * sy1, cy2 * sx, cx * cy1 * cy2 - sy1 * sy2, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxy4(const clmvec<3, T>& vec)
	{
		return mrotateyxy4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxy(T ry1, T rx, T ry2)
	{
		return mrotateyxy4(ry1, rx, ry2);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyxy(const clmvec<3, T>& vec)
	{
		return mrotateyxy4(vec);
	}

	// Rotates around y first, then z, then y
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotateyzy3(T ry1, T rz, T ry2)
	{
		T cy1 = cos(ry1);
		T sy1 = sin(ry1);
		T cz = cos(rz);
		T sz = sin(rz);
		T cy2 = cos(ry2);
		T sy2 = sin(ry2);
		return clmmat<3, 3, T>(
			cy1 * cy2 * cz - sy1 * sy2, -cy2 * sz, cy1 * sy2 + cy2 * cz * sy1,
			cy1 * sz, cz, sy1 * sz,
			-cy2 * sy1 - cy1 * cz * sy2, sy2 * sz, cy1 * cy2 - cz * sy1 * sy2
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotateyzy3(const clmvec<3, T>& vec)
	{
		return mrotateyzy3(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotateyzy4(T ry1, T rz, T ry2)
	{
		T cy1 = cos(ry1);
		T sy1 = sin(ry1);
		T cz = cos(rz);
		T sz = sin(rz);
		T cy2 = cos(ry2);
		T sy2 = sin(ry2);
		return clmmat<4, 4, T>(
			cy1 * cy2 * cz - sy1 * sy2, -cy2 * sz, cy1 * sy2 + cy2 * cz * sy1, 0,
			cy1 * sz, cz, sy1 * sz, 0,
			-cy2 * sy1 - cy1 * cz * sy2, sy2 * sz, cy1 * cy2 - cz * sy1 * sy2, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzy4(const clmvec<3, T>& vec)
	{
		return mrotateyzy4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzy(T ry1, T rz, T ry2)
	{
		return mrotateyzy4(ry1, rz, ry2);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotateyzy(const clmvec<3, T>& vec)
	{
		return mrotateyzy4(vec);
	}

	// Rotates around z first, then x, then z
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatezxz3(T rz1, T rx, T rz2)
	{
		T cz1 = cos(rz1);
		T sz1 = sin(rz1);
		T cx = cos(rx);
		T sx = sin(rx);
		T cz2 = cos(rz2);
		T sz2 = sin(rz2);
		return clmmat<3, 3, T>(
			cz1 * cz2 - cx * sz1 * sz2, -cz2 * sz1 - cx * cz1 * sz2, sx * sz2,
			cz1 * sz2 + cx * cz2 * sz1, cx * cz1 * cz2 - sz1 * sz2, -cz2 * sx,
			sx * sz1, cz1 * sx, cx
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatezxz3(const clmvec<3, T>& vec)
	{
		return mrotatezxz3(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatezxz4(T rz1, T rx, T rz2)
	{
		T cz1 = cos(rz1);
		T sz1 = sin(rz1);
		T cx = cos(rx);
		T sx = sin(rx);
		T cz2 = cos(rz2);
		T sz2 = sin(rz2);
		return clmmat<4, 4, T>(
			cz1 * cz2 - cx * sz1 * sz2, -cz2 * sz1 - cx * cz1 * sz2, sx * sz2, 0,
			cz1 * sz2 + cx * cz2 * sz1, cx * cz1 * cz2 - sz1 * sz2, -cz2 * sx, 0,
			sx * sz1, cz1 * sx, cx, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxz4(const clmvec<3, T>& vec)
	{
		return mrotatezxz4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxz(T rz1, T rx, T rz2)
	{
		return mrotatezxz4(rz1, rx, rz2);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezxz(const clmvec<3, T>& vec)
	{
		return mrotatezxz4(vec);
	}

	// Rotates around z first, then y, then z
	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotatezyz3(T rz1, T ry, T rz2)
	{
		T cz1 = cos(rz1);
		T sz1 = sin(rz1);
		T cy = cos(ry);
		T sy = sin(ry);
		T cz2 = cos(rz2);
		T sz2 = sin(rz2);
		return clmmat<3, 3, T>(
			cy * cz1 * cz2 - sz1 * sz2, -cz1 * sz2 - cy * cz2 * sz1, cz2 * sy,
			cz2 * sz1 + cy * cz1 * sz2, cz1 * cz2 - cy * sz1 * sz2, sy * sz2,
			-cz1 * sy, sy * sz1, cy
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotatezyz3(const clmvec<3, T>& vec)
	{
		return mrotatezyz3(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotatezyz4(T rz1, T ry, T rz2)
	{
		T cz1 = cos(rz1);
		T sz1 = sin(rz1);
		T cy = cos(ry);
		T sy = sin(ry);
		T cz2 = cos(rz2);
		T sz2 = sin(rz2);
		return clmmat<4, 4, T>(
			cy * cz1 * cz2 - sz1 * sz2, -cz1 * sz2 - cy * cz2 * sz1, cz2 * sy, 0,
			cz2 * sz1 + cy * cz1 * sz2, cz1 * cz2 - cy * sz1 * sz2, sy * sz2, 0,
			-cz1 * sy, sy * sz1, cy, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyz4(const clmvec<3, T>& vec)
	{
		return mrotatezyz4(vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyz(T rz1, T ry, T rz2)
	{
		return mrotatezyz4(rz1, ry, rz2);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotatezyz(const clmvec<3, T>& vec)
	{
		return mrotatezyz4(vec);
	}

	*/

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
		return mrotate2(rot);
	}

	//

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<3, 3, T> mrotate3(T rot, T x, T y, T z)
	{
		T c = cos(rot);
		T s = sin(rot);
		T t = 1 - c;
		return clmmat<3, 3, T>(
			t * x * x + c, t * x * y - s * z, t * x * z + s * y,
			t * x * y + s * z, t * y * y + c, t * y * z - s * x,
			t * x * z - s * y, t * y * z + s * x, t * z * z + c
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<3, 3, T> mrotate3(T rot, const clmvec<3, T>& vec)
	{
		return mrotate3(rot, vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr clmmat<4, 4, T> mrotate4(T rot, T x, T y, T z)
	{
		T c = cos(rot);
		T s = sin(rot);
		T t = 1 - c;
		return clmmat<4, 4, T>(
			t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0,
			t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0,
			t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotate4(T rot, const clmvec<3, T>& vec)
	{
		return mrotate4(rot, vec.get(0), vec.get(1), vec.get(2));
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotate(T rot, T x, T y, T z)
	{
		return mrotate4(rot, x, y, z);
	}

	template <typename T = matdefault_t>
		requires arithmetic<T>
	constexpr inline clmmat<4, 4, T> mrotate(T rot, const clmvec<3, T>& vec)
	{
		return mrotate4(rot, vec);
	}

}

#endif