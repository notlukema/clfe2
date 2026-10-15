#ifndef CLFE_CLMATH_VEC4_H
#define CLFE_CLMATH_VEC4_H

#include "mdef.h"
#include "mconst.h"
#include "vec.h"

namespace clfe
{

	template <typename T>
	class clmvec<4, T>
	{
	protected:
		T data[4];

	public:
		constexpr clmvec() : data{}
		{}

		template <typename U>
		constexpr explicit clmvec(U scalar) requires mcompat<T, U> : data{ scalar, scalar, scalar, scalar }
		{}

		constexpr clmvec(T x, T y, T z, T w) : data{ x, y, z, w }
		{}

		template <typename U>
		constexpr explicit clmvec(const U* arr) requires mcompat<T, U> : data{ arr[0], arr[1], arr[2], arr[3] }
		{}

		// Copy constructor
		template <typename U>
		constexpr clmvec(const clmvec<4, U>& other) requires mcompat<T, U> : data{ static_cast<T>(other.get(0)), static_cast<T>(other.get(1)), static_cast<T>(other.get(2)), static_cast<T>(other.get(3)) }
		{}

		// Copy assignment
		template <typename U>
		constexpr clmvec<4, T>& operator=(const clmvec<4, U>& other) requires mcompat<T, U>
		{
			data[0] = static_cast<T>(other.get(0));
			data[1] = static_cast<T>(other.get(1));
			data[2] = static_cast<T>(other.get(2));
			data[3] = static_cast<T>(other.get(3));
			return *this;
		}

		//

		constexpr inline clmsize_t size() const
		{
			return static_cast<clmsize_t>(4);
		}

		constexpr inline const T* get() const
		{
			return static_cast<const T*>(data);
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

		constexpr inline T w() const
		{
			return data[3];
		}

		constexpr inline T& wr()
		{
			return data[3];
		}

		constexpr inline void w(T w)
		{
			data[3] = w;
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

		constexpr inline clmvec<2, T> xw() const
		{
			return clmvec<2, T>(data[0], data[3]);
		}

		constexpr inline clmvec<2, T> yz() const
		{
			return clmvec<2, T>(data[1], data[2]);
		}

		constexpr inline clmvec<2, T> yw() const
		{
			return clmvec<2, T>(data[1], data[3]);
		}

		constexpr inline clmvec<2, T> zw() const
		{
			return clmvec<2, T>(data[2], data[3]);
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

		constexpr void xw(T x, T w)
		{
			data[0] = x;
			data[3] = w;
		}

		constexpr void yz(T y, T z)
		{
			data[1] = y;
			data[2] = z;
		}

		constexpr void yw(T y, T w)
		{
			data[1] = y;
			data[3] = w;
		}

		constexpr void zw(T z, T w)
		{
			data[2] = z;
			data[3] = w;
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

		constexpr void xw(const clmvec<2, T>& xw)
		{
			data[0] = xw.get(0);
			data[3] = xw.get(1);
		}

		constexpr void yz(const clmvec<2, T>& yz)
		{
			data[1] = yz.get(0);
			data[2] = yz.get(1);
		}

		constexpr void yw(const clmvec<2, T>& yw)
		{
			data[1] = yw.get(0);
			data[3] = yw.get(1);
		}

		constexpr void zw(const clmvec<2, T>& zw)
		{
			data[2] = zw.get(0);
			data[3] = zw.get(1);
		}

		// By 3

		constexpr inline clmvec<3, T> xyz() const
		{
			return clmvec<3, T>(data[0], data[1], data[2]);
		}

		constexpr inline clmvec<3, T> xyw() const
		{
			return clmvec<3, T>(data[0], data[1], data[3]);
		}

		constexpr inline clmvec<3, T> xzw() const
		{
			return clmvec<3, T>(data[0], data[2], data[3]);
		}

		constexpr inline clmvec<3, T> yzw() const
		{
			return clmvec<3, T>(data[1], data[2], data[3]);
		}

		constexpr void xyz(T x, T y, T z)
		{
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}

		constexpr void xyw(T x, T y, T w)
		{
			data[0] = x;
			data[1] = y;
			data[3] = w;
		}

		constexpr void xzw(T x, T z, T w)
		{
			data[0] = x;
			data[2] = z;
			data[3] = w;
		}

		constexpr void yzw(T y, T z, T w)
		{
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}

		constexpr void xyz(const clmvec<3, T>& xyz)
		{
			data[0] = xyz.get(0);
			data[1] = xyz.get(1);
			data[2] = xyz.get(2);
		}

		constexpr void xyw(const clmvec<3, T>& xyw)
		{
			data[0] = xyw.get(0);
			data[1] = xyw.get(1);
			data[3] = xyw.get(2);
		}

		constexpr void xzw(const clmvec<3, T>& xzw)
		{
			data[0] = xzw.get(0);
			data[2] = xzw.get(1);
			data[3] = xzw.get(2);
		}

		constexpr void yzw(const clmvec<3, T>& yzw)
		{
			data[1] = yzw.get(0);
			data[2] = yzw.get(1);
			data[3] = yzw.get(2);
		}

		// By 4

		constexpr inline clmvec<4, T> xyzw() const
		{
			return clmvec<4, T>(data[0], data[1], data[2], data[3]);
		}

		constexpr void xyzw(T x, T y, T z, T w)
		{
			data[0] = x;
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}

		constexpr void xyzw(const clmvec<4, T>& xyzw)
		{
			data[0] = xyzw.get(0);
			data[1] = xyzw.get(1);
			data[2] = xyzw.get(2);
			data[3] = xyzw.get(3);
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

		constexpr inline T a() const
		{
			return w();
		}

		constexpr inline T& ar()
		{
			return wr();
		}

		constexpr inline void a(T a)
		{
			w(a);
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
		
		constexpr inline clmvec<2, T> ra() const
		{
			return xw();
		}

		constexpr inline clmvec<2, T> gb() const
		{
			return yz();
		}

		constexpr inline clmvec<2, T> ga() const
		{
			return yw();
		}

		constexpr inline clmvec<2, T> ba() const
		{
			return zw();
		}

		constexpr inline void rg(T r, T g)
		{
			xy(r, g);
		}

		constexpr inline void rb(T r, T b)
		{
			xz(r, b);
		}

		constexpr inline void ra(T r, T a)
		{
			xw(r, a);
		}

		constexpr inline void gb(T g, T b)
		{
			yz(g, b);
		}

		constexpr inline void ga(T g, T a)
		{
			yw(g, a);
		}

		constexpr inline void ba(T b, T a)
		{
			zw(b, a);
		}

		constexpr inline void rg(const clmvec<2, T>& rg)
		{
			xy(rg);
		}

		constexpr inline void rb(const clmvec<2, T>& rb)
		{
			xz(rb);
		}

		constexpr inline void ra(const clmvec<2, T>& ra)
		{
			xw(ra);
		}

		constexpr inline void gb(const clmvec<2, T>& gb)
		{
			yz(gb);
		}

		constexpr inline void ga(const clmvec<2, T>& ga)
		{
			yw(ga);
		}

		constexpr inline void ba(const clmvec<2, T>& ba)
		{
			zw(ba);
		}

		// By 3

		constexpr inline clmvec<3, T> rgb() const
		{
			return xyz();
		}

		constexpr inline clmvec<3, T> rga() const
		{
			return xyw();
		}

		constexpr inline clmvec<3, T> rba() const
		{
			return xzw();
		}

		constexpr inline clmvec<3, T> gba() const
		{
			return yzw();
		}

		constexpr inline void rgb(T r, T g, T b)
		{
			xyz(r, g, b);
		}

		constexpr inline void rga(T r, T g, T a)
		{
			xyw(r, g, a);
		}

		constexpr inline void rba(T r, T b, T a)
		{
			xzw(r, b, a);
		}

		constexpr inline void gba(T g, T b, T a)
		{
			yzw(g, b, a);
		}

		constexpr inline void rgb(const clmvec<3, T>& rgb)
		{
			xyz(rgb);
		}

		constexpr inline void rga(const clmvec<3, T>& rga)
		{
			xyw(rga);
		}

		constexpr inline void rba(const clmvec<3, T>& rba)
		{
			xzw(rba);
		}

		constexpr inline void gba(const clmvec<3, T>& gba)
		{
			yzw(gba);
		}

		// By 4

		constexpr inline clmvec<4, T> rgba() const
		{
			return xyzw();
		}

		constexpr inline void rgba(T r, T g, T b, T a)
		{
			xyzw(r, g, b, a);
		}

		constexpr inline void rgba(const clmvec<4, T>& rgba)
		{
			xyzw(rgba);
		}

		//

		template <typename U = T>
		constexpr U dis2() const requires arithmetic_variant1<T, U>
		{
			return static_cast<U>(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]);
		}

		template <typename U = T>
		constexpr U distance() const requires arithmetic_variant1<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			return static_cast<U>(sqrt(dis2<U>()));
		}

		template <typename U = T>
		constexpr clmvec<4, U> normalized() const requires arithmetic_variant1<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			U dist = distance<U>();
			return clmvec<4, U>(static_cast<U>(data[0] / dist), static_cast<U>(data[1] / dist), static_cast<U>(data[2] / dist), static_cast<U>(data[3] / dist));
		}

		constexpr clmvec<4, T>& normalize() requires arithmetic<T> && requires { sqrt(static_cast<T>(0)); }
		{
			T dist = distance<T>();
			data[0] /= dist;
			data[1] /= dist;
			data[2] /= dist;
			data[3] /= dist;
			return *this;
		}

		// 

		template <typename U = T>
		constexpr clmvec<4, U> snormalized(const clmvec<4, U>& exception = clmvec<4, U>(), U d2line = mconst<U>::epsilon()) const requires arithmetic_variant1<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			U d2 = dis2<U>();
			if (d2 < d2line)
			{
				return clmvec<4, U>(exception);
			}

			U dist = static_cast<U>(sqrt(d2));
			return clmvec<4, U>(static_cast<U>(data[0] / dist), static_cast<U>(data[1] / dist), static_cast<U>(data[2] / dist), static_cast<U>(data[3] / dist));
		}

		constexpr clmvec<4, T>& snormalize(const clmvec<4, T>& exception = clmvec<4, T>(), T d2line = mconst<T>::epsilon()) requires arithmetic<T> && requires { sqrt(static_cast<T>(0)); }
		{
			T d2 = dis2<T>();
			if (d2 < d2line)
			{
				data[0] = exception.get(0);
				data[1] = exception.get(1);
				data[2] = exception.get(2);
				data[3] = exception.get(3);
				return *this;
			}

			T dist = static_cast<T>(sqrt(d2));
			data[0] /= dist;
			data[1] /= dist;
			data[2] /= dist;
			data[3] /= dist;
			return *this;
		}

	};

}

#endif // CLFE_CLMATH_VEC4_H