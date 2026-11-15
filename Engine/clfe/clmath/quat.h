#ifndef CLFE_CLMATH_QUAT_H
#define CLFE_CLMATH_QUAT_H

// Quaternions exist as their own class mainly due to special operations that require them to be treated differently from a classic 4d vector

#include "mdef.h"
#include "mconst.h"
#include "vec.h"

namespace clfe
{

	// Note: quaternions do not normalize themselves, so please call normalize() or snormalize() upon creation using non-unit vectors

	template <typename T>
		requires arithmetic<T>
	class clmquat : public clmvec<4, T>
	{
	public:
		constexpr clmquat() : clmvec<4, T>(0, 0, 0, 1)
		{}

		constexpr clmquat(T x, T y, T z, T w) : clmvec<4, T>(x, y, z, w)
		{}

		template <typename U>
		constexpr explicit clmquat(const U* arr) requires mcompat<T, U> : clmvec<4, T>(arr)
		{}

		// Copy constructor
		template <typename U>
		constexpr clmquat(const clmvec<4, U>& other) requires mcompat<T, U> : clmvec<4, T>(other)
		{}

		// Copy assignment
		template <typename U>
		constexpr clmquat<T>& operator=(const clmvec<4, U>& other) requires mcompat<T, U>
		{
			clmvec<4, T>::data[0] = static_cast<T>(other.get(0));
			clmvec<4, T>::data[1] = static_cast<T>(other.get(1));
			clmvec<4, T>::data[2] = static_cast<T>(other.get(2));
			clmvec<4, T>::data[3] = static_cast<T>(other.get(3));	
			return *this;
		}

		// Override with new default values, though not mandatory (not virtual)

		template <typename U = T>
		constexpr clmvec<4, U> snormalized(const clmvec<4, U>& exception = clmvec<4, U>(0, 0, 0, 1), U d2line = mconst<U>::epsilon()) const requires arithmetic<U> && requires { sqrt(static_cast<U>(0)); }
		{
			return clmvec<4, T>::template snormalized<U>(exception, d2line);
		}

		constexpr clmvec<4, T>& snormalize(const clmvec<4, T>& exception = clmvec<4, T>(0, 0, 0, 1), T d2line = mconst<T>::epsilon()) requires requires { sqrt(static_cast<T>(0)); }
		{
			return clmvec<4, T>::snormalize(exception, d2line);
		}

	};

}

#endif // CLFE_CLMATH_QUAT_H