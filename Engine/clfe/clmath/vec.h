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
			for (clmsize_t i = 0; i < Size; i++)
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
			for (clmsize_t i = 0; i < Size; i++)
			{
				data[i] = static_cast<T>(arr[i]);
			}
		}

		// Copy constructor
		template <typename U>
		constexpr clmvec(const clmvec<Size, U>& other) requires mcompat<T, U>
		{
			for (clmsize_t i = 0; i < Size; i++)
			{
				data[i] = static_cast<T>(other.get(i));
			}
		}

		// Copy assignment
		template <typename U>
		constexpr clmvec<Size, T>& operator=(const clmvec<Size, U>& other) requires mcompat<T, U>
		{
			for (clmsize_t i = 0; i < Size; i++)
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

		//

		template <typename U = T>
		constexpr U dis2() const requires arithmetic_variant1<T, U>
		{
			T sum = static_cast<T>(0);
			for (clmsize_t i = 0; i < Size; i++)
			{
				sum += data[i] * data[i];
			}
			return static_cast<U>(sum);
		}

		template <typename U = T>
		constexpr U distance() const requires arithmetic_variant1<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			return static_cast<U>(sqrt(dis2<U>()));
		}

		template <typename U = T>
		constexpr clmvec<Size, U> normalized() const requires arithmetic_variant1<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			U dist = distance<U>();
			clmvec<Size, U> result;
			for (clmsize_t i = 0; i < Size; i++)
			{
				result.data[i] = static_cast<U>(data[i]) / dist;
			}
			return result;
		}

		constexpr clmvec<Size, T>& normalize() requires arithmetic<T> && requires { sqrt(static_cast<T>(0)); }
		{
			T dist = distance<T>();
			for (clmsize_t i = 0; i < Size; i++)
			{
				data[i] = data[i] / dist;
			}
			return *this;
		}

		// 

		template <typename U = T>
		constexpr clmvec<Size, U> snormalized(const clmvec<Size, U>& exception = clmvec<Size, U>(), U d2line = mconst<U>::epsilon()) const requires arithmetic_variant1<T, U> && requires { sqrt(static_cast<U>(0)); }
		{
			U d2 = dis2<U>();
			if (d2 < d2line)
			{
				return clmvec<Size, U>(exception);
			}

			U dist = static_cast<U>(sqrt(d2));
			clmvec<Size, U> result;
			for (clmsize_t i = 0; i < Size; i++)
			{
				result.data[i] = static_cast<U>(data[i]) / dist;
			}
			return result;
		}

		constexpr clmvec<Size, T>& snormalize(const clmvec<Size, T>& exception = clmvec<Size, T>(), T d2line = mconst<T>::epsilon()) requires arithmetic<T> && requires { sqrt(static_cast<T>(0)); }
		{
			T d2 = dis2<T>();
			if (d2 < d2line)
			{
				for (clmsize_t i = 0; i < Size; i++)
				{
					data[i] = exception.get(i);
				}
				return *this;
			}

			T dist = static_cast<T>(sqrt(d2));
			for (clmsize_t i = 0; i < Size; i++)
			{
				data[i] = data[i] / dist;
			}
			return *this;
		}

	};

}

#endif // CLFE_CLMATH_VEC_H