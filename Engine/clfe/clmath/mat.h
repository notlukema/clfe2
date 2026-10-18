#ifndef CLFE_CLMATH_MAT_H
#define CLFE_CLMATH_MAT_H

#include "mdef.h"
#include "mconst.h"
#include "vec.h"

namespace clfe
{

	// Row major
	template <clmsize_t Rows, clmsize_t Cols, typename T>
		requires (Rows > 0) && (Cols > 0)
	class clmmat
	{
	protected:
		using D_t = clmvec<Cols, T>;
		D_t data[Rows];

	public:
		constexpr clmmat() requires !arithmetic<T> : data{}
		{}

		constexpr explicit clmmat(bool identity = false) requires arithmetic<T> && (Rows != Cols) : data{}
		{}

		constexpr explicit clmmat(bool identity = true) requires arithmetic<T> && (Rows == Cols) : data{}
		{
			if (identity)
			{
				for (clmsize_t i = 0; i < Rows; i++)
				{
					data[i].set(i, static_cast<T>(1));
				}
			}
		}

		// iscalar = identity scalar (default 1 for square matrices)
		constexpr explicit clmmat(T iscalar) requires !msame<T, bool>&& arithmetic<T> && (Rows == Cols) : data{}
		{
			for (clmsize_t i = 0; i < Rows; i++)
			{
				data[i].set(i, iscalar);
			}
		}

		template <typename... Args>
		constexpr clmmat(Args... args) requires (sizeof...(Args) == Rows * Cols) && mcompat<T, Args...>
		{
			T temp[] = { static_cast<T>(args)... };
			for (clmsize_t r = 0; r < Rows; r++)
			{
				for (clmsize_t c = 0; c < Cols; c++)
				{
					data[r].set(c, temp[r * Cols + c]);
				}
			}
			/*
			clmsize_t r = 0;
			clmsize_t c = 0;
			(([&](const auto& arg) {
				data[r].set(c, static_cast<T>(arg));
				c++;
				if (c >= Cols)
				{
					c = 0;
					r++;
				}
				}(args)), ...);
			*/
		}

		template <typename U>
		constexpr explicit clmmat(const U* arr) requires mcompat<T, U>
		{
			for (clmsize_t r = 0; r < Rows; r++)
			{
				for (clmsize_t c = 0; c < Cols; c++)
				{
					data[r].set(c, arr[r * Cols + c]);
				}
			}
		}

		// Copy constructor
		template <typename U>
		constexpr clmmat(const clmmat<Rows, Cols, U>& other) requires mcompat<T, U>
		{
			for (clmsize_t r = 0; r < Rows; r++)
			{
				data[r] = other.get(r);
			}
		}

		// Copy assignment
		template <typename U>
		constexpr clmmat<Rows, Cols, U>& operator=(const clmmat<Rows, Cols, U>& other) requires mcompat<T, U>
		{
			for (clmsize_t r = 0; r < Rows; r++)
			{
				data[r] = other.get(r);
			}
			return *this;
		}

		//

		constexpr inline clmsize_t rows() const
		{
			return Rows;
		}

		constexpr inline clmsize_t cols() const
		{
			return Cols;
		}

		constexpr inline D_t* get()
		{
			return static_cast<D_t*>(data);
		}

		constexpr inline D_t& operator[](clmsize_t i)
		{
			return data[i];
		}

		constexpr inline D_t get(clmsize_t i) const
		{
			return data[i];
		}

		constexpr inline D_t& getr(clmsize_t i)
		{
			return data[i];
		}

		constexpr inline T get(clmsize_t r, clmsize_t c) const
		{
			return data[r].get(c);
		}

		constexpr inline T& getr(clmsize_t r, clmsize_t c)
		{
			return data[r].get(c);
		}

		constexpr inline void set(clmsize_t i, D_t row)
		{
			data[i] = row;
		}

		constexpr inline void set(clmsize_t r, clmsize_t c, T value)
		{
			data[r].set(c, value);
		}

		//

		template <typename U = T>
		constexpr clmmat<Cols, Rows, U> transposed() const requires mcompat<T, U>
		{
			clmmat<Cols, Rows, U> result;
			for (clmsize_t r = 0; r < Rows; r++)
			{
				for (clmsize_t c = 0; c < Cols; c++)
				{
					result.data[c].set(r, data[r].get(c));
				}
			}
			return result;
		}

		constexpr clmmat<Rows, Cols, T>& transpose() requires (Rows == Cols) && (Rows > 1)
		{
			for (clmsize_t r = 1; r < Rows; r++)
			{
				for (clmsize_t c = 0; c < r; c++)
				{
					T temp = data[r].get(c);
					data[r].set(c, data[c].get(r));
					data[c].set(r, temp);
				}
			}
			return *this;
		}

	private:
		// The row only moves downwards
		template <typename U, clmsize_t Size>
		constexpr U detHelper(clmsize_t r, const clmsize_t (&c)[Size])
		{
			if constexpr (Size == 1)
			{
				return static_cast<U>(get(r, c[0]));
			}
			else if constexpr (Size == 2)
			{
				return static_cast<U>(get(r, c[0])) * static_cast<U>(get(r + 1, c[1])) - static_cast<U>(get(r, c[1])) * static_cast<U>(get(r + 1, c[0]));
			}
			else
			{
				U sum = static_cast<U>(0);
				U flip = static_cast<U>(1);
				for (clmsize_t i = 0; i < Size; i++)
				{
					clmsize_t c2[Size - 1] = {};
					for (clmsize_t k = 0, j = 0; k < Size - 1; k++)
					{
						if (j == i)
						{
							j++;
						}
						c2[k] = c[j];
						j++;
					}
					sum += flip * static_cast<U>(get(r, c[i])) * detHelper<U, Size - 1>(r + 1, c2);
					flip = static_cast<U>(0) - flip;
				}
				return sum;
			}
		}

		// The row only moves downwards but can be initially custom set
		template <typename U, clmsize_t Size>
		constexpr U detHelper2(const clmsize_t (&r)[Size], const clmsize_t(&c)[Size])
		{
			if constexpr (Size == 1)
			{
				return static_cast<U>(get(r[0], c[0]));
			}
			else if constexpr (Size == 2)
			{
				return static_cast<U>(get(r[0], c[0])) * static_cast<U>(get(r[1], c[1])) - static_cast<U>(get(r[0], c[1])) * static_cast<U>(get(r[1], c[0]));
			}
			else
			{
				U sum = static_cast<U>(0);
				U flip = static_cast<U>(1);
				clmsize_t r2[Size - 1] = {};
				for (clmsize_t i = 0; i < Size - 1; i++)
				{
					r2[i] = r[i + 1];
				}
				for (clmsize_t i = 0; i < Size; i++)
				{
					clmsize_t c2[Size - 1] = {};
					for (clmsize_t k = 0, j = 0; k < Size - 1; k++)
					{
						if (j == i)
						{
							j++;
						}
						c2[k] = c[j];
						j++;
					}
					sum += flip * static_cast<U>(get(r[0], c[i])) * detHelper2<U, Size - 1>(r2, c2);
					flip = static_cast<U>(0) - flip;
				}
				return sum;
			}
		}

	public:
		template <typename U = T>
		constexpr U determinant() requires (Rows == Cols) && arithmetic<T, U>
		{
			clmsize_t c[Cols] = {};
			for (clmsize_t i = 0; i < Cols; i++)
			{
				c[i] = i;
			}
			return detHelper<U, Cols>(0, c);
		}

		/* Not very important functions that would complicate things a lot
		
		template <typename U = T>
		constexpr U minor(clmsize_t r, clmsize_t c) requires (Rows == Cols) && arithmetic<T, U>
		{
			clmsize_t ra[Rows - 1] = {};
			clmsize_t ca[Cols - 1] = {};
			clmsize_t r1 = 0;
			clmsize_t c1 = 0;
			for (clmsize_t i = 0; i < Rows - 1; i++)
			{
				if (r1 == r)
				{
					r1++;
				}
				if (c1 == c)
				{
					c1++;
				}
				ra[i] = r1;
				ca[i] = c1;
				r1++;
				c1++;
			}
			return detHelper2<U, Rows - 1>(ra, ca);
		}

		// This calculation is crazy expensive for matrices larger than 3x3
		template <typename U = T>
		constexpr clmmat<Rows, Cols, U> cofactor() requires (Rows == Cols) && arithmetic<T, U>
		{
			clmmat<Rows, Cols, U> result;
			clmsize_t ra[Rows - 1] = {};
			for (clmsize_t i = 0; i < Rows - 1; i++)
			{
				ra[i] = i + 1;
			}
			U flip = static_cast<U>(-1);
			for (clmsize_t r = 0; r < Rows; r++)
			{
				clmsize_t ca[Cols - 1] = {};
				for (clmsize_t i = 0; i < Cols - 1; i++)
				{
					ca[i] = i + 1;
				}
				U flip2 = static_cast<U>(0) - flip;
				for (clmsize_t c = 0; c < Cols; c++)
				{
					result[r].set(c, flip2 * detHelper2<U, Rows - 1>(ra, ca));
					flip2 = static_cast<U>(0) - flip2;
					if (c < Cols - 1)
					{
						ca[c]--;
					}
				}
				flip = static_cast<U>(0) - flip;
				if (r < Rows - 1)
				{
					ra[r]--;
				}
			}
			return result;
		}

		// This calculation is crazy expensive for matrices larger than 3x3
		template <typename U = T>
		constexpr inline clmmat<Rows, Cols, U> adjoint() requires (Rows == Cols) && arithmetic<T, U>
		{
			return cofactor<U>().transpose();
		}
		*/

		// This calculation is crazy expensive for matrices larger than 3x3
		template <typename U = T>
		constexpr clmmat<Rows, Cols, U> inverse() requires (Rows == Cols) && arithmetic<T, U>
		{
			U invdet = static_cast<U>(1) / determinant<U>();
			clmmat<Rows, Cols, U> result;
			clmsize_t ra[Rows - 1] = {};
			for (clmsize_t i = 0; i < Rows - 1; i++)
			{
				ra[i] = i + 1;
			}
			U flip = static_cast<U>(-1);
			for (clmsize_t r = 0; r < Rows; r++)
			{
				clmsize_t ca[Cols - 1] = {};
				for (clmsize_t i = 0; i < Cols - 1; i++)
				{
					ca[i] = i + 1;
				}
				U flip2 = static_cast<U>(0) - flip;
				for (clmsize_t c = 0; c < Cols; c++)
				{
					result[r].set(c, flip2 * detHelper2<U, Rows - 1>(ra, ca) * invdet);
					flip2 = static_cast<U>(0) - flip2;
					if (c < Cols - 1)
					{
						ca[c]--;
					}
				}
				flip = static_cast<U>(0) - flip;
				if (r < Rows - 1)
				{
					ra[r]--;
				}
			}
			return result.transpose();
		}

	};

}

#endif // CLFE_CLMATH_MAT_H