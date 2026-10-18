#ifndef CLFE_CLMATH_VECDEF_H
#define CLFE_CLMATH_VECDEF_H

#include <cstdint>

#include "clfe/features.h"
#if _CPP_VERSION >= 23
#include <stdfloat>
#endif

#include "mdef.h"
#include "vec.h"

namespace clfe
{

	template <clmsize_t Size, typename T>
	using vec = clmvec<Size, T>;

	template <typename T>
	using vec2 = clmvec<2, T>;

	using vec2i = clmvec<2, int>;
	using vec2u = clmvec<2, unsigned int>;
	using vec2d = clmvec<2, double>;
	using vec2ld = clmvec<2, long double>;
	using vec2f = clmvec<2, float>;
	using vec2b = clmvec<2, bool>;

	using vec2l = clmvec<2, long>;
	using vec2ul = clmvec<2, unsigned long>;
	using vec2ll = clmvec<2, long long>;
	using vec2ull = clmvec<2, unsigned long long>;

	using vec2_i8 = clmvec<2, int8_t>;
	using vec2_u8 = clmvec<2, uint8_t>;
	using vec2_i16 = clmvec<2, int16_t>;
	using vec2_u16 = clmvec<2, uint16_t>;
	using vec2_i32 = clmvec<2, int32_t>;
	using vec2_u32 = clmvec<2, uint32_t>;
	using vec2_i64 = clmvec<2, int64_t>;
	using vec2_u64 = clmvec<2, uint64_t>;

	template <typename T>
	using vec3 = clmvec<3, T>;

	using vec3i = clmvec<3, int>;
	using vec3u = clmvec<3, unsigned int>;
	using vec3d = clmvec<3, double>;
	using vec3ld = clmvec<3, long double>;
	using vec3f = clmvec<3, float>;
	using vec3b = clmvec<3, bool>;

	using vec3l = clmvec<3, long>;
	using vec3ul = clmvec<3, unsigned long>;
	using vec3ll = clmvec<3, long long>;
	using vec3ull = clmvec<3, unsigned long long>;

	using vec3_i8 = clmvec<3, int8_t>;
	using vec3_u8 = clmvec<3, uint8_t>;
	using vec3_i16 = clmvec<3, int16_t>;
	using vec3_u16 = clmvec<3, uint16_t>;
	using vec3_i32 = clmvec<3, int32_t>;
	using vec3_u32 = clmvec<3, uint32_t>;
	using vec3_i64 = clmvec<3, int64_t>;
	using vec3_u64 = clmvec<3, uint64_t>;

	template <typename T>
	using vec4 = clmvec<4, T>;

	using vec4i = clmvec<4, int>;
	using vec4u = clmvec<4, unsigned int>;
	using vec4d = clmvec<4, double>;
	using vec4ld = clmvec<4, long double>;
	using vec4f = clmvec<4, float>;
	using vec4b = clmvec<4, bool>;

	using vec4l = clmvec<4, long>;
	using vec4ul = clmvec<4, unsigned long>;
	using vec4ll = clmvec<4, long long>;
	using vec4ull = clmvec<4, unsigned long long>;

	using vec4_i8 = clmvec<4, int8_t>;
	using vec4_u8 = clmvec<4, uint8_t>;
	using vec4_i16 = clmvec<4, int16_t>;
	using vec4_u16 = clmvec<4, uint16_t>;
	using vec4_i32 = clmvec<4, int32_t>;
	using vec4_u32 = clmvec<4, uint32_t>;
	using vec4_i64 = clmvec<4, int64_t>;
	using vec4_u64 = clmvec<4, uint64_t>;

#if defined(__STDCPP_FLOAT16_T__)

	using vec2_f16 = clmvec<2, std::float16_t>;
	using vec3_f16 = clmvec<3, std::float16_t>;
	using vec4_f16 = clmvec<4, std::float16_t>;

#endif

#if defined(__STDCPP_FLOAT32_T__)

	using vec2_f32 = clmvec<2, std::float32_t>;
	using vec3_f32 = clmvec<3, std::float32_t>;
	using vec4_f32 = clmvec<4, std::float32_t>;

#endif

#if defined(__STDCPP_FLOAT64_T__)

	using vec2_f64 = clmvec<2, std::float64_t>;
	using vec3_f64 = clmvec<3, std::float64_t>;
	using vec4_f64 = clmvec<4, std::float64_t>;

#endif

#if defined(__STDCPP_FLOAT128_T__)

	using vec2_f128 = clmvec<2, std::float128_t>;
	using vec3_f128 = clmvec<3, std::float128_t>;
	using vec4_f128 = clmvec<4, std::float128_t>;

#endif

#if defined(__STDCPP_BFLOAT16_T__)

	using vec2_bf16 = clmvec<2, std::bfloat16_t>;
	using vec3_bf16 = clmvec<3, std::bfloat16_t>;
	using vec4_bf16 = clmvec<4, std::bfloat16_t>;

#endif

}

#endif // CLFE_CLMATH_VECDEF_H