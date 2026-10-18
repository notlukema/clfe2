#ifndef CLFE_CLMATH_VEC2_H
#define CLFE_CLMATH_VEC2_H

#include "mdef.h"
#include "mconst.h"
#include "vec.h"

namespace clfe
{
	
	template <typename T>
	class clmvec<2, T>
	{
	protected:
		T data[2];

	public:
		constexpr clmvec() : data{}
		{}

		template <typename U>
		constexpr explicit clmvec(U scalar) requires mcompat<T, U> : data{ scalar, scalar }
		{}

		constexpr clmvec(T x, T y) : data{ x, y }
		{}

		template <typename U>
		constexpr explicit clmvec(const U* arr) requires mcompat<T, U> : data{ arr[0], arr[1] }
		{}

		// Copy constructor
		template <typename U>
		constexpr clmvec(const clmvec<2, U>& other) requires mcompat<T, U> : data{ static_cast<T>(other.get(0)), static_cast<T>(other.get(1)) }
		{}

		// Copy assignment
		template <typename U>
		constexpr clmvec<2, T>& operator=(const clmvec<2, U>& other) requires mcompat<T, U>
		{
			data[0] = static_cast<T>(other.get(0));
			data[1] = static_cast<T>(other.get(1));
			return *this;
		}

		//

		constexpr inline clmsize_t size() const
		{
			return static_cast<clmsize_t>(2);
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

		// By 2

		constexpr inline clmvec<2, T> xy() const
		{
			return clmvec<2, T>(data[0], data[1]);
		}

		constexpr void xy(T x, T y)
		{
			data[0] = x;
			data[1] = y;
		}

		constexpr void xy(const clmvec<2, T>& xy)
		{
			data[0] = xy.get(0);
			data[1] = xy.get(1);
		}

		//

		template <typename U = T>
		constexpr U dis2() const requires arithmetic<T, U>
		{
			return static_cast<U>(data[0] * data[0] + data[1] * data[1]);
		}

		template <typename U = T>
		constexpr inline U distance() const requires arithmetic<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			return static_cast<U>(sqrt(dis2<U>()));
		}

		template <typename U = T>
		constexpr clmvec<2, U> normalized() const requires arithmetic<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			U dist = distance<U>();
			return clmvec<2, U>(static_cast<U>(data[0] / dist), static_cast<U>(data[1] / dist));
		}

		constexpr clmvec<2, T>& normalize() requires arithmetic<T> && requires { sqrt(static_cast<T>(0)); }
		{
			T dist = distance<T>();
			data[0] /= dist;
			data[1] /= dist;
			return *this;
		}

		// 

		template <typename U = T>
		constexpr clmvec<2, U> snormalized(const clmvec<2, U>& exception = clmvec<2, U>(), U d2line = mconst<U>::epsilon()) const requires arithmetic<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			U d2 = dis2<U>();
			if (d2 < d2line)
			{
				return clmvec<2, U>(exception);
			}

			U dist = static_cast<U>(sqrt(d2));
			return clmvec<2, U>(static_cast<U>(data[0] / dist), static_cast<U>(data[1] / dist));
		}

		constexpr clmvec<2, T>& snormalize(const clmvec<2, T>& exception = clmvec<2, T>(), T d2line = mconst<T>::epsilon()) requires arithmetic<T> && requires { sqrt(static_cast<T>(0)); }
		{
			T d2 = dis2<T>();
			if (d2 < d2line)
			{
				data[0] = exception.get(0);
				data[1] = exception.get(1);
				return *this;
			}

			T dist = static_cast<T>(sqrt(d2));
			data[0] /= dist;
			data[1] /= dist;
			return *this;
		}

	};

}

#endif // CLFE_CLMATH_VEC2_H