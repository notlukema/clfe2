#ifndef CLFE_CLUTIL_PRINT_H
#define CLFE_CLUTIL_PRINT_H

#include <iostream>
#if defined(__cpp_lib_print)
#include <print>
#else
#include <stdio.h>
#endif
#include <string>
#include <type_traits>
#include <concepts>

#include "clfe/features.h"

// Include this file last because the print functions depend on header guards from other components

namespace clfe
{

#if defined(__cpp_lib_print)

	template <typename T>
	void print(T x) requires std::is_integral_v<T>
	{
		std::print("{}", x);
	}
	
	template <typename T>
	void print(T x) requires std::is_floating_point_v<T>
	{
		std::print("{:.4f}", x);
	}

	void print(const char* str)
	{
		std::print("{}", str);
	}

	void print(char c)
	{
		std::print("{}", c);
	}

	void print(const std::string& str)
	{
		std::print("{}", str);
	}

#else

	template <typename T>
	void print(T x) requires std::is_integral_v<T>
	{
		printf("%d", x);
	}

	template <typename T>
	void print(T x) requires std::is_floating_point_v<T>
	{
		printf("%.4f", x);
	}

	void print(const char* str)
	{
		printf(str);
	}

	void print(char c)
	{
		printf("%c", c);
	}

	void print(const std::string& str)
	{
		printf(str.c_str());
	}

#endif

	template <typename T>
	concept printable = requires(T a) { print(a); };

#ifdef CLFE_CLMATH_VEC_H

	template <clmsize_t Size, typename T>
	void print(const clmvec<Size, T>& vec) requires (Size > 0) && printable<T>
	{
		print("[");
		clmsize_t i = 0;
		for (; i < vec.size() - 1; i++)
		{
			print(vec.get(i));
			print(", ");
		}
		print(vec.get(i));
		print("]");
	}

	template <clmsize_t Size, typename T>
	std::ostream& operator<<(std::ostream& os, const clmvec<Size, T>& vec) requires (Size > 0) && printable<T>
	{
		os << "[";
		clmsize_t i = 0;
		for (; i < vec.size() - 1; i++)
		{
			os << vec.get(i) << ", ";
		}
		os << vec.get(i) << "]";
		return os;
	}

#endif

#ifdef CLFE_CLMATH_MAT_H

	template <clmsize_t Rows, clmsize_t Cols, typename T>
	void print(const clmmat<Rows, Cols, T>& mat) requires (Rows > 0) && (Cols > 0) && printable<T>
	{
		print("[");
		for (clmsize_t r = 0; r < mat.rows(); r++)
		{
			if (r > 0)
			{
				print(" ");
			}
			auto vec = mat.get(r);
			clmsize_t c = 0;
			for (; c < vec.size() - 1; c++)
			{
				print(vec.get(c));
				print(", ");
			}
			print(vec.get(c));
			if (r < mat.rows() - 1)
			{
				print("\n");
			}
		}
		print("]");
	}
	
	template <clmsize_t Rows, clmsize_t Cols, typename T>
	std::ostream& operator<<(std::ostream& os, const clmmat<Rows, Cols, T>& mat) requires (Rows > 0) && (Cols > 0) && printable<T>
	{
		os << "[";
		for (clmsize_t r = 0; r < mat.rows(); r++)
		{
			if (r > 0)
			{
				os << " ";
			}
			auto vec = mat.get(r);
			clmsize_t c = 0;
			for (; c < vec.size() - 1; c++)
			{
				os << vec.get(c) << ", ";
			}
			os << vec.get(c);
			if (r < mat.rows() - 1)
			{
				os << "\n";
			}
		}
		os << "]";
		return os;
	}
	
#endif

	// Special println

	template <typename T>
	inline void println(T v) requires requires(T v) { print(v); }
	{
		print(v);
		print("\n");
	}

}

#endif // CLFE_CLUTIL_PRINT_H