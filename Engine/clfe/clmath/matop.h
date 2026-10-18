#ifndef CLFE_CLMATH_MATOP_H
#define CLFE_CLMATH_MATOP_H

#include "mdef.h"
#include "mat.h"

namespace clfe
{

	// Utility

	// Math

	// Operations

	// mat + mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a + b; }
	constexpr auto operator+(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) - static_cast<U>(0))>();
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
	template <clmsize_t Rows1, clmsize_t Cols1, clmsize_t Rows2, clmsize_t Cols2, typename T, typename U>
		requires (Cols1 == Rows2) && (Cols1 > 0) && arithmetic<T, U>
	constexpr auto operator*(const clmmat<Rows1, Cols1, T>& mat1, const clmmat<Rows2, Cols2, U>& mat2) -> clmmat<Rows1, Cols2, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmmat<Rows1, Cols2, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (clmsize_t r = 0; r < Rows1; r++)
		{
			for (clmsize_t c = 0; c < Cols2; c++)
			{
				decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
				for (clmsize_t k = 0; k < Cols1; k++)
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Rows; i++)
		{
			result.set(i, val * mat.get(i));
		}
		return result;
	}

	// mat *= mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows == Cols) && (Cols > 0) && arithmetic<T, U>
	constexpr clmmat<Rows, Cols, T>& operator*=(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2)
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) / static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) / static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) % static_cast<U>(0))>();
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
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) % static_cast<U>(0))>();
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