#ifndef CLFE_CLMATH_MATH_H
#define CLFE_CLMATH_MATH_H

#include <cmath>

// Porting std math functions into clfe
// Maybe add comment annotations?

// Also waiting for constexpr std math functions lol (hope I don't forget by that time)

namespace clfe
{

	// Trig

	inline double sin(double x)
	{
		return std::sin(x);
	}

	inline long double sin(long double x)
	{
		return std::sinl(x);
	}

	inline long double sinl(long double x)
	{
		return std::sinl(x);
	}

	inline float sin(float x)
	{
		return std::sinf(x);
	}

	inline float sinf(float x)
	{
		return std::sinf(x);
	}

	inline double cos(double x)
	{
		return std::cos(x);
	}

	inline long double cos(long double x)
	{
		return std::cosl(x);
	}

	inline long double cosl(long double x)
	{
		return std::cosl(x);
	}

	inline float cos(float x)
	{
		return std::cosf(x);
	}

	inline float cosf(float x)
	{
		return std::cosf(x);
	}

	inline double tan(double x)
	{
		return std::tan(x);
	}

	inline long double tan(long double x)
	{
		return std::tanl(x);
	}

	inline long double tanl(long double x)
	{
		return std::tanl(x);
	}

	inline float tan(float x)
	{
		return std::tanf(x);
	}

	inline float tanf(float x)
	{
		return std::tanf(x);
	}

	inline double asin(double x)
	{
		return std::asin(x);
	}

	inline long double asin(long double x)
	{
		return std::asinl(x);
	}

	inline long double asinl(long double x)
	{
		return std::asinl(x);
	}

	inline float asin(float x)
	{
		return std::asinf(x);
	}
	
	inline float asinf(float x)
	{
		return std::asinf(x);
	}

	inline double acos(double x)
	{
		return std::acos(x);
	}

	inline long double acos(long double x)
	{
		return std::acosl(x);
	}

	inline long double acosl(long double x)
	{
		return std::acosl(x);
	}

	inline float acos(float x)
	{
		return std::acosf(x);
	}

	inline float acosf(float x)
	{
		return std::acosf(x);
	}

	inline double atan(double x)
	{
		return std::atan(x);
	}

	inline long double atan(long double x)
	{
		return std::atanl(x);
	}

	inline long double atanl(long double x)
	{
		return std::atanl(x);
	}	

	inline float atan(float x)
	{
		return std::atanf(x);
	}

	inline float atanf(float x)
	{
		return std::atanf(x);
	}

	inline double atan2(double y, double x)
	{
		return std::atan2(y, x);
	}

	inline long double atan2(long double y, long double x)
	{
		return std::atan2l(y, x);
	}

	inline long double atan2l(long double y, long double x)
	{
		return std::atan2l(y, x);
	}

	inline float atan2(float y, float x)
	{
		return std::atan2f(y, x);
	}

	inline float atan2f(float y, float x)
	{
		return std::atan2f(y, x);
	}

	// Hyper

	inline double sinh(double x)
	{
		return std::sinh(x);
	}

	inline long double sinh(long double x)
	{
		return std::sinhl(x);
	}

	inline long double sinhl(long double x)
	{
		return std::sinhl(x);
	}

	inline float sinh(float x)
	{
		return std::sinhf(x);
	}

	inline float sinhf(float x)
	{
		return std::sinhf(x);
	}

	inline double cosh(double x)
	{
		return std::cosh(x);
	}

	inline long double cosh(long double x)
	{
		return std::coshl(x);
	}

	inline long double coshl(long double x)
	{
		return std::coshl(x);
	}

	inline float cosh(float x)
	{
		return std::coshf(x);
	}

	inline float coshf(float x)
	{
		return std::coshf(x);
	}

	inline double tanh(double x)
	{
		return std::tanh(x);
	}

	inline long double tanh(long double x)
	{
		return std::tanhl(x);
	}

	inline long double tanhl(long double x)
	{
		return std::tanhl(x);
	}

	inline float tanh(float x)
	{
		return std::tanhf(x);
	}

	inline float tanhf(float x)
	{
		return std::tanhf(x);
	}

	inline double asinh(double x)
	{
		return std::asinh(x);
	}

	inline long double asinh(long double x)
	{
		return std::asinhl(x);
	}

	inline long double asinhl(long double x)
	{
		return std::asinhl(x);
	}

	inline float asinh(float x)
	{
		return std::asinhf(x);
	}

	inline float asinhf(float x)
	{
		return std::asinhf(x);
	}

	inline double acosh(double x)
	{
		return std::acosh(x);
	}

	inline long double acosh(long double x)
	{
		return std::acoshl(x);
	}

	inline long double acoshl(long double x)
	{
		return std::acoshl(x);
	}

	inline float acosh(float x)
	{
		return std::acoshf(x);
	}

	inline float acoshf(float x)
	{
		return std::acoshf(x);
	}

	inline double atanh(double x)
	{
		return std::atanh(x);
	}

	inline long double atanh(long double x)
	{
		return std::atanhl(x);
	}

	inline long double atanhl(long double x)
	{
		return std::atanhl(x);
	}

	inline float atanh(float x)
	{
		return std::atanhf(x);
	}

	inline float atanhf(float x)
	{
		return std::atanhf(x);
	}

	// Exp, Log

	inline double exp(double x)
	{
		return std::exp(x);
	}

	inline long double exp(long double x)
	{
		return std::expl(x);
	}

	inline long double expl(long double x)
	{
		return std::expl(x);
	}

	inline float exp(float x)
	{
		return std::expf(x);
	}

	inline float expf(float x)
	{
		return std::expf(x);
	}

	inline double frexp(double x, int* exp)
	{
		return std::frexp(x, exp);
	}

	inline long double frexp(long double x, int* exp)
	{
		return std::frexpl(x, exp);
	}

	inline long double frexpl(long double x, int* exp)
	{
		return std::frexpl(x, exp);
	}
	
	inline float frexp(float x, int* exp)
	{
		return std::frexpf(x, exp);
	}

	inline float frexpf(float x, int* exp)
	{
		return std::frexpf(x, exp);
	}

	inline double ldexp(double x, int exp)
	{
		return std::ldexp(x, exp);
	}

	inline long double ldexp(long double x, int exp)
	{
		return std::ldexpl(x, exp);
	}

	inline long double ldexpl(long double x, int exp)
	{
		return std::ldexpl(x, exp);
	}

	inline float ldexp(float x, int exp)
	{
		return std::ldexpf(x, exp);
	}

	inline float ldexpf(float x, int exp)
	{
		return std::ldexpf(x, exp);
	}

	inline double log(double x)
	{
		return std::log(x);
	}

	inline long double log(long double x)
	{
		return std::logl(x);
	}

	inline long double logl(long double x)
	{
		return std::logl(x);
	}

	inline float log(float x)
	{
		return std::logf(x);
	}

	inline float logf(float x)
	{
		return std::logf(x);
	}

	inline double log10(double x)
	{
		return std::log10(x);
	}

	inline long double log10(long double x)
	{
		return std::log10l(x);
	}

	inline long double log10l(long double x)
	{
		return std::log10l(x);
	}

	inline float log10(float x)
	{
		return std::log10f(x);
	}

	inline float log10f(float x)
	{
		return std::log10f(x);
	}

	inline double modf(double x, double* intpart)
	{
		return std::modf(x, intpart);
	}

	inline long double modf(long double x, long double* intpart)
	{
		return std::modfl(x, intpart);
	}

	inline long double modfl(long double x, long double* intpart)
	{
		return std::modfl(x, intpart);
	}

	inline float modf(float x, float* intpart)
	{
		return std::modff(x, intpart);
	}

	inline float modff(float x, float* intpart)
	{
		return std::modff(x, intpart);
	}

	inline double exp2(double x)
	{
		return std::exp2(x);
	}

	inline long double exp2(long double x)
	{
		return std::exp2l(x);
	}

	inline long double exp2l(long double x)
	{
		return std::exp2l(x);
	}

	inline float exp2(float x)
	{
		return std::exp2f(x);
	}

	inline float exp2f(float x)
	{
		return std::exp2f(x);
	}

	inline double expm1(double x)
	{
		return std::expm1(x);
	}

	inline long double expm1(long double x)
	{
		return std::expm1l(x);
	}

	inline long double expm1l(long double x)
	{
		return std::expm1l(x);
	}

	inline float expm1(float x)
	{
		return std::expm1f(x);
	}

	inline float expm1f(float x)
	{
		return std::expm1f(x);
	}

	inline int ilogb(double x)
	{
		return std::ilogb(x);
	}

	inline int ilogb(long double x)
	{
		return std::ilogbl(x);
	}

	inline int ilogbl(long double x)
	{
		return std::ilogbl(x);
	}

	inline int ilogb(float x)
	{
		return std::ilogbf(x);
	}

	inline int ilogbf(float x)
	{
		return std::ilogbf(x);
	}

	inline double log1p(double x)
	{
		return std::log1p(x);
	}

	inline long double log1p(long double x)
	{
		return std::log1pl(x);
	}

	inline long double log1pl(long double x)
	{
		return std::log1pl(x);
	}

	inline float log1p(float x)
	{
		return std::log1pf(x);
	}

	inline float log1pf(float x)
	{
		return std::log1pf(x);
	}

	inline double log2(double x)
	{
		return std::log2(x);
	}

	inline long double log2(long double x)
	{
		return std::log2l(x);
	}

	inline long double log2l(long double x)
	{
		return std::log2l(x);
	}

	inline float log2(float x)
	{
		return std::log2f(x);
	}

	inline float log2f(float x)
	{
		return std::log2f(x);
	}

	inline double logb(double x)
	{
		return std::logb(x);
	}

	inline long double logb(long double x)
	{
		return std::logbl(x);
	}

	inline long double logbl(long double x)
	{
		return std::logbl(x);
	}

	inline float logb(float x)
	{
		return std::logbf(x);
	}

	inline float logbf(float x)
	{
		return std::logbf(x);
	}

	inline double scalbn(double x, int n)
	{
		return std::scalbn(x, n);
	}

	inline long double scalbn(long double x, int n)
	{
		return std::scalbnl(x, n);
	}

	inline long double scalbnl(long double x, int n)
	{
		return std::scalbnl(x, n);
	}

	inline float scalbn(float x, int n)
	{
		return std::scalbnf(x, n);
	}

	inline float scalbnf(float x, int n)
	{
		return std::scalbnf(x, n);
	}

	inline double scalbln(double x, long n)
	{
		return std::scalbln(x, n);
	}

	inline long double scalbln(long double x, long n)
	{
		return std::scalblnl(x, n);
	}

	inline long double scalblnl(long double x, long n)
	{
		return std::scalblnl(x, n);
	}

	inline float scalbln(float x, long n)
	{
		return std::scalblnf(x, n);
	}

	inline float scalblnf(float x, long n)
	{
		return std::scalblnf(x, n);
	}

	// Pow

	inline double pow(double base, double exponent)
	{
		return std::pow(base, exponent);
	}

	inline long double pow(long double base, long double exponent)
	{
		return std::powl(base, exponent);
	}

	inline long double powl(long double base, long double exponent)
	{
		return std::powl(base, exponent);
	}

	inline float pow(float base, float exponent)
	{
		return std::powf(base, exponent);
	}

	inline float powf(float base, float exponent)
	{
		return std::powf(base, exponent);
	}

	inline double sqrt(double x)
	{
		return std::sqrt(x);
	}

	inline long double sqrt(long double x)
	{
		return std::sqrtl(x);
	}

	inline long double sqrtl(long double x)
	{
		return std::sqrtl(x);
	}

	inline float sqrt(float x)
	{
		return std::sqrtf(x);
	}

	inline float sqrtf(float x)
	{
		return std::sqrtf(x);
	}

	inline double cbrt(double x)
	{
		return std::cbrt(x);
	}

	inline long double cbrt(long double x)
	{
		return std::cbrtl(x);
	}

	inline long double cbrtl(long double x)
	{
		return std::cbrtl(x);
	}

	inline float cbrt(float x)
	{
		return std::cbrtf(x);
	}

	inline float cbrtf(float x)
	{
		return std::cbrtf(x);
	}

	inline double hypot(double x, double y)
	{
		return std::hypot(x, y);
	}

	inline long double hypot(long double x, long double y)
	{
		return std::hypotl(x, y);
	}

	inline long double hypotl(long double x, long double y)
	{
		return std::hypotl(x, y);
	}

	inline float hypot(float x, float y)
	{
		return std::hypotf(x, y);
	}

	inline float hypotf(float x, float y)
	{
		return std::hypotf(x, y);
	}

	// Err, Gamma

	inline double erf(double x)
	{
		return std::erf(x);
	}

	inline long double erf(long double x)
	{
		return std::erfl(x);
	}

	inline long double erfl(long double x)
	{
		return std::erfl(x);
	}

	inline float erf(float x)
	{
		return std::erff(x);
	}

	inline float erff(float x)
	{
		return std::erff(x);
	}

	inline double erfc(double x)
	{
		return std::erfc(x);
	}

	inline long double erfc(long double x)
	{
		return std::erfcl(x);
	}

	inline long double erfcl(long double x)
	{
		return std::erfcl(x);
	}

	inline float erfc(float x)
	{
		return std::erfcf(x);
	}

	inline float erfcf(float x)
	{
		return std::erfcf(x);
	}

	inline double tgamma(double x)
	{
		return std::tgamma(x);
	}

	inline long double tgamma(long double x)
	{
		return std::tgammal(x);
	}

	inline long double tgammal(long double x)
	{
		return std::tgammal(x);
	}

	inline float tgamma(float x)
	{
		return std::tgammaf(x);
	}

	inline float tgammaf(float x)
	{
		return std::tgammaf(x);
	}

	inline double lgamma(double x)
	{
		return std::lgamma(x);
	}

	inline long double lgamma(long double x)
	{
		return std::lgammal(x);
	}

	inline long double lgammal(long double x)
	{
		return std::lgammal(x);
	}

	inline float lgamma(float x)
	{
		return std::lgammaf(x);
	}

	inline float lgammaf(float x)
	{
		return std::lgammaf(x);
	}

	// Round, Remainder

	inline double ceil(double x)
	{
		return std::ceil(x);
	}

	inline long double ceil(long double x)
	{
		return std::ceill(x);
	}

	inline long double ceill(long double x)
	{
		return std::ceill(x);
	}

	inline float ceil(float x)
	{
		return std::ceilf(x);
	}

	inline float ceilf(float x)
	{
		return std::ceilf(x);
	}

	inline double floor(double x)
	{
		return std::floor(x);
	}

	inline long double floor(long double x)
	{
		return std::floorl(x);
	}

	inline long double floorl(long double x)
	{
		return std::floorl(x);
	}

	inline float floor(float x)
	{
		return std::floorf(x);
	}

	inline float floorf(float x)
	{
		return std::floorf(x);
	}

	inline double fmod(double numer, double denom)
	{
		return std::fmod(numer, denom);
	}

	inline long double fmod(long double numer, long double denom)
	{
		return std::fmodl(numer, denom);
	}

	inline long double fmodl(long double numer, long double denom)
	{
		return std::fmodl(numer, denom);
	}

	inline float fmod(float numer, float denom)
	{
		return std::fmodf(numer, denom);
	}

	inline float fmodf(float numer, float denom)
	{
		return std::fmodf(numer, denom);
	}

	inline double trunc(double x)
	{
		return std::trunc(x);
	}

	inline long double trunc(long double x)
	{
		return std::truncl(x);
	}

	inline long double truncl(long double x)
	{
		return std::truncl(x);
	}

	inline float trunc(float x)
	{
		return std::truncf(x);
	}

	inline float truncf(float x)
	{
		return std::truncf(x);
	}

	inline double round(double x)
	{
		return std::round(x);
	}

	inline long double round(long double x)
	{
		return std::roundl(x);
	}

	inline long double roundl(long double x)
	{
		return std::roundl(x);
	}

	inline float round(float x)
	{
		return std::roundf(x);
	}

	inline float roundf(float x)
	{
		return std::roundf(x);
	}

	inline long lround(double x)
	{
		return std::lround(x);
	}

	inline long lround(long double x)
	{
		return std::lroundl(x);
	}

	inline long lroundl(long double x)
	{
		return std::lroundl(x);
	}

	inline long lround(float x)
	{
		return std::lroundf(x);
	}

	inline long lroundf(float x)
	{
		return std::lroundf(x);
	}

	inline long long llround(double x)
	{
		return std::llround(x);
	}

	inline long long llround(long double x)
	{
		return std::llroundl(x);
	}

	inline long long llroundl(long double x)
	{
		return std::llroundl(x);
	}
	
	inline long long llround(float x)
	{
		return std::llroundf(x);
	}

	inline long long llroundf(float x)
	{
		return std::llroundf(x);
	}

	inline double rint(double x)
	{
		return std::rint(x);
	}

	inline long double rint(long double x)
	{
		return std::rintl(x);
	}

	inline long double rintl(long double x)
	{
		return std::rintl(x);
	}

	inline float rint(float x)
	{
		return std::rintf(x);
	}

	inline float rintf(float x)
	{
		return std::rintf(x);
	}

	inline long lrint(double x)
	{
		return std::lrint(x);
	}

	inline long lrint(long double x)
	{
		return std::lrintl(x);
	}

	inline long lrintl(long double x)
	{
		return std::lrintl(x);
	}

	inline long lrint(float x)
	{
		return std::lrintf(x);
	}

	inline long lrintf(float x)
	{
		return std::lrintf(x);
	}

	inline long long llrint(double x)
	{
		return std::llrint(x);
	}

	inline long long llrint(long double x)
	{
		return std::llrintl(x);
	}

	inline long long llrintl(long double x)
	{
		return std::llrintl(x);
	}

	inline long long llrint(float x)
	{
		return std::llrintf(x);
	}

	inline long long llrintf(float x)
	{
		return std::llrintf(x);
	}

	inline double nearbyint(double x)
	{
		return std::nearbyint(x);
	}

	inline long double nearbyint(long double x)
	{
		return std::nearbyintl(x);
	}

	inline long double nearbyintl(long double x)
	{
		return std::nearbyintl(x);
	}

	inline float nearbyint(float x)
	{
		return std::nearbyintf(x);
	}

	inline float nearbyintf(float x)
	{
		return std::nearbyintf(x);
	}

	inline double remainder(double numer, double denom)
	{
		return std::remainder(numer, denom);
	}

	inline long double remainder(long double numer, long double denom)
	{
		return std::remainderl(numer, denom);
	}

	inline long double remainderl(long double numer, long double denom)
	{
		return std::remainderl(numer, denom);
	}

	inline float remainder(float numer, float denom)
	{
		return std::remainderf(numer, denom);
	}

	inline float remainderf(float numer, float denom)
	{
		return std::remainderf(numer, denom);
	}

	inline double remquo(double numer, double denom, int* z)
	{
		return std::remquo(numer, denom, z);
	}

	inline long double remquo(long double numer, long double denom, int* z)
	{
		return std::remquol(numer, denom, z);
	}

	inline long double remquol(long double numer, long double denom, int* z)
	{
		return std::remquol(numer, denom, z);
	}

	inline float remquo(float numer, float denom, int* z)
	{
		return std::remquof(numer, denom, z);
	}

	inline float remquof(float numer, float denom, int* z)
	{
		return std::remquof(numer, denom, z);
	}

	// Floating point manip

	inline double copysign(double number, double sign)
	{
		return std::copysign(number, sign);
	}

	inline long double copysign(long double number, long double sign)
	{
		return std::copysignl(number, sign);
	}

	inline long double copysignl(long double number, long double sign)
	{
		return std::copysignl(number, sign);
	}

	inline float copysign(float number, float sign)
	{
		return std::copysignf(number, sign);
	}

	inline float copysignf(float number, float sign)
	{
		return std::copysignf(number, sign);
	}

	inline double nan(const char* tagp)
	{
		return std::nan(tagp);
	}

	inline long double nanl(const char* tagp)
	{
		return std::nanl(tagp);
	}

	inline float nanf(const char* tagp)
	{
		return std::nanf(tagp);
	}

	inline double nextafter(double x, double y)
	{
		return std::nextafter(x, y);
	}

	inline long double nextafter(long double x, long double y)
	{
		return std::nextafterl(x, y);
	}

	inline long double nextafterl(long double x, long double y)
	{
		return std::nextafterl(x, y);
	}

	inline float nextafter(float x, float y)
	{
		return std::nextafterf(x, y);
	}

	inline float nextafterf(float x, float y)
	{
		return std::nextafterf(x, y);
	}

	inline double nexttoward(double x, long double y)
	{
		return std::nexttoward(x, y);
	}

	inline long double nexttoward(long double x, long double y)
	{
		return std::nexttowardl(x, y);
	}

	inline long double nexttowardl(long double x, long double y)
	{
		return std::nexttowardl(x, y);
	}

	inline float nexttoward(float x, long double y)
	{
		return std::nexttowardf(x, y);
	}

	inline float nexttowardf(float x, long double y)
	{
		return std::nexttowardf(x, y);
	}

	// Min, Max, Diff

	inline double fdim(double x, double y)
	{
		return std::fdim(x, y);
	}

	inline long double fdim(long double x, long double y)
	{
		return std::fdiml(x, y);
	}

	inline long double fdiml(long double x, long double y)
	{
		return std::fdiml(x, y);
	}

	inline float fdim(float x, float y)
	{
		return std::fdimf(x, y);
	}

	inline float fdimf(float x, float y)
	{
		return std::fdimf(x, y);
	}

	inline double fmax(double x, double y)
	{
		return std::fmax(x, y);
	}

	inline long double fmax(long double x, long double y)
	{
		return std::fmaxl(x, y);
	}

	inline long double fmaxl(long double x, long double y)
	{
		return std::fmaxl(x, y);
	}

	inline float fmax(float x, float y)
	{
		return std::fmaxf(x, y);
	}

	inline float fmaxf(float x, float y)
	{
		return std::fmaxf(x, y);
	}

	inline double fmin(double x, double y)
	{
		return std::fmin(x, y);
	}

	inline long double fmin(long double x, long double y)
	{
		return std::fminl(x, y);
	}

	inline long double fminl(long double x, long double y)
	{
		return std::fminl(x, y);
	}

	inline float fmin(float x, float y)
	{
		return std::fminf(x, y);
	}

	inline float fminf(float x, float y)
	{
		return std::fminf(x, y);
	}

	// Other

	inline double fabs(double x)
	{
		return std::fabs(x);
	}

	inline long double fabs(long double x)
	{
		return std::fabsl(x);
	}

	inline long double fabsl(long double x)
	{
		return std::fabsl(x);
	}

	inline float fabs(float x)
	{
		return std::fabsf(x);
	}

	inline float fabsf(float x)
	{
		return std::fabsf(x);
	}

	inline double abs(double x)
	{
		return std::abs(x);
	}

	inline long double abs(long double x)
	{
		return std::abs(x);
	}

	inline long double absl(long double x)
	{
		return std::abs(x);
	}

	inline float abs(float x)
	{
		return std::abs(x);
	}

	inline float absf(float x)
	{
		return std::abs(x);
	}

	inline double fma(double x, double y, double z)
	{
		return std::fma(x, y, z);
	}

	inline long double fma(long double x, long double y, long double z)
	{
		return std::fmal(x, y, z);
	}

	inline long double fmal(long double x, long double y, long double z)
	{
		return std::fmal(x, y, z);
	}

	inline float fma(float x, float y, float z)
	{
		return std::fmaf(x, y, z);
	}

	inline float fmaf(float x, float y, float z)
	{
		return std::fmaf(x, y, z);
	}

	// Classification Macros

	inline int fpclassify(double x) noexcept
	{
		return std::fpclassify(x);
	}

	inline int fpclassify(long double x) noexcept
	{
		return std::fpclassify(x);
	}

	inline int fpclassify(float x) noexcept
	{
		return std::fpclassify(x);
	}

	inline bool isfinite(double x) noexcept
	{
		return std::isfinite(x);
	}

	inline bool isfinite(long double x) noexcept
	{
		return std::isfinite(x);
	}
		
	inline bool isfinite(float x) noexcept
	{
		return std::isfinite(x);
	}

	inline bool isinf(double x) noexcept
	{
		return std::isinf(x);
	}

	inline bool isinf(long double x) noexcept
	{
		return std::isinf(x);
	}

	inline bool isinf(float x) noexcept
	{
		return std::isinf(x);
	}

	inline bool isnan(double x) noexcept
	{
		return std::isnan(x);
	}

	inline bool isnan(long double x) noexcept
	{
		return std::isnan(x);
	}

	inline bool isnan(float x) noexcept
	{
		return std::isnan(x);
	}

	inline bool isnormal(double x) noexcept
	{
		return std::isnormal(x);
	}

	inline bool isnormal(long double x) noexcept
	{
		return std::isnormal(x);
	}

	inline bool isnormal(float x) noexcept
	{
		return std::isnormal(x);
	}

	inline bool signbit(double x) noexcept
	{
		return std::signbit(x);
	}

	inline bool signbit(long double x) noexcept
	{
		return std::signbit(x);
	}

	inline bool signbit(float x) noexcept
	{
		return std::signbit(x);
	}

	// Comparison Macros

	inline bool isgreater(double x, double y) noexcept
	{
		return std::isgreater(x, y);
	}

	inline bool isgreater(long double x, long double y) noexcept
	{
		return std::isgreater(x, y);
	}

	inline bool isgreater(float x, float y) noexcept
	{
		return std::isgreater(x, y);
	}

	inline bool isgreaterequal(double x, double y) noexcept
	{
		return std::isgreaterequal(x, y);
	}

	inline bool isgreaterequal(long double x, long double y) noexcept
	{
		return std::isgreaterequal(x, y);
	}

	inline bool isgreaterequal(float x, float y) noexcept
	{
		return std::isgreaterequal(x, y);
	}

	inline bool isless(double x, double y) noexcept
	{
		return std::isless(x, y);
	}

	inline bool isless(long double x, long double y) noexcept
	{
		return std::isless(x, y);
	}

	inline bool isless(float x, float y) noexcept
	{
		return std::isless(x, y);
	}

	inline bool islessequal(double x, double y) noexcept
	{
		return std::islessequal(x, y);
	}

	inline bool islessequal(long double x, long double y) noexcept
	{
		return std::islessequal(x, y);
	}

	inline bool islessequal(float x, float y) noexcept
	{
		return std::islessequal(x, y);
	}

	inline bool islessgreater(double x, double y) noexcept
	{
		return std::islessgreater(x, y);
	}

	inline bool islessgreater(long double x, long double y) noexcept
	{
		return std::islessgreater(x, y);
	}

	inline bool islessgreater(float x, float y) noexcept
	{
		return std::islessgreater(x, y);
	}

	inline bool isunordered(double x, double y) noexcept
	{
		return std::isunordered(x, y);
	}

	inline bool isunordered(long double x, long double y) noexcept
	{
		return std::isunordered(x, y);
	}

	inline bool isunordered(float x, float y) noexcept
	{
		return std::isunordered(x, y);
	}

}

#endif // CLFE_CLMATH_MATH_H