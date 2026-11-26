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
		constexpr U len2() const requires arithmetic<T, U>
		{
			return static_cast<U>(data[0] * data[0] + data[1] * data[1]);
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
		constexpr clmvec<2, U> normalized() const requires floating_point<T, U>
		{
			U invlen = inv_len<U>();
			return clmvec<2, U>(static_cast<U>(data[0] * invlen), static_cast<U>(data[1] * invlen));
		}

		constexpr clmvec<2, T>& normalize() requires floating_point<T>
		{
			T invlen = inv_len<T>();
			data[0] *= invlen;
			data[1] *= invlen;
			return *this;
		}

		// 

		template <typename U = T>
		constexpr clmvec<2, U> snormalized(const clmvec<2, U>& ex, U thres2 = mconst<U>::epsilon2()) const requires floating_point<T, U>
		{
			U l2 = len2<U>();
			if (l2 <= thres2)
			{
				return clmvec<2, U>(ex);
			}

			U invlen = static_cast<U>(1) / static_cast<U>(sqrt(l2));
			return clmvec<2, U>(static_cast<U>(data[0] * invlen), static_cast<U>(data[1] * invlen));
		}

		constexpr clmvec<2, T>& snormalize(const clmvec<2, T>& ex, T thres2 = _CLFE_DEF_THRES2_VALUE) requires floating_point<T>
		{
			T l2 = len2<T>();
			if (l2 <= thres2)
			{
				data[0] = ex.get(0);
				data[1] = ex.get(1);
				return *this;
			}

			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			data[0] *= invlen;
			data[1] *= invlen;
			return *this;
		}

	};

}

#endif // CLFE_CLMATH_VEC2_H