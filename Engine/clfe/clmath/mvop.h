#ifndef CLFE_CLMATH_MVOP_H
#define CLFE_CLMATH_MVOP_H

#include "mdef.h"
#include "vec.h"
#include "mat.h"

namespace clfe
{

	// Cast matrix to vector
	template <typename T, clmsize_t Size, typename U>
		requires (Size > 0) && mcompat<T, U>
	constexpr inline clmvec<Size, T> mvcast(const clmmat<Size, 1, U>& mat)
	{
		return clmvec<Size, T>(mat.get(0));
	}

	// Cast matrix to vector
	// (same type case)
	template <clmsize_t Size, typename T>
		requires (Size > 0)
	constexpr inline clmvec<Size, T> mvcast(const clmmat<Size, 1, T>& mat)
	{
		return mvcast<T, Size, T>(mat);
	}

	// Cast matrix to vector
	template <typename T, clmsize_t Size, typename U>
		requires (Size > 0) && mcompat<T, U>
	constexpr clmvec<Size, T> mvcast(const clmmat<1, Size, U>& mat)
	{
		clmvec<Size, T> result;
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, static_cast<T>(mat.get(0, i)));
		}
		return result;
	}

	// Cast matrix to vector
	// (same type case)
	template <clmsize_t Size, typename T>
		requires (Size > 0)
	constexpr inline clmvec<Size, T> mvcast(const clmmat<1, Size, T>& mat)
	{
		return mvcast<T, Size, T>(mat);
	}

	// Cast vector to matrix (row major)
	template <typename T, clmsize_t Size, typename U>
		requires (Size > 0) && mcompat<T, U>
	constexpr clmmat<1, Size, T> mvcastr(const clmvec<Size, U>& vec)
	{
		clmmat<1, Size, T> result;
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(0, i, static_cast<T>(vec.get(i)));
		}
		return result;
	}

	// Cast vector to matrix (row major)
	// (same type case)
	template <clmsize_t Size, typename T>
		requires (Size > 0)
	constexpr inline clmmat<1, Size, T> mvcastr(const clmvec<Size, T>& vec)
	{
		return mvcastr<T, Size, T>(vec);
	}

	// Cast vector to matrix (column major)
	template <typename T, clmsize_t Size, typename U>
		requires (Size > 0) && mcompat<T, U>
	constexpr clmmat<Size, 1, T> mvcastc(const clmvec<Size, U>& vec)
	{
		clmmat<Size, 1, T> result;
		for (clmsize_t i = 0; i < Size; i++)
		{
			result.set(i, 0, static_cast<T>(vec.get(i)));
		}
		return result;
	}

	// Cast vector to matrix (column major)
	// (same type case)
	template <clmsize_t Size, typename T>
		requires (Size > 0)
	constexpr inline clmmat<Size, 1, T> mvcastc(const clmvec<Size, T>& vec)
	{
		return mvcastc<T, Size, T>(vec);
	}

	// Cast vector to matrix (default row major)
	template <typename T, clmsize_t Size, typename U>
		requires (Size > 0) && mcompat<T, U>
	constexpr inline clmmat<1, Size, T> mvcast(const clmvec<Size, U>& vec)
	{
		return mvcastr<T, Size, U>(vec);
	}

	// Cast vector to matrix (default row major)
	// (same type case)
	template <clmsize_t Size, typename T>
		requires (Size > 0)
	constexpr inline clmmat<1, Size, T> mvcast(const clmvec<Size, T>& vec)
	{
		return mvcast<T, Size, T>(vec);
	}

	// Operations

#if defined (_CLFE_CLMATH_FLIP_VECTOR_MATRIX_MUL)

	// vec * mat
	template <clmsize_t Size, clmsize_t Rows, typename T, typename U>
		requires (Size > 0) && (Rows > 0) && arithmetic<T, U>
	constexpr auto operator*(const clmvec<Size, T>& vec, const clmmat<Rows, Size, U>& mat) -> clmvec<Rows, decltype(static_cast<T>(0)* static_cast<U>(0))>
	{
		auto result = clmvec<Rows, decltype(static_cast<T>(0) * static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Rows; i++)
		{
			decltype(static_cast<T>(0) * static_cast<U>(0)) sum = 0;
			for (clmsize_t c = 0; c < Size; c++)
			{
				sum += vec.get(i) * mat.get(i, c);
			}
			result.set(i, sum);
		}
		return result;
	}

	// mat * vec
	template <clmsize_t Size, clmsize_t Cols, typename T, typename U>
		requires (Size > 0) && (Cols > 0) && arithmetic<T, U>
	constexpr auto operator*(const clmmat<Size, Cols, T>& mat, const clmvec<Size, U>& vec) -> clmvec<Cols, decltype(static_cast<T>(0)* static_cast<U>(0))>
	{
		auto result = clmvec<Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Cols; i++)
		{
			decltype(static_cast<T>(0) * static_cast<U>(0)) sum = 0;
			for (clmsize_t r = 0; r < Size; r++)
			{
				sum += vec.get(i) * mat.get(r, i);
			}
			result.set(i, sum);
		}
		return result;
	}

#else

	// vec * mat
	template <clmsize_t Size, clmsize_t Cols, typename T, typename U>
		requires (Size > 0) && (Cols > 0) && arithmetic<T, U>
	constexpr auto operator*(const clmvec<Size, T>& vec, const clmmat<Size, Cols, U>& mat) -> clmvec<Cols, decltype(static_cast<T>(0)* static_cast<U>(0))>
	{
		auto result = clmvec<Cols, decltype(static_cast<T>(0) * static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Cols; i++)
		{
			decltype(static_cast<T>(0) * static_cast<U>(0)) sum = 0;
			for (clmsize_t r = 0; r < Size; r++)
			{
				sum += vec.get(i) * mat.get(r, i);
			}
			result.set(i, sum);
		}
		return result;
	}

	// mat * vec
	template <clmsize_t Size, clmsize_t Rows, typename T, typename U>
		requires (Size > 0) && (Rows > 0) && arithmetic<T, U>
	constexpr auto operator*(const clmmat<Rows, Size, T>& mat, const clmvec<Size, U>& vec) -> clmvec<Rows, decltype(static_cast<T>(0)* static_cast<U>(0))>
	{
		auto result = clmvec<Rows, decltype(static_cast<T>(0) * static_cast<U>(0))>();
		for (clmsize_t i = 0; i < Rows; i++)
		{
			decltype(static_cast<T>(0) * static_cast<U>(0)) sum = 0;
			for (clmsize_t c = 0; c < Size; c++)
			{
				sum += vec.get(i) * mat.get(i, c);
			}
			result.set(i, sum);
		}
		return result;
	}

#endif

}

#endif // CLFE_CLMATH_MVOP_H