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
		for (clmsize_t r = 0; r < Rows1; ++r)
		{
			for (clmsize_t c = 0; c < Cols1; ++c)
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
		for (; r < size_min(Rows1, Rows2); ++r)
		{
			clmsize_t c = 0;
			for (; c < size_min(Cols1, Cols2); ++c)
			{
				result.set(r, c, static_cast<T>(mat.get(r, c)));
			}
			if constexpr (Cols1 > Cols2)
			{
				for (; c < Cols1; ++c)
				{
					result.set(r, c, static_cast<T>(val));
				}
			}
		}
		if constexpr (Rows1 > Rows2)
		{
			for (; r < Rows1; ++r)
			{
				for (clmsize_t c = 0; c < Cols1; ++c)
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
			for (clmsize_t r = 0; r < size_min(Rows1, Rows2); ++r)
			{
				for (clmsize_t c = 0; c < size_min(Cols1, Cols2); ++c)
				{
					result.set(r, c, static_cast<T>(mat.get(r, c)));
				}
			}
			clmsize_t r = (Cols1 > Cols2) ? 0 : Rows2;
			clmsize_t c = (Cols1 > Cols2) ? Cols2 : 0;
			(([&](const auto& arg) {
				result.set(r, c, static_cast<T>(arg));
				++c;
				if (c >= Cols1)
				{
					++r;
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

	//

	// Identity matrix
	template <clmsize_t Size, typename T>
		requires (Size > 0) && arithmetic<T>
	constexpr clmmat<Size, Size, T> midentity()
	{
		return clmmat<Size, Size, T>(true);
	}

	// Transpose a matrix
	template <clmsize_t Rows, clmsize_t Cols, typename T, clmsize_t Size0>
		requires (Rows > 0) && (Cols > 0) && arithmetic<T>
	constexpr clmmat<Cols, Rows, T> mtranspose(const clmmat<Rows, Cols, T>& mat)
	{
		clmmat<Cols, Rows, T> result;
		for (clmsize_t r = 0; r < Rows; ++r)
		{
			for (clmsize_t c = 0; c < Cols; ++c)
			{
				result.set(c, r, mat.get(r, c));
			}
		}
		return result;
	}
	
	// Helper used to calculate determinants
	template <clmsize_t Size, typename T, clmsize_t Size0>
		requires (Size > 0) && arithmetic<T>
	constexpr T mdet_helper(const clmmat<Size, Size, T>& mat, const clmsize_t(&r)[Size0], const clmsize_t(&c)[Size0])
	{
		if constexpr (Size0 == 1)
		{
			return static_cast<T>(mat.get(r[0], c[0]));
		}
		else if constexpr (Size0 == 2)
		{
			return static_cast<T>(mat.get(r[0], c[0])) * static_cast<T>(mat.get(r[1], c[1])) - static_cast<T>(mat.get(r[0], c[1])) * static_cast<T>(mat.get(r[1], c[0]));
		}
		else
		{
			T sum = static_cast<T>(0);
			T flip = static_cast<T>(1);
			clmsize_t r2[Size0 - 1] = {};
			for (clmsize_t i = 0; i < Size0 - 1; ++i)
			{
				r2[i] = r[i + 1];
			}
			for (clmsize_t i = 0; i < Size0; ++i)
			{
				clmsize_t c2[Size0 - 1] = {};
				for (clmsize_t k = 0, j = 0; k < Size0 - 1; ++k)
				{
					if (j == i)
					{
						++j;
					}
					c2[k] = c[j];
					++j;
				}
				sum += flip * static_cast<T>(mat.get(r[0], c[i])) * mdet_helper<Size, T, Size0 - 1>(mat, r2, c2);
				flip = static_cast<T>(0) - flip;
			}
			return sum;
		}
	}

	// Calculate the determinant of a matrix
	template <clmsize_t Size, typename T>
		requires (Size > 0) && arithmetic<T>
	constexpr T mdeterminant(const clmmat<Size, Size, T>& mat)
	{
		clmsize_t ra[Size] = {};
		clmsize_t ca[Size] = {};
		for (clmsize_t i = 0; i < Size; ++i)
		{
			ra[i] = i;
			ca[i] = i;
		}
		return mdet_helper<Size, T, Size>(mat, ra, ca);
	}

	// Calculate the minor of a matrix
	template <clmsize_t Size, typename T>
		requires (Size > 0) && arithmetic<T>
	constexpr T mminor(const clmmat<Size, Size, T>& mat, clmsize_t r, clmsize_t c)
	{
		clmsize_t ra[Size - 1] = {};
		clmsize_t ca[Size - 1] = {};
		clmsize_t r1 = 0;
		clmsize_t c1 = 0;
		for (clmsize_t i = 0; i < Size - 1; ++i)
		{
			if (r1 == r)
			{
				++r1;
			}
			if (c1 == c)
			{
				++c1;
			}
			ra[i] = r1;
			ca[i] = c1;
			++r1;
			++c1;
		}
		return mdet_helper<Size, T, Size - 1>(mat, ra, ca);
	}

	// Calculate the cofactor of a matrix
	// This calculation is crazy expensive for matrices larger than 3x3
	template <clmsize_t Size, typename T>
		requires (Size > 0) && arithmetic<T>
	constexpr clmmat<Size, Size, T> mcofactor(const clmmat<Size, Size, T>& mat)
	{
		clmmat<Size, Size, T> result;
		clmsize_t ra[Size - 1] = {};
		for (clmsize_t i = 0; i < Size - 1; ++i)
		{
			ra[i] = i + 1;
		}
		T flip = static_cast<T>(-1);
		for (clmsize_t r = 0; r < Size; ++r)
		{
			clmsize_t ca[Size - 1] = {};
			for (clmsize_t i = 0; i < Size - 1; ++i)
			{
				ca[i] = i + 1;
			}
			T flip2 = static_cast<T>(0) - flip;
			for (clmsize_t c = 0; c < Size; ++c)
			{
				result.set(r, c, flip2 * mdet_helper<Size, T, Size - 1>(mat, ra, ca));
				flip2 = static_cast<T>(0) - flip2;
				if (c < Size - 1)
				{
					--ca[c];
				}
			}
			flip = static_cast<T>(0) - flip;
			if (r < Size - 1)
			{
				--ra[r];
			}
		}
		return result;
	}

	// Calculate the adjoint of a matrix
	// This calculation is crazy expensive for matrices larger than 3x3
	template <clmsize_t Size, typename T>
		requires (Size > 0) && arithmetic<T>
	constexpr inline clmmat<Size, Size, T> madjoint(const clmmat<Size, Size, T>& mat) requires arithmetic<T>
	{
		return mcofactor<Size, T>(mat).transpose();
	}

	// Calculate the inverse with a pre-determined determinant
	// This calculation is crazy expensive for matrices larger than 3x3
	template <clmsize_t Size, typename T>
		requires (Size > 0) && arithmetic<T>
	constexpr clmmat<Size, Size, T> minverse(const clmmat<Size, Size, T>& mat, T det)
	{
		T invdet = static_cast<T>(1) / det;
		clmmat<Size, Size, T> result;
		clmsize_t ra[Size - 1] = {};
		for (clmsize_t i = 0; i < Size - 1; ++i)
		{
			ra[i] = i + 1;
		}
		T flip = static_cast<T>(-1);
		for (clmsize_t r = 0; r < Size; ++r)
		{
			clmsize_t ca[Size - 1] = {};
			for (clmsize_t i = 0; i < Size - 1; ++i)
			{
				ca[i] = i + 1;
			}
			T flip2 = static_cast<T>(0) - flip;
			for (clmsize_t c = 0; c < Size; ++c)
			{
				result.set(r, c, flip2 * mdet_helper<Size, T, Size - 1>(mat, ra, ca) * invdet);
				flip2 = static_cast<T>(0) - flip2;
				if (c < Size - 1)
				{
					--ca[c];
				}
			}
			flip = static_cast<T>(0) - flip;
			if (r < Size - 1)
			{
				--ra[r];
			}
		}
		return result.transpose();
	}

	// Calculate the inverse of a matrix (no checks)
	// This calculation is crazy expensive for matrices larger than 3x3
	template <clmsize_t Size, typename T>
		requires (Size > 0) && arithmetic<T>
	constexpr inline clmmat<Size, Size, T> minverse(const clmmat<Size, Size, T>& mat)
	{
		return minverse<Size, T>(mat, mdeterminant<Size, T>(mat));
	}

	// Calculate the inverse of a matrix (with checks)
	// This calculation is crazy expensive for matrices larger than 3x3
	template <clmsize_t Size, typename T>
		requires (Size > 0) && arithmetic<T>
	constexpr inline clmmat<Size, Size, T> msinverse(const clmmat<Size, Size, T>& mat)
	{
		T det = mdeterminant<Size, T>(mat);
		if (det == 0)
		{
			return midentity<Size, T>();
		}
		return minverse<Size, T>(mat, det);
	}

	// Operations

	// mat + mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a + b; }
	constexpr auto operator+(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
		{
			mat.set(i, static_cast<T>(mat.get(i) - val));
		}
		return mat;
	}

	// Matrix multiplication
	template <clmsize_t Rows1, clmsize_t Size, clmsize_t Cols2, typename T, typename U>
		requires (Size > 0) && (Rows1 > 0) && (Cols2 > 0) && arithmetic<T, U>
	constexpr auto mmul(const clmmat<Rows1, Size, T>& mat1, const clmmat<Size, Cols2, U>& mat2) -> clmmat<Rows1, Cols2, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmmat<Rows1, Cols2, decltype(static_cast<T>(0) + static_cast<U>(0))>(false);
		for (clmsize_t r = 0; r < Rows1; ++r)
		{
			for (clmsize_t c = 0; c < Cols2; ++c)
			{
				decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
				for (clmsize_t k = 0; k < Size; ++k)
				{
					sum += mat1.get(r, k) * mat2.get(k, c);
				}
				result.set(r, c, sum);
			}
		}
		return result;
	}

	// mat * mat
	template <clmsize_t Rows1, clmsize_t Size, clmsize_t Cols2, typename T, typename U>
		requires (Size > 0) && (Rows1 > 0) && (Cols2 > 0) && arithmetic<T, U>
	constexpr inline auto operator*(const clmmat<Rows1, Size, T>& mat1, const clmmat<Size, Cols2, U>& mat2) -> clmmat<Rows1, Cols2, decltype(static_cast<T>(0)* static_cast<U>(0))>
	{
		return mmul<Rows1, Size, Cols2, T, U>(mat1, mat2);
	}

	// mat * val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a * b; }
	constexpr auto operator*(const clmmat<Rows, Cols, T>& mat, U val) -> clmmat<Rows, Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>(false);
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
		{
			result.set(i, val * mat.get(i));
		}
		return result;
	}

	// mat *= mat
	// Equals mat1 = mat2 * mat1
	template <clmsize_t Size, typename T, typename U>
		requires (Size > 0) && arithmetic<T, U>
	constexpr clmmat<Size, Size, T>& operator*=(const clmmat<Size, Size, T>& mat1, const clmmat<Size, Size, U>& mat2)
	{
		mat1 = mmul<Size, Size, Size, U, T>(mat2, mat1);
		return mat1;
	}

	// mat *= val
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { { a * b } -> mconvert<T>; }
	constexpr clmmat<Rows, Cols, T>& operator*=(const clmmat<Rows, Cols, T>& mat, U val)
	{
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
		{
			mat.set(i, static_cast<T>(mat.get(i) % val));
		}
		return mat;
	}

	// Negation

	// -mat
	template <clmsize_t Rows, clmsize_t Cols, typename T>
		requires (Rows > 0) && (Cols > 0) && requires(T a) { -a; }
	constexpr auto operator-(const clmmat<Rows, Cols, T>& mat) -> clmmat<Rows, Cols, decltype(-static_cast<T>(0))>
	{
		auto result = clmmat<Rows, Cols, decltype(-static_cast<T>(0))>(false);
		for (clmsize_t i = 0; i < Rows; ++i)
		{
			result.set(i, -mat.get(i));
		}
		return result;
	}

	// Comparison

	// mat == mat
	template <clmsize_t Rows, clmsize_t Cols, typename T, typename U>
		requires (Rows > 0) && (Cols > 0) && requires(T a, U b) { a == b; }
	constexpr bool operator==(const clmmat<Rows, Cols, T>& mat1, const clmmat<Rows, Cols, U>& mat2)
	{
		for (clmsize_t i = 0; i < Rows; ++i)
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
		for (clmsize_t i = 0; i < Rows; ++i)
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