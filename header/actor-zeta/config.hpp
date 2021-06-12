#pragma once

namespace actor_zeta {

#ifndef CONFIG_NO_EXCEPTIONS
#if defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)
#define CONFIG_NO_EXCEPTIONS 0
#else
#define CONFIG_NO_EXCEPTIONS 1
#endif
#endif

#ifndef CPLUSPLUS
#if defined(_MSVC_LANG) && !defined(__clang__)
#define CPLUSPLUS (_MSC_VER == 1900 ? 201103L : _MSVC_LANG)
#else
#define CPLUSPLUS __cplusplus
#endif
#endif

#define COMPILER_VERSION(major, minor, patch) (10 * (10 * (major) + (minor)) + (patch))

#if defined(__clang__)
#define COMPILER_CLANG_VERSION COMPILER_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
#define COMPILER_CLANG_VERSION 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define COMPILER_GNUC_VERSION COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
#define COMPILER_GNUC_VERSION 0
#endif

#define CPP11_OR_GREATER (CPLUSPLUS >= 201103L)
#define CPP14_OR_GREATER (CPLUSPLUS >= 201402L)
#define CPP17_OR_GREATER (CPLUSPLUS >= 201703L)
#define CPP20_OR_GREATER (CPLUSPLUS >= 202000L)

#if CPP17_OR_GREATER && defined(__has_include)
#if __has_include(<any> )
#define HAVE_STD_ANY 1
#else
#define HAVE_STD_ANY 0
#endif
#else
#define HAVE_STD_ANY 0
#endif

#if CPP17_OR_GREATER && defined(__has_include)
#if __has_include(<string_view> )
#define HAVE_STD_STRING_VIEW 1
#else
#define HAVE_STD_STRING_VIEW 0
#endif
#else
#define HAVE_STD_STRING_VIEW 0
#endif

#define CACHE_LINE_SIZE 64

} // namespace actor_zeta
