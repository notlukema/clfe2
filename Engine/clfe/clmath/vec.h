#ifndef CLFE_CLMATH_VEC_H
#define CLFE_CLMATH_VEC_H

#include "mdef.h"
#include "mconst.h"

namespace clfe
{

	template <clmsize_t Size, typename T>
		requires (Size > 0)
	class clmvec
	{
	protected:
		T data[Size];

	public:
		constexpr clmvec() : data{}
		{}

		template <typename U>
		constexpr explicit clmvec(U scalar) requires mcompat<T, U>
		{
			// No array fill?
			for (clmsize_t i = 0; i < Size; ++i)
			{
				data[i] = static_cast<T>(scalar);
			}
		}

		template <typename... Args>
		constexpr clmvec(Args... args) requires (sizeof...(Args) == Size && mcompat<T, Args...>) : data{ static_cast<T>(args)... }
		{}

		template <typename U>
		constexpr explicit clmvec(const U* arr) requires mcompat<T, U>
		{
			for (clmsize_t i = 0; i < Size; ++i)
			{
				data[i] = static_cast<T>(arr[i]);
			}
		}

		// Copy constructor
		template <typename U>
		constexpr clmvec(const clmvec<Size, U>& other) requires mcompat<T, U>
		{
			for (clmsize_t i = 0; i < Size; ++i)
			{
				data[i] = static_cast<T>(other.get(i));
			}
		}
		
		// Copy assignment
		template <typename U>
		constexpr clmvec<Size, T>& operator=(const clmvec<Size, U>& other) requires mcompat<T, U>
		{
			for (clmsize_t i = 0; i < Size; ++i)
			{
				data[i] = static_cast<T>(other.get(i));
			}
			return *this;
		}
		
		//

		constexpr inline clmsize_t size() const
		{
			return Size;
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

		//

		template <typename U = T>
		constexpr U len2() const requires arithmetic<T, U>
		{
			T sum = static_cast<T>(0);
			for (clmsize_t i = 0; i < Size; ++i)
			{
				sum += data[i] * data[i];
			}
			return static_cast<U>(sum);
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
		constexpr clmvec<Size, U> normalized() const requires floating_point<T, U>
		{
			U invlen = inv_len<U>();
			clmvec<Size, U> result;
			for (clmsize_t i = 0; i < Size; ++i)
			{
				result.data[i] = static_cast<U>(data[i]) * invlen;
			}
			return result;
		}

		constexpr clmvec<Size, T>& normalize() requires floating_point<T>
		{
			T invlen = inv_len<T>();
			for (clmsize_t i = 0; i < Size; ++i)
			{
				data[i] = data[i] * invlen;
			}
			return *this;
		}

		//

		template <typename U = T>
		constexpr clmvec<Size, U> snormalized(const clmvec<Size, U>& ex, U thres2 = mconst<U>::epsilon2()) const requires floating_point<T, U>
		{
			U l2 = len2<U>();
			if (l2 <= thres2)
			{
				return clmvec<Size, U>(ex);
			}

			U invlen = static_cast<U>(1) / static_cast<U>(sqrt(l2));
			clmvec<Size, U> result;
			for (clmsize_t i = 0; i < Size; ++i)
			{
				result.data[i] = static_cast<U>(data[i]) * invlen;
			}
			return result;
		}

		constexpr clmvec<Size, T>& snormalize(const clmvec<Size, T>& ex, T thres2 = _CLFE_DEF_THRES2_VALUE) requires floating_point<T>
		{
			T l2 = len2<T>();
			if (l2 <= thres2)
			{
				for (clmsize_t i = 0; i < Size; ++i)
				{
					data[i] = ex.get(i);
				}
				return *this;
			}

			T invlen = static_cast<T>(1) / static_cast<T>(sqrt(l2));
			for (clmsize_t i = 0; i < Size; ++i)
			{
				data[i] = data[i] * invlen;
			}
			return *this;
		}

	};

}

#endif // CLFE_CLMATH_VEC_H