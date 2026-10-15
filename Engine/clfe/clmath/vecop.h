#ifndef CLFE_CLMATH_VECOP_H
#define CLFE_CLMATH_VECOP_H

#include "mdef.h"
#include "vec.h"

namespace clfe
{

	// Utility

	// Create a smaller or similar vector using a larger or similar vector
	template <clmsize_t Size1, typename T, clmsize_t Size2, typename U>
		requires (Size1 <= Size2) && (Size1 > 0) && mcompat<T, U>
	clmvec<Size1, T> vresize(const clmvec<Size2, U>& vec)
	{
		clmvec<Size1, T> result;
		for (clmsize_t i = 0; i < Size1; i++)
		{
			result.set(i, static_cast<T>(vec.get(i)));
		}
		return result;
	}
	
	// Create a larger vector using a smaller vector and fill the rest with a value
	// Single case (fill with number)
	template <clmsize_t Size1, typename T, clmsize_t Size2, typename U, typename V>
		requires (Size1 > Size2) && (Size2 > 0) && mcompat<T, U, V>
	clmvec<Size1, T> vresize(const clmvec<Size2, U>& vec, V val)
	{
		clmvec<Size1, T> result;
		clmsize_t i = 0;
		for (; i < Size2; i++)
		{
			result.set(i, static_cast<T>(vec.get(i)));
		}
		for (; i < Size1; i++)
		{
			result.set(i, static_cast<T>(val));
		}
		return result;
	}

	// Create a larger vector using a smaller vector and fill the rest with a value
	// Empty case (fill with 0)
	template <clmsize_t Size1, typename T, clmsize_t Size2, typename U>
		requires (Size1 > Size2) && (Size2 > 0) && mcompat<T, U>
	inline clmvec<Size1, T> vresize(const clmvec<Size2, U>& vec)
	{
		return vresize<Size1, T, Size2, U, T>(vec, static_cast<T>(0));
	}

	// Create a larger vector using a smaller vector and extra supplied arguments
	// Filled case (fill with arguments)
	template <clmsize_t Size1, typename T, clmsize_t Size2, typename U, typename... Args>
		requires (Size1 > Size2) && (Size2 > 0) && (sizeof...(Args) == Size1 - Size2) && (sizeof...(Args) > 1) && mcompat<T, U, Args...>
	clmvec<Size1, T> vresize(const clmvec<Size2, U>& vec, Args... args)
	{
		clmvec<Size1, T> result;
		clmsize_t i = 0;
		for (; i < Size2; i++)
		{
			result.set(i, static_cast<T>(vec.get(i)));
		}
		(([&](const auto& arg) {
			result.set(i, static_cast<T>(arg));
			i++;
			}(args)), ...);
		return result;
	}

	// Cast to another vector type (Note: there are so many other ways to do the same thing)
	template <typename T, clmsize_t Size, typename U>
		requires (Size > 0) && mcompat<T, U>
	inline clmvec<Size, T> vcast(const clmvec<Size, U>& vec)
	{
		return clmvec<Size, T>(vec);
	}

	// Math

	// Dot product
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && arithmetic<T> && arithmetic<U> //requires(T a, U b, decltype(static_cast<T>(0) + static_cast<U>(0)) c) { a + b; c * c; }
	auto vdot(const clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2) -> decltype(static_cast<T>(0) * static_cast<U>(0))
	{
		auto result = static_cast<decltype(static_cast<T>(0) * static_cast<U>(0))>(0);
		for (clmsize_t i = 0; i < Size; i++)
		{
			result += vec1.get(i) * vec2.get(i);
		}
		return result;
	}

	// Cross product of size 3
	template <typename T, typename U>
		requires arithmetic<T> && arithmetic<U>
	auto vcross(const clmvec<3, T>& vec1, const clmvec<3, U>& vec2) -> clmvec<3, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		return clmvec<3, decltype(static_cast<T>(0) * static_cast<U>(0))>(
			vec1.get(1) * vec2.get(2) - vec1.get(2) * vec2.get(1),
			vec1.get(2) * vec2.get(0) - vec1.get(0) * vec2.get(2),
			vec1.get(0) * vec2.get(1) - vec1.get(1) * vec2.get(0)
		);
	}

	// Cross product of size 7
	// Note: this function is untested
	template <typename T, typename U>
		requires arithmetic<T> && arithmetic<U>
	auto vcross(const clmvec<7, T>& vec1, const clmvec<7, U>& vec2) -> clmvec<7, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		return clmvec<7, decltype(static_cast<T>(0) * static_cast<U>(0))>(
			vec1.get(1) * vec2.get(2) - vec1.get(2) * vec2.get(1) + vec1.get(3) * vec2.get(6) - vec1.get(6) * vec2.get(3) + vec1.get(4) * vec2.get(5) - vec1.get(5) * vec2.get(4),
			vec1.get(2) * vec2.get(0) - vec1.get(0) * vec2.get(2) + vec1.get(3) * vec2.get(5) - vec1.get(5) * vec2.get(3) + vec1.get(6) * vec2.get(4) - vec1.get(4) * vec2.get(6),
			vec1.get(0) * vec2.get(1) - vec1.get(1) * vec2.get(0) + vec1.get(3) * vec2.get(4) - vec1.get(4) * vec2.get(3) + vec1.get(5) * vec2.get(6) - vec1.get(6) * vec2.get(5),
			vec1.get(6) * vec2.get(0) - vec1.get(0) * vec2.get(6) + vec1.get(5) * vec2.get(1) - vec1.get(1) * vec2.get(5) + vec1.get(4) * vec2.get(2) - vec1.get(2) * vec2.get(4),
			vec1.get(5) * vec2.get(0) - vec1.get(0) * vec2.get(5) + vec1.get(1) * vec2.get(6) - vec1.get(6) * vec2.get(1) + vec1.get(2) * vec2.get(3) - vec1.get(3) * vec2.get(2),
			vec1.get(0) * vec2.get(4) - vec1.get(4) * vec2.get(0) + vec1.get(1) * vec2.get(3) - vec1.get(3) * vec2.get(1) + vec1.get(6) * vec2.get(2) - vec1.get(2) * vec2.get(6),
			vec1.get(0) * vec2.get(3) - vec1.get(3) * vec2.get(0) + vec1.get(4) * vec2.get(1) - vec1.get(1) * vec2.get(4) + vec1.get(2) * vec2.get(5) - vec1.get(5) * vec2.get(2)
		);
	}

	// Operations

	// vec + vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a + b; }
	auto operator+(const clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2) -> clmvec<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, vec1.get(i) + vec2.get(i));
		}
		return result;
	}

	// vec + val
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a + b; }
	auto operator+(const clmvec<Size, T>& vec, U val) -> clmvec<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, vec.get(i) + val);
		}
		return result;
	}

	// val + vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a + b; }
	inline auto operator+(T val, const clmvec<Size, U>& vec) -> clmvec<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, val + vec.get(i));
		}
		return result;
	}

	// vec += vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { { a + b } -> mcompat<T>; }
	clmvec<Size, T>& operator+=(clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			vec1.set(i, static_cast<T>(vec1.get(i) + vec2.get(i)));
		}
		return vec1;
	}

	// vec += val
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { { a + b } -> mcompat<T>; }
	clmvec<Size, T>& operator+=(clmvec<Size, T>& vec, U val)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			vec.set(i, static_cast<T>(vec.get(i) + val));
		}
		return vec;
	}

	// vec - vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a - b; }
	auto operator-(const clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2) -> clmvec<Size, decltype(static_cast<T>(0) - static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) - static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, vec1.get(i) - vec2.get(i));
		}
		return result;
	}

	// vec - val
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a - b; }
	auto operator-(const clmvec<Size, T>& vec, U val) -> clmvec<Size, decltype(static_cast<T>(0) - static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) - static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, vec.get(i) - val);
		}
		return result;
	}

	// val - vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a - b; }
	inline auto operator-(T val, const clmvec<Size, U>& vec) -> clmvec<Size, decltype(static_cast<T>(0) - static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) - static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, val - vec.get(i));
		}
		return result;
	}

	// vec -= vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { { a - b } -> mcompat<T>; }
	clmvec<Size, T>& operator-=(clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			vec1.set(i, static_cast<T>(vec1.get(i) - vec2.get(i)));
		}
		return vec1;
	}

	// vec -= val
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { { a - b } -> mcompat<T>; }
	clmvec<Size, T>& operator-=(clmvec<Size, T>& vec, U val)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			vec.set(i, static_cast<T>(vec.get(i) - val));
		}
		return vec;
	}

	// vec * vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a * b; }
	auto operator*(const clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2) -> clmvec<Size, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) * static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, vec1.get(i) * vec2.get(i));
		}
		return result;
	}

	// vec + val
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a * b; }
	auto operator*(const clmvec<Size, T>& vec, U val) -> clmvec<Size, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) * static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, vec.get(i) * val);
		}
		return result;
	}

	// val * vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a * b; }
	inline auto operator*(T val, const clmvec<Size, U>& vec) -> clmvec<Size, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) * static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, val * vec.get(i));
		}
		return result;
	}

	// vec *= vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { { a * b } -> mcompat<T>; }
	clmvec<Size, T>& operator*=(clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			vec1.set(i, static_cast<T>(vec1.get(i) * vec2.get(i)));
		}
		return vec1;
	}

	// vec *= val
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { { a * b } -> mcompat<T>; }
	clmvec<Size, T>& operator*=(clmvec<Size, T>& vec, U val)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			vec.set(i, static_cast<T>(vec.get(i) * val));
		}
		return vec;
	}

	// vec / vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a / b; }
	auto operator/(const clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2) -> clmvec<Size, decltype(static_cast<T>(0) / static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) / static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, vec1.get(i) / vec2.get(i));
		}
		return result;
	}

	// vec / val
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a / b; }
	auto operator/(const clmvec<Size, T>& vec, U val) -> clmvec<Size, decltype(static_cast<T>(0) / static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) / static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, vec.get(i) / val);
		}
		return result;
	}

	// val / vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a / b; }
	inline auto operator/(T val, const clmvec<Size, U>& vec) -> clmvec<Size, decltype(static_cast<T>(0) / static_cast<U>(0))>
	{
		auto result = clmvec<Size, decltype(static_cast<T>(0) / static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, val / vec.get(i));
		}
		return result;
	}

	// vec /= vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { { a / b } -> mcompat<T>; }
	clmvec<Size, T>& operator/=(clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			vec1.set(i, static_cast<T>(vec1.get(i) / vec2.get(i)));
		}
		return vec1;
	}

	// vec /= val
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { { a / b } -> mcompat<T>; }
	clmvec<Size, T>& operator/=(clmvec<Size, T>& vec, U val)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			vec.set(i, static_cast<T>(vec.get(i) / val));
		}
		return vec;
	}

	// Comparison

	// vec == vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a == b; }
	bool operator==(const clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			if (vec1.get(i) == vec2.get(i))
			{
				continue;
			}
			return false;
		}
		return true;
	}

	// vec != vec
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && requires(T a, U b) { a != b; }
	bool operator!=(const clmvec<Size, T>& vec1, const clmvec<Size, U>& vec2)
	{
		for (clmsize_t i = 0; i < Size; i++)
		{
			if (vec1.get(i) != vec2.get(i))
			{
				continue;
			}
			return false;
		}
		return true;
	}

}

#endif // CLFE_CLMATH_VECOP_H