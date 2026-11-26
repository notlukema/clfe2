#ifndef CLFE_CLMATH_VEC3_H
#define CLFE_CLMATH_VEC3_H

#include "mdef.h"
#include "mconst.h"
#include "vec.h"

namespace clfe
{

	template <typename T>
	class clmvec<3, T>
	{
	protected:
		T data[3];

	public:
		constexpr clmvec() : data{}
		{}

		template <typename U>
		constexpr explicit clmvec(U scalar) requires mcompat<T, U> : data{ scalar, scalar, scalar }
		{}

		constexpr clmvec(T x, T y, T z) : data{ x, y, z }
		{}

		template <typename U>
		constexpr explicit clmvec(const U* arr) requires mcompat<T, U> : data{ arr[0], arr[1], arr[2] }
		{}

		// Copy constructor
		template <typename U>
		constexpr clmvec(const clmvec<3, U>& other) requires mcompat<T, U> : data{ static_cast<T>(other.get(0)), static_cast<T>(other.get(1)), static_cast<T>(other.get(2)) }
		{}

		// Copy assignment
		template <typename U>
		constexpr clmvec<3, T>& operator=(const clmvec<3, U>& other) requires mcompat<T, U>
		{
			data[0] = static_cast<T>(other.get(0));
			data[1] = static_cast<T>(other.get(1));
			data[2] = static_cast<T>(other.get(2));
			return *this;
		}

		//

		constexpr inline clmsize_t size() const
		{
			return static_cast<clmsize_t>(3);
		}

		constexpr inline T* get() const
		{
			return static_cast<T*>(data);
		}

		constexpr inline T& operator[](clmsize_t i)
		{
			return data[i];
		}

		constexpr inline T get(clmsize_t i) const
		{
			return data[i];
		}

		constexpr inline T& getr(clmsize_t i)
		{
			return data[i];
		}

		constexpr inline void set(clmsize_t i, T value)
		{
			data[i] = value;
		}

		// Single accessors

		constexpr inline T x() const
		{
			return data[0];
		}

		constexpr inline T& xr()
		{
			return data[0];
		}

		constexpr inline void x(T x)
		{
			data[0] = x;
		}

		constexpr inline T y() const
		{
			return data[1];
		}

		constexpr inline T& yr()
		{
			return data[1];
		}

		constexpr inline void y(T y)
		{
			data[1] = y;
		}

		constexpr inline T z() const
		{
			return data[2];
		}

		constexpr inline T& zr()
		{
			return data[2];
		}

		constexpr inline void z(T z)
		{
			data[2] = z;
		}

		// By 2

		constexpr inline clmvec<2, T> xy() const
		{
			return clmvec<2, T>(data[0], data[1]);
		}

		constexpr inline clmvec<2, T> xz() const
		{
			return clmvec<2, T>(data[0], data[2]);
		}

		constexpr inline clmvec<2, T> yz() const
		{
			return clmvec<2, T>(data[1], data[2]);
		}

		constexpr void xy(T x, T y)
		{
			data[0] = x;
			data[1] = y;
		}

		constexpr void xz(T x, T z)
		{
			data[0] = x;
			data[2] = z;
		}

		constexpr void yz(T y, T z)
		{
			data[1] = y;
			data[2] = z;
		}

		constexpr void xy(const clmvec<2, T>& xy)
		{
			data[0] = xy.get(0);
			data[1] = xy.get(1);
		}

		constexpr void xz(const clmvec<2, T>& xz)
		{
			data[0] = xz.get(0);
			data[2] = xz.get(1);
		}

		constexpr void yz(const clmvec<2, T>& yz)
		{
			data[1] = yz.get(0);
			data[2] = yz.get(1);
		}

		// By 3

		constexpr inline clmvec<3, T> xyz() const
		{
			return clmvec<3, T>(data[0], data[1], data[2]);
		}

		constexpr void xyz(T x, T y, T z)
		{
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}

		constexpr void xyz(const clmvec<3, T>& xyz)
		{
			data[0] = xyz.get(0);
			data[1] = xyz.get(1);
			data[2] = xyz.get(2);
		}

		// Rgb variant singles

		constexpr inline T r() const
		{
			return x();
		}

		constexpr inline T& rr()
		{
			return xr();
		}

		constexpr inline void r(T r)
		{
			x(r);
		}

		constexpr inline T g() const
		{
			return y();
		}

		constexpr inline T& gr()
		{
			return y();
		}

		constexpr inline void g(T g)
		{
			y(g);
		}

		constexpr inline T b() const
		{
			return z();
		}

		constexpr inline T& br()
		{
			return zr();
		}

		constexpr inline void b(T b)
		{
			z(b);
		}

		// By 2

		constexpr inline clmvec<2, T> rg() const
		{
			return xy();
		}

		constexpr inline clmvec<2, T> rb() const
		{
			return xz();
		}

		constexpr inline clmvec<2, T> gb() const
		{
			return yz();
		}

		constexpr inline void rg(T r, T g)
		{
			xy(r, g);
		}

		constexpr inline void rb(T r, T b)
		{
			xz(r, b);
		}

		constexpr inline void gb(T g, T b)
		{
			yz(g, b);
		}

		constexpr inline void rg(const clmvec<2, T>& rg)
		{
			xy(rg);
		}

		constexpr inline void rb(const clmvec<2, T>& rb)
		{
			xz(rb);
		}

		constexpr inline void gb(const clmvec<2, T>& gb)
		{
			yz(gb);
		}

		// By 3

		constexpr inline clmvec<3, T> rgb() const
		{
			return xyz();
		}

		constexpr inline void rgb(T r, T g, T b)
		{
			xyz(r, g, b);
		}

		constexpr inline void rgb(const clmvec<3, T>& rgb)
		{
			xyz(rgb);
		}

		//

		template <typename U = T>
		constexpr U len2() const requires arithmetic<T, U>
		{
			return static_cast<U>(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
		}

		template <typename U = T>
		constexpr inline U length() const requires arithmetic<T, U>
		{
			return static_cast<U>(sqrt(len2<U>()));
		}

		template <typename U = T>
		constexpr inline U inv_len() const requires floating_point<T, U>
		{
			return static_cast<U>(1) / static_cast<U>(sqrt(len2<U>()));
		}

		template <typename U = T>
		constexpr clmvec<3, U> normalized() const requires floating_point<T, U>
		{
			U invlen = inv_len<U>();
			return clmvec<3, U>(static_cast<U>(data[0] * invlen), static_cast<U>(data[1] * invlen), static_cast<U>(data[2] * invlen));
		}

		constexpr clmvec<3, T>& normalize() requires floating_point<T>
		{
			T invlen = inv_len<T>();
			data[0] *= invlen;
			data[1] *= invlen;
			data[2] *= invlen;
			return *this;
		}

		// 

		template <typename U = T>
		constexpr clmvec<3, U> snormalized(const clmvec<3, U>& ex, U thres2 = mconst<U>::epsilon2()) const requires floating_point<T, U>
		{
			U l2 = len2<U>();
			if (l2 < thres2)
			{
				return clmvec<3, U>(ex);
			}

			U invlen = static_cast<U>(1) / static_cast<U>(sqrt(l2));
			return clmvec<3, U>(static_cast<U>(data[0] * invlen), static_cast<U>(data[1] * invlen), static_cast<U>(data[2] * invlen));
		}

		constexpr clmvec<3, T>& snormalize(const clmvec<3, T>& ex, T thres2 = _CLFE_DEF_THRES2_VALUE) requires floating_point<T>
		{
			T l2 = len2<T>();
			if (l2 < thres2)
			{
				data[0] = ex.get(0);
				data[1] = ex.get(1);
				data[2] = ex.get(2);
				return *this;
			}

			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			data[0] *= invlen;
			data[1] *= invlen;
			data[2] *= invlen;
			return *this;
		}

	};

}

#endif // CLFE_CLMATH_VEC3_H