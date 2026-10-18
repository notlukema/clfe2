#ifndef CLFE_CLMATH_MCONST_H
#define CLFE_CLMATH_MCONST_H
#define _SILENCE_ALL_CXX23_DEPRECATION_WARNINGS

#include <numbers>
#include <limits>

#include "mdef.h"

#include "clfe/features.h"

// Porting std number and numeric_limits into clfe

namespace clfe
{

	template <typename T>
		requires arithmetic<T>
	struct mnumbers
	{
	public:
		static constexpr T e = static_cast<T>(0);
		static constexpr T log2e = static_cast<T>(0);
		static constexpr T log10e = static_cast<T>(0);
		static constexpr T pi = static_cast<T>(0);
		static constexpr T inv_pi = static_cast<T>(0);
		static constexpr T inv_sqrtpi = static_cast<T>(0);
		static constexpr T ln2 = static_cast<T>(0);
		static constexpr T ln10 = static_cast<T>(0);
		static constexpr T sqrt2 = static_cast<T>(0);
		static constexpr T sqrt3 = static_cast<T>(0);
		static constexpr T inv_sqrt3 = static_cast<T>(0);
		static constexpr T egamma = static_cast<T>(0);
		static constexpr T phi = static_cast<T>(0);

	};

	template <typename T>
		requires floating_point<T>
	struct mnumbers<T>
	{
	public:
		static constexpr T e = std::numbers::e_v<T>;
		static constexpr T log2e = std::numbers::log2e_v<T>;
		static constexpr T log10e = std::numbers::log10e_v<T>;
		static constexpr T pi = std::numbers::pi_v<T>;
		static constexpr T inv_pi = std::numbers::inv_pi_v<T>;
		static constexpr T inv_sqrtpi = std::numbers::inv_sqrtpi_v<T>;
		static constexpr T ln2 = std::numbers::ln2_v<T>;
		static constexpr T ln10 = std::numbers::ln10_v<T>;
		static constexpr T sqrt2 = std::numbers::sqrt2_v<T>;
		static constexpr T sqrt3 = std::numbers::sqrt3_v<T>;
		static constexpr T inv_sqrt3 = std::numbers::inv_sqrt3_v<T>;
		static constexpr T egamma = std::numbers::egamma_v<T>;
		static constexpr T phi = std::numbers::phi_v<T>;

	};

	template <typename T>
		requires arithmetic<T>
	struct mconst
	{
	public:
		using numbers = mnumbers<T>;
		/*
		static constexpr T e = mnumbers<T>::e;
		static constexpr T log2e = mnumbers<T>::log2e;
		static constexpr T log10e = mnumbers<T>::log10e;
		static constexpr T pi = mnumbers<T>::pi;
		static constexpr T inv_pi = mnumbers<T>::inv_pi;
		static constexpr T inv_sqrtpi = mnumbers<T>::inv_sqrtpi;
		static constexpr T ln2 = mnumbers<T>::ln2;
		static constexpr T ln10 = mnumbers<T>::ln10;
		static constexpr T sqrt2 = mnumbers<T>::sqrt2;
		static constexpr T sqrt3 = mnumbers<T>::sqrt3;
		static constexpr T inv_sqrt3 = mnumbers<T>::inv_sqrt3;
		static constexpr T egamma = mnumbers<T>::egamma;
		static constexpr T phi = mnumbers<T>::phi;
		*/
		/*
		static constexpr T e = (floating_point<T> ? std::numbers::e_v<T> : static_cast<T>(0));
		static constexpr T log2e = (floating_point<T> ? std::numbers::log2e_v<T> : static_cast<T>(0));
		static constexpr T log10e = (floating_point<T> ? std::numbers::log10e_v<T> : static_cast<T>(0));
		static constexpr T pi = (floating_point<T> ? std::numbers::pi_v<T> : static_cast<T>(0));
		static constexpr T inv_pi = (floating_point<T> ? std::numbers::inv_pi_v<T> : static_cast<T>(0));
		static constexpr T inv_sqrtpi = (floating_point<T> ? std::numbers::inv_sqrtpi_v<T> : static_cast<T>(0));
		static constexpr T ln2 = (floating_point<T> ? std::numbers::ln2_v<T> : static_cast<T>(0));
		static constexpr T ln10 = (floating_point<T> ? std::numbers::ln10_v<T> : static_cast<T>(0));
		static constexpr T sqrt2 = (floating_point<T> ? std::numbers::sqrt2_v<T> : static_cast<T>(0));
		static constexpr T sqrt3 = (floating_point<T> ? std::numbers::sqrt3_v<T> : static_cast<T>(0));
		static constexpr T inv_sqrt3 = (floating_point<T> ? std::numbers::inv_sqrt3_v<T> : static_cast<T>(0));
		static constexpr T egamma = (floating_point<T> ? std::numbers::egamma_v<T> : static_cast<T>(0));
		static constexpr T phi = (floating_point<T> ? std::numbers::phi_v<T> : static_cast<T>(0));
		*/

		using mlimits = std::numeric_limits<T>;

		static constexpr bool is_specialized = mlimits::is_specialized;
		static constexpr bool is_signed = mlimits::is_signed;
		static constexpr bool is_integer = mlimits::is_integer;
		static constexpr bool is_exact = mlimits::is_exact;
		static constexpr bool has_infinity = mlimits::has_infinity;
		static constexpr bool has_quiet_NaN = mlimits::has_quiet_NaN;
		static constexpr bool has_signaling_NaN = mlimits::has_signaling_NaN;

#if _CPP_VERSION < 23 || defined(_CLFE_KEEP_DEPRECATED)

		using float_denorm_style = std::float_denorm_style;
		static constexpr float_denorm_style has_denorm = mlimits::has_denorm;

		static constexpr bool has_denorm_loss = mlimits::has_denorm_loss;

#endif

		using float_round_style = std::float_round_style;
		static constexpr float_round_style round_style = mlimits::round_style;

		static constexpr bool is_iec559 = mlimits::is_iec559;
		static constexpr bool is_bounded = mlimits::is_bounded;
		static constexpr bool is_modulo = mlimits::is_modulo;

		static constexpr int digits = mlimits::digits;
		static constexpr int digits10 = mlimits::digits10;
		static constexpr int max_digits10 = mlimits::max_digits10;
		static constexpr int radix = mlimits::radix;
		static constexpr int min_exponent = mlimits::min_exponent;
		static constexpr int min_exponent10 = mlimits::min_exponent10;
		static constexpr int max_exponent = mlimits::max_exponent;
		static constexpr int max_exponent10 = mlimits::max_exponent10;

		static constexpr bool traps = mlimits::traps;
		static constexpr bool tinyness_before = mlimits::tinyness_before;

		static constexpr T min() noexcept
		{
			return mlimits::min();
		}

		static constexpr T lowest() noexcept
		{
			return mlimits::lowest();
		}

		static constexpr T max() noexcept
		{
			return mlimits::max();
		}

		static constexpr T epsilon() noexcept
		{
			return mlimits::epsilon();
		}

		static constexpr T round_error() noexcept
		{
			return mlimits::round_error();
		}

		static constexpr T infinity() noexcept
		{
			return mlimits::infinity();
		}

		static constexpr T quiet_NaN() noexcept
		{
			return mlimits::quiet_NaN();
		}

		static constexpr T signaling_NaN() noexcept
		{
			return mlimits::signaling_NaN();
		}

		static constexpr T denorm_min() noexcept
		{
			return mlimits::denorm_min();
		}

	};

}

#endif // CLFE_CLMATH_MCONST_H