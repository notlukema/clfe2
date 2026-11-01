#ifndef CLFE_CLMATH_MATOP_H
#define CLFE_CLMATH_MATOP_H

#include "mdef.h"
#include "mat.h"
#include "vec.h"
#include "vecop.h"

// Perhaps change Rows, Cols, (Rows == Cols) into a single Size variable?

namespace clfe
{

	// Utility

	// Create a smaller or similar matrix using a larger or similar matrix
	template <clmsize_t Rows1, clmsize_t Cols1, typename T, clmsize_t Rows2, clmsize_t Cols2, typename U>
		requires (Rows1 <= Rows1) && (Cols1 <= Cols2) && (Rows1 > 0) && (Cols1 > 0) && mcompat<T, U>
	constexpr clmmat<Rows1, Cols1, T> mresize(const clmmat<Rows2, Cols2, U>& mat)
	{
		clmmat<Rows1, Cols1, T> result(false);
		for (clmsize_t r = 0; r < Rows1; r++)
		{
			for (clmsize_t c = 0; c < Cols1; c++)
			{
				result.set(r, c, static_cast<T>(mat.get(r, c)));
			}
		}
		return result;
	}

	// Create a smaller or similar matrix using a larger or similar matrix
	// Unused value for compatibility
	template <clmsize_t Rows1, clmsize_t Cols1, typename T, typename V, clmsize_t Rows2, clmsize_t Cols2, typename U>
		requires (Rows1 <= Rows1) && (Cols1 <= Cols2) && (Rows1 > 0) && (Cols1 > 0) && mcompat<T, U>
	constexpr clmmat<Rows1, Cols1, T> mresize(const clmmat<Rows2, Cols2, U>& mat, V val)
	{
		return mresize<Rows1, Cols1, T, V, Rows2, Cols2, U>(mat);
	}

	// Create a larger matrix using a smaller matrix and fill the rest with a value
	// Single case (fill with value)
	template <clmsize_t Rows1, clmsize_t Cols1, typename T, typename V, clmsize_t Rows2, clmsize_t Cols2, typename U>
		requires (Rows1 > Rows2) || (Cols1 > Cols2) && (Rows2 > 0) && (Cols2 > 0) && mcompat<T, U, V>
	constexpr clmmat<Rows1, Cols1, T> mresize(const clmmat<Rows2, Cols2, U>& mat, V val)
	{
		clmmat<Rows1, Cols1, T> result(false);
		clmsize_t r = 0;
		for (; r < size_min(Rows1, Rows2); r++)
		{
			clmsize_t c = 0;
			for (; c < size_min(Cols1, Cols2); c++)
			{
				result.set(r, c, static_cast<T>(mat.get(r, c)));
			}
			if constexpr (Cols1 > Cols2)
			{
				for (; c < Cols1; c++)
				{
					result.set(r, c, static_cast<T>(val));
				}
			}
		}
		if constexpr (Rows1 > Rows2)
		{
			for (; r < Rows1; r++)
			{
				for (clmsize_t c = 0; c < Cols1; c++)
				{
					result.set(r, c, static_cast<T>(val));
				}
			}
		}
		return result;
	}

	// Create a larger matrix using a smaller matrix and fill the rest with a value
	// Empty case (fill with 0)
	template <clmsize_t Rows1, clmsize_t Cols1, typename T, clmsize_t Rows2, clmsize_t Cols2, typename U>
		requires (Rows1 > Rows2) || (Cols1 > Cols2) && (Rows2 > 0) && (Cols2 > 0) && mcompat<T, U> && requires() { static_cast<T>(0); }
	constexpr inline clmmat<Rows1, Cols1, T> mresize(const clmmat<Rows2, Cols2, U>& mat)
	{
		return mresize<Rows1, Cols1, T, T, Rows2, Cols2, U>(mat, static_cast<T>(0));
	}

	// Create a larger matrix using a smaller matrix and extra supplied arguments
	// Variable case (fill with arguments)
	// Fills by row first from left to right
	template <clmsize_t Rows1, clmsize_t Cols1, typename T, clmsize_t Rows2, clmsize_t Cols2, typename U, typename... Args>
		requires ((Rows1 > Rows2) || (Cols1 > Cols2)) && (Rows2 > 0) && (Cols2 > 0) && mcompat<T, U, Args...> && (sizeof...(Args) > 1) &&
		(sizeof...(Args) == size_max(0, Cols1 - Cols2) * size_min(Rows1, Rows2) + size_max(0, Rows1 - Rows2) * Cols1)
	constexpr clmmat<Rows1, Cols1, T> mresize(const clmmat<Rows2, Cols2, U>& mat, Args... args)
	{
			clmmat<Rows1, Cols1, T> result(false);
			for (clmsize_t r = 0; r < size_min(Rows1, Rows2); r++)
			{
				for (clmsize_t c = 0; c < size_min(Cols1, Cols2); c++)
				{
					result.set(r, c, static_cast<T>(mat.get(r, c)));
				}
			}
			clmsize_t r = (Cols1 > Cols2) ? 0 : Rows2;
			clmsize_t c = (Cols1 > Cols2) ? Cols2 : 0;
			(([&](const auto& arg) {
				result.set(r, c, static_cast<T>(arg));
				c++;
				if (c >= Cols1)
				{
					r++;
					c = (r >= Rows2) ? 0 : Cols2;
				}
				}(args)), ...);
			return result;
	}

	// Cast to another matrix type (Note: this function is somewhat redundant)
	template <typename T, clmsize_t Rows, clmsize_t Cols, typename U>
		requires (Rows > 0) && (Cols > 0) &&  mcompat<T, U>
	constexpr inline clmmat<Rows, Cols, T> mcast(const clmmat<Rows, Cols, U>& mat)
	{
		return clmmat<Rows, Cols, T>(mat);
	}

	// Math (non)

	// Operations

	// mat + mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a + b; }
	constexpr auto operator+(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, mat1.get(i) + mat2.get(i));
		}
		return result;
	}

	// mat + val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a + b; }
	constexpr auto operator+(const clmmat<Rows, Cols, T>& mat, U val) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, mat.get(i) + val);
		}
		return result;
	}

	// val + mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a + b; }
	constexpr auto operator+(T val, const clmmat<Rows, Cols, U>& mat) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, val + mat.get(i));
		}
		return result;
	}

	// mat += mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { { a + b } -> mconvert<T>; }
	constexpr clmmat<Rows, Cols, T>& operator+=(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			mat1.set(i, static_cast<T>(mat1.get(i) + mat2.get(i)));
		}
		return mat1;
	}

	// mat += val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { { a + b } -> mconvert<T>; }
	constexpr clmmat<Rows, Cols, T>& operator+=(const clmmat<Rows, Cols, T>& mat, U val)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			mat.set(i, static_cast<T>(mat.get(i) + val));
		}
		return mat;
	}

	// mat - mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a - b; }
	constexpr auto operator-(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, mat1.get(i) - mat2.get(i));
		}
		return result;
	}

	// mat - val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a - b; }
	constexpr auto operator-(const clmmat<Rows, Cols, T>& mat, U val) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, mat.get(i) - val);
		}
		return result;
	}

	// val - mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a + b; }
	constexpr auto operator-(T val, const clmmat<Rows, Cols, U>& mat) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, val - mat.get(i));
		}
		return result;
	}

	// mat -= mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { { a - b } -> mconvert<T>; }
	constexpr clmmat<Rows, Cols, T>& operator-=(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			mat1.set(i, static_cast<T>(mat1.get(i) - mat2.get(i)));
		}
		return mat1;
	}

	// mat -= val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { { a - b } -> mconvert<T>; }
	constexpr clmmat<Rows, Cols, T>& operator-=(const clmmat<Rows, Cols, T>& mat, U val)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			mat.set(i, static_cast<T>(mat.get(i) - val));
		}
		return mat;
	}

	// mat * mat
	template <clmsize_t Rows1, clmsize_t Size, clmsize_t Cols2, typename T, typename U>
		requires (Size > 0) && (Rows1 > 0) && (Cols2 > 0) && arithmetic<T, U>
	constexpr auto operator*(const clmmat<Rows1, Size, T>& mat1, const clmmat<Size, Cols2, U>& mat2) -> clmmat<Rows1, Cols2, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmmat<Rows1, Cols2, decltype(static_cast<T>(0) + static_cast<U>(0))>(false);
		for (clmsize_t r = 0; r < Rows1; r++)
		{
			for (clmsize_t c = 0; c < Cols2; c++)
			{
				decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
				for (clmsize_t k = 0; k < Size; k++)
				{
					sum += mat1.get(r, k) * mat2.get(k, c);
				}
				result.set(r, c, sum);
			}
		}
		return result;
	}

	// mat * val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a * b; }
	constexpr auto operator*(const clmmat<Rows, Cols, T>& mat, U val) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, mat.get(i) * val);
		}
		return result;
	}

	// val * mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a * b; }
	constexpr auto operator*(T val, const clmmat<Rows, Cols, U>& mat) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, val * mat.get(i));
		}
		return result;
	}

	// mat *= mat
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && arithmetic<T, U>
	constexpr clmmat<Size, Size, T>& operator*=(const clmmat<Size, Size, T>& mat1, const clmmat<Size, Size, U>& mat2)
	{
		auto result = mat1 * mat2;
		mat1 = result;
		return mat1;
	}

	// mat *= val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { { a * b } -> mconvert<T>; }
	constexpr clmmat<Rows, Cols, T>& operator*=(const clmmat<Rows, Cols, T>& mat, U val)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			mat.set(i, static_cast<T>(mat.get(i) * val));
		}
		return mat;
	}

	// mat / val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a / b; }
	constexpr auto operator/(const clmmat<Rows, Cols, T>& mat, U val) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) / static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) / static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, mat.get(i) / val);
		}
		return result;
	}

	// val / mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a / b; }
	constexpr auto operator/(T val, const clmmat<Rows, Cols, U>& mat) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) / static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) / static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, val / mat.get(i));
		}
		return result;
	}

	// mat /= val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { { a / b } -> mconvert<T>; }
	constexpr clmmat<Rows, Cols, T>& operator/=(const clmmat<Rows, Cols, T>& mat, U val)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			mat.set(i, static_cast<T>(mat.get(i) / val));
		}
		return mat;
	}

	// mat % val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a % b; }
	constexpr auto operator%(const clmmat<Rows, Cols, T>& mat, U val) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) % static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) % static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, mat.get(i) % val);
		}
		return result;
	}

	// val % mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a % b; }
	constexpr auto operator%(T val, const clmmat<Rows, Cols, U>& mat) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) % static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) % static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, val % mat.get(i));
		}
		return result;
	}

	// mat %= val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { { a % b } -> mconvert<T>; }
	constexpr clmmat<Rows, Cols, T>& operator%=(const clmmat<Rows, Cols, T>& mat, U val)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			mat.set(i, static_cast<T>(mat.get(i) % val));
		}
		return mat;
	}

	// Comparison

	// mat == mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a == b; }
	constexpr bool operator==(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			if (mat1.get(i) == mat2.get(i))
			{
				continue;
			}
			return false;
		}
		return true;
	}

	// mat != mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a == b; }
	constexpr bool operator!=(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2)
	{
		for (clmsize_t i = 0; i < Rows; i++)
		{
			if (mat1.get(i) != mat2.get(i))
			{
				continue;
			}
			return false;
		}
		return true;
	}

}

#endif // CLFE_CLMATH_MATOP_H