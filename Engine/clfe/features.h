#ifndef CLFE_FEATURES_H
#define CLFE_FEATURES_H

// Macros use _ALL_CAPS, global variables use PascalCase, and most normal things use snake_case
// The engine uses a lot of c++ features so it has a base requirement of c++20

// Find compiler

#if defined(__clang__)
#define _CLANG
#define _COMPILER_NAME "clang"
#elif defined(__GNUC__)// || defined(__GNUG__)
#define _GCC
#define _COMPILER_NAME "gcc"
#elif defined(_MSC_VER)
#define _MSVC
#define _COMPILER_NAME "msvc"
#elif defined(__INTEL_LLVM_COMPILER)
// Somewhat unsupported as in a lot of assumptions were made about this compiler
#define _ICPX
#define _COMPILER_NAME "icpx"
#else
#define _COMPILER_NAME "unknown"
#endif

// Find c++ version date
#if defined(_MSVC)
#define _CPP_VERSION_LONG _MSVC_LANG
#else
#define _CPP_VERSION_LONG __cplusplus
#endif

// Find c++ version
#if _CPP_VERSION_LONG == 202603L
#define _CPP_VERSION 26
#elif _CPP_VERSION_LONG == 202302L
#define _CPP_VERSION 23
#elif _CPP_VERSION_LONG == 202002L
#define _CPP_VERSION 20
#elif _CPP_VERSION_LONG == 201703L
#define _CPP_VERSION 17
#elif _CPP_VERSION_LONG == 201402L
#define _CPP_VERSION 14
#elif _CPP_VERSION_LONG == 201103L
#define _CPP_VERSION 11
#elif _CPP_VERSION_LONG == 199711L
#define _CPP_VERSION 3
#else
#define _CPP_VERSION -1
#endif

// CLFE related macro work
// nothing yet

// Custom macros:
//#define _CLFE_KEEP_DEPRECATED (Note: due to cross-compiler complexity, deprecation warnings are not automatically suppressed by the engine and requires user configuration)
//#define _CLFE_CLMATH_COLUMN_MAJOR_MATRIX

// Note: consider implementing std::forward

namespace clfe
{

#if defined (_CPP_VERSION)
	constexpr int CppVersion = _CPP_VERSION;
#else
	constexpr int CppVersion = -1;
#endif

}

#endif // CLFE_FEATURES_H