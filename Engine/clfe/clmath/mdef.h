#ifndef CLFE_CLMATH_MDEF_H
#define CLFE_CLMATH_MDEF_H

#include <cstdint>
#include <type_traits>
#include <concepts>

namespace clfe
{

	using clmsize_t = uint32_t;

	// Guarentees that all types are the same as T
	template <typename T, typename... Args>
	concept msame = (std::same_as<T, Args> && ...);

	// Guarentees that all types can be converted to T
	template <typename T, typename... Args>
	concept mcompat = (std::convertible_to<Args, T> && ...);

	// Guarentees that From can be converted to To
	template <typename From, typename To>
	concept mconvert = std::convertible_to<From, To>;

	//

	// Guarentees that T is an arithmetic type
	template <typename... Args>
	concept arithmetic = (std::is_arithmetic_v<Args> && ...);

	// Guarentees that T is an integral type
	template <typename... Args>
	concept integral = (std::is_integral_v<Args> && ...);

	// Guarentees that T is a floating point type
	template <typename... Args>
	concept floating_point = (std::is_floating_point_v<Args> && ...);

	/*
	// Guarentees that T and U are arithmetic types and that T can be converted to U
	template <typename T, typename U>
	concept arithmetic = arithmetic<T, U> && std::convertible_to<T, U>;

	// Guarentees that T and U are arithmetic types and that the result of T + U can be converted to T
	template <typename T, typename U>
	concept arithmetic_variant2 = arithmetic<T, U> && std::convertible_to<decltype(static_cast<T>(0) + static_cast<U>(0)), T>;
	*/

	//

	// Guarentees that T can do basic math operations with itself
	template <typename T>
	concept mathable = requires(T a)
	{
		a + a;
		a - a;
		a * a;
		a / a;
	};

	// Guarentees that T and U can do basic math operations with each other
	template <typename T, typename U>
	concept intermathable = requires(T a, U b)
	{
		a + b;
		a - b;
		a * b;
		a / b;
		b + a;
		b - a;
		b * a;
		b / a;
	};

	// Guarentees that T and U are mathable and intermathable
	template <typename T, typename U>
	concept mathable_variant1 = mathable<T> && mathable<U> && intermathable<T, U>;

	// Guarentees that T and U are mathable and intermathable and that T can be converted to U
	template <typename T, typename U>
	concept mathable_variant2 = mathable_variant1<T, U> && std::convertible_to<T, U>;

	// Guarentees that T and U are mathable and intermathable and that the result of basic math operations between T and U can be converted to T
	template <typename T, typename U>
	concept mathable_variant3 = mathable_variant1<T, U> && requires(T a, U b)
	{
		{ a + b } -> mconvert<T>;
		{ a - b } -> mconvert<T>;
		{ a * b } -> mconvert<T>;
		{ a / b } -> mconvert<T>;
		{ b + a } -> mconvert<T>;
		{ b - a } -> mconvert<T>;
		{ b * a } -> mconvert<T>;
		{ b / a } -> mconvert<T>;
	};

	//

	constexpr clmsize_t size_max(clmsize_t a, clmsize_t b)
	{
		return (a > b) ? a : b;
	}

	constexpr clmsize_t size_min(clmsize_t a, clmsize_t b)
	{
		return (a < b) ? a : b;
	}

}

#endif // CLFE_CLMATH_MDEF_H