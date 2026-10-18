#ifndef CLFE_CLMATH_MATDEF_H
#define CLFE_CLMATH_MATDEF_H

#include <cstdint>

#include "clfe/features.h"
#if _CPP_VERSION >= 23
#include <stdfloat>
#endif

#include "mdef.h"
#include "mat.h"

namespace clfe
{

	template <clmsize_t Rows, clmsize_t Cols, typename T>
	using mat = clmmat<Rows, Cols, T>;

	template <typename T>
	using mat22 = clmmat<2, 2, T>;

	using mat22i = clmmat<2, 2, int>;
	using mat22u = clmmat<2, 2, unsigned int>;
	using mat22d = clmmat<2, 2, double>;
	using mat22ld = clmmat<2, 2, long double>;
	using mat22f = clmmat<2, 2, float>;
	using mat22b = clmmat<2, 2, bool>;

	using mat22l = clmmat<2, 2, long>;
	using mat22ul = clmmat<2, 2, unsigned long>;
	using mat22ll = clmmat<2, 2, long long>;
	using mat22ull = clmmat<2, 2, unsigned long long>;

	using mat22_i8 = clmmat<2, 2, int8_t>;
	using mat22_u8 = clmmat<2, 2, uint8_t>;
	using mat22_i16 = clmmat<2, 2, int16_t>;
	using mat22_u16 = clmmat<2, 2, uint16_t>;
	using mat22_i32 = clmmat<2, 2, int32_t>;
	using mat22_u32 = clmmat<2, 2, uint32_t>;
	using mat22_i64 = clmmat<2, 2, int64_t>;
	using mat22_u64 = clmmat<2, 2, uint64_t>;

	template <typename T>
	using mat23 = clmmat<2, 3, T>;

	using mat23i = clmmat<2, 3, int>;
	using mat23u = clmmat<2, 3, unsigned int>;
	using mat23d = clmmat<2, 3, double>;
	using mat23ld = clmmat<2, 3, long double>;
	using mat23f = clmmat<2, 3, float>;
	using mat23b = clmmat<2, 3, bool>;

	using mat23l = clmmat<2, 3, long>;
	using mat23ul = clmmat<2, 3, unsigned long>;
	using mat23ll = clmmat<2, 3, long long>;
	using mat23ull = clmmat<2, 3, unsigned long long>;

	using mat23_i8 = clmmat<2, 3, int8_t>;
	using mat23_u8 = clmmat<2, 3, uint8_t>;
	using mat23_i16 = clmmat<2, 3, int16_t>;
	using mat23_u16 = clmmat<2, 3, uint16_t>;
	using mat23_i32 = clmmat<2, 3, int32_t>;
	using mat23_u32 = clmmat<2, 3, uint32_t>;
	using mat23_i64 = clmmat<2, 3, int64_t>;
	using mat23_u64 = clmmat<2, 3, uint64_t>;

	template <typename T>
	using mat24 = clmmat<2, 4, T>;

	using mat24i = clmmat<2, 4, int>;
	using mat24u = clmmat<2, 4, unsigned int>;
	using mat24d = clmmat<2, 4, double>;
	using mat24ld = clmmat<2, 4, long double>;
	using mat24f = clmmat<2, 4, float>;
	using mat24b = clmmat<2, 4, bool>;

	using mat24l = clmmat<2, 4, long>;
	using mat24ul = clmmat<2, 4, unsigned long>;
	using mat24ll = clmmat<2, 4, long long>;
	using mat24ull = clmmat<2, 4, unsigned long long>;

	using mat24_i8 = clmmat<2, 4, int8_t>;
	using mat24_u8 = clmmat<2, 4, uint8_t>;
	using mat24_i16 = clmmat<2, 4, int16_t>;
	using mat24_u16 = clmmat<2, 4, uint16_t>;
	using mat24_i32 = clmmat<2, 4, int32_t>;
	using mat24_u32 = clmmat<2, 4, uint32_t>;
	using mat24_i64 = clmmat<2, 4, int64_t>;
	using mat24_u64 = clmmat<2, 4, uint64_t>;

	template <typename T>
	using mat32 = clmmat<3, 2, T>;

	using mat32i = clmmat<3, 2, int>;
	using mat32u = clmmat<3, 2, unsigned int>;
	using mat32d = clmmat<3, 2, double>;
	using mat32ld = clmmat<3, 2, long double>;
	using mat32f = clmmat<3, 2, float>;
	using mat32b = clmmat<3, 2, bool>;

	using mat32l = clmmat<3, 2, long>;
	using mat32ul = clmmat<3, 2, unsigned long>;
	using mat32ll = clmmat<3, 2, long long>;
	using mat32ull = clmmat<3, 2, unsigned long long>;

	using mat32_i8 = clmmat<3, 2, int8_t>;
	using mat32_u8 = clmmat<3, 2, uint8_t>;
	using mat32_i16 = clmmat<3, 2, int16_t>;
	using mat32_u16 = clmmat<3, 2, uint16_t>;
	using mat32_i32 = clmmat<3, 2, int32_t>;
	using mat32_u32 = clmmat<3, 2, uint32_t>;
	using mat32_i64 = clmmat<3, 2, int64_t>;
	using mat32_u64 = clmmat<3, 2, uint64_t>;

	template <typename T>
	using mat33 = clmmat<3, 3, T>;

	using mat33i = clmmat<3, 3, int>;
	using mat33u = clmmat<3, 3, unsigned int>;
	using mat33d = clmmat<3, 3, double>;
	using mat33ld = clmmat<3, 3, long double>;
	using mat33f = clmmat<3, 3, float>;
	using mat33b = clmmat<3, 3, bool>;

	using mat33l = clmmat<3, 3, long>;
	using mat33ul = clmmat<3, 3, unsigned long>;
	using mat33ll = clmmat<3, 3, long long>;
	using mat33ull = clmmat<3, 3, unsigned long long>;

	using mat33_i8 = clmmat<3, 3, int8_t>;
	using mat33_u8 = clmmat<3, 3, uint8_t>;
	using mat33_i16 = clmmat<3, 3, int16_t>;
	using mat33_u16 = clmmat<3, 3, uint16_t>;
	using mat33_i32 = clmmat<3, 3, int32_t>;
	using mat33_u32 = clmmat<3, 3, uint32_t>;
	using mat33_i64 = clmmat<3, 3, int64_t>;
	using mat33_u64 = clmmat<3, 3, uint64_t>;

	template <typename T>
	using mat34 = clmmat<3, 4, T>;

	using mat34i = clmmat<3, 4, int>;
	using mat34u = clmmat<3, 4, unsigned int>;
	using mat34d = clmmat<3, 4, double>;
	using mat34ld = clmmat<3, 4, long double>;
	using mat34f = clmmat<3, 4, float>;
	using mat34b = clmmat<3, 4, bool>;

	using mat34l = clmmat<3, 4, long>;
	using mat34ul = clmmat<3, 4, unsigned long>;
	using mat34ll = clmmat<3, 4, long long>;
	using mat34ull = clmmat<3, 4, unsigned long long>;

	using mat34_i8 = clmmat<3, 4, int8_t>;
	using mat34_u8 = clmmat<3, 4, uint8_t>;
	using mat34_i16 = clmmat<3, 4, int16_t>;
	using mat34_u16 = clmmat<3, 4, uint16_t>;
	using mat34_i32 = clmmat<3, 4, int32_t>;
	using mat34_u32 = clmmat<3, 4, uint32_t>;
	using mat34_i64 = clmmat<3, 4, int64_t>;
	using mat34_u64 = clmmat<3, 4, uint64_t>;

	template <typename T>
	using mat42 = clmmat<4, 2, T>;

	using mat42i = clmmat<4, 2, int>;
	using mat42u = clmmat<4, 2, unsigned int>;
	using mat42d = clmmat<4, 2, double>;
	using mat42ld = clmmat<4, 2, long double>;
	using mat42f = clmmat<4, 2, float>;
	using mat42b = clmmat<4, 2, bool>;

	using mat42l = clmmat<4, 2, long>;
	using mat42ul = clmmat<4, 2, unsigned long>;
	using mat42ll = clmmat<4, 2, long long>;
	using mat42ull = clmmat<4, 2, unsigned long long>;

	using mat42_i8 = clmmat<4, 2, int8_t>;
	using mat42_u8 = clmmat<4, 2, uint8_t>;
	using mat42_i16 = clmmat<4, 2, int16_t>;
	using mat42_u16 = clmmat<4, 2, uint16_t>;
	using mat42_i32 = clmmat<4, 2, int32_t>;
	using mat42_u32 = clmmat<4, 2, uint32_t>;
	using mat42_i64 = clmmat<4, 2, int64_t>;
	using mat42_u64 = clmmat<4, 2, uint64_t>;

	template <typename T>
	using mat43 = clmmat<4, 3, T>;

	using mat43i = clmmat<4, 3, int>;
	using mat43u = clmmat<4, 3, unsigned int>;
	using mat43d = clmmat<4, 3, double>;
	using mat43ld = clmmat<4, 3, long double>;
	using mat43f = clmmat<4, 3, float>;
	using mat43b = clmmat<4, 3, bool>;

	using mat43l = clmmat<4, 3, long>;
	using mat43ul = clmmat<4, 3, unsigned long>;
	using mat43ll = clmmat<4, 3, long long>;
	using mat43ull = clmmat<4, 3, unsigned long long>;

	using mat43_i8 = clmmat<4, 3, int8_t>;
	using mat43_u8 = clmmat<4, 3, uint8_t>;
	using mat43_i16 = clmmat<4, 3, int16_t>;
	using mat43_u16 = clmmat<4, 3, uint16_t>;
	using mat43_i32 = clmmat<4, 3, int32_t>;
	using mat43_u32 = clmmat<4, 3, uint32_t>;
	using mat43_i64 = clmmat<4, 3, int64_t>;
	using mat43_u64 = clmmat<4, 3, uint64_t>;

	template <typename T>
	using mat44 = clmmat<4, 4, T>;

	using mat44i = clmmat<4, 4, int>;
	using mat44u = clmmat<4, 4, unsigned int>;
	using mat44d = clmmat<4, 4, double>;
	using mat44ld = clmmat<4, 4, long double>;
	using mat44f = clmmat<4, 4, float>;
	using mat44b = clmmat<4, 4, bool>;

	using mat44l = clmmat<4, 4, long>;
	using mat44ul = clmmat<4, 4, unsigned long>;
	using mat44ll = clmmat<4, 4, long long>;
	using mat44ull = clmmat<4, 4, unsigned long long>;

	using mat44_i8 = clmmat<4, 4, int8_t>;
	using mat44_u8 = clmmat<4, 4, uint8_t>;
	using mat44_i16 = clmmat<4, 4, int16_t>;
	using mat44_u16 = clmmat<4, 4, uint16_t>;
	using mat44_i32 = clmmat<4, 4, int32_t>;
	using mat44_u32 = clmmat<4, 4, uint32_t>;
	using mat44_i64 = clmmat<4, 4, int64_t>;
	using mat44_u64 = clmmat<4, 4, uint64_t>;

#if defined(__STDCPP_FLOAT16_T__)

	using mat22_f16 = clmmat<2, 2, std::float16_t>;
	using mat23_f16 = clmmat<2, 3, std::float16_t>;
	using mat24_f16 = clmmat<2, 4, std::float16_t>;
	using mat32_f16 = clmmat<3, 2, std::float16_t>;
	using mat33_f16 = clmmat<3, 3, std::float16_t>;
	using mat34_f16 = clmmat<3, 4, std::float16_t>;
	using mat42_f16 = clmmat<4, 2, std::float16_t>;
	using mat43_f16 = clmmat<4, 3, std::float16_t>;
	using mat44_f16 = clmmat<4, 4, std::float16_t>;

#endif

#if defined(__STDCPP_FLOAT32_T__)

	using mat22_f32 = clmmat<2, 2, std::float32_t>;
	using mat23_f32 = clmmat<2, 3, std::float32_t>;
	using mat24_f32 = clmmat<2, 4, std::float32_t>;
	using mat32_f32 = clmmat<3, 2, std::float32_t>;
	using mat33_f32 = clmmat<3, 3, std::float32_t>;
	using mat34_f32 = clmmat<3, 4, std::float32_t>;
	using mat42_f32 = clmmat<4, 2, std::float32_t>;
	using mat43_f32 = clmmat<4, 3, std::float32_t>;
	using mat44_f32 = clmmat<4, 4, std::float32_t>;

#endif

#if defined(__STDCPP_FLOAT64_T__)

	using mat22_f64 = clmmat<2, 2, std::float64_t>;
	using mat23_f64 = clmmat<2, 3, std::float64_t>;
	using mat24_f64 = clmmat<2, 4, std::float64_t>;
	using mat32_f64 = clmmat<3, 2, std::float64_t>;
	using mat33_f64 = clmmat<3, 3, std::float64_t>;
	using mat34_f64 = clmmat<3, 4, std::float64_t>;
	using mat42_f64 = clmmat<4, 2, std::float64_t>;
	using mat43_f64 = clmmat<4, 3, std::float64_t>;
	using mat44_f64 = clmmat<4, 4, std::float64_t>;

#endif

#if defined(__STDCPP_FLOAT128_T__)

	using mat22_f128 = clmmat<2, 2, std::float128_t>;
	using mat23_f128 = clmmat<2, 3, std::float128_t>;
	using mat24_f128 = clmmat<2, 4, std::float128_t>;
	using mat32_f128 = clmmat<3, 2, std::float128_t>;
	using mat33_f128 = clmmat<3, 3, std::float128_t>;
	using mat34_f128 = clmmat<3, 4, std::float128_t>;
	using mat42_f128 = clmmat<4, 2, std::float128_t>;
	using mat43_f128 = clmmat<4, 3, std::float128_t>;
	using mat44_f128 = clmmat<4, 4, std::float128_t>;

#endif

#if defined(__STDCPP_BFLOAT16_T__)

	using mat22_bf16 = clmmat<2, 2, std::bfloat16_t>;
	using mat23_bf16 = clmmat<2, 3, std::bfloat16_t>;
	using mat24_bf16 = clmmat<2, 4, std::bfloat16_t>;
	using mat32_bf16 = clmmat<3, 2, std::bfloat16_t>;
	using mat33_bf16 = clmmat<3, 3, std::bfloat16_t>;
	using mat34_bf16 = clmmat<3, 4, std::bfloat16_t>;
	using mat42_bf16 = clmmat<4, 2, std::bfloat16_t>;
	using mat43_bf16 = clmmat<4, 3, std::bfloat16_t>;
	using mat44_bf16 = clmmat<4, 4, std::bfloat16_t>;

#endif

}

#endif // CLFE_CLMATH_MATDEF_H