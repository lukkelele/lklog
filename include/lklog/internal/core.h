#pragma once

/* NOLINTBEGIN(misc-unused-alias-decls) */
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>

#ifdef SPDLOG_USE_STD_FORMAT
#include <format>
#else
#include <spdlog/fmt/fmt.h>
#endif

#include "lklog_config.h"
/* NOLINTEND(misc-unused-alias-decls) */

#define LKLOG_UNUSED(...)       (void)(sizeof(__VA_ARGS__))
#define LKLOG_ARRAYSIZE(Array)  (static_cast<std::size_t>((sizeof(Array) / sizeof(*(Array)))))
#define LKLOG_STRINGIFY(x)      #x

#if defined(LKLOG_COMPILER_MSVC)
#	define LKLOG_FORCEINLINE  __forceinline
#	define LKLOG_CDECL        __cdecl
#	define LKLOG_STDCALL      __stdcall
#elif defined(LKLOG_COMPILER_GCC)
#	define LKLOG_FORCEINLINE  inline __attribute__((always_inline))
#	define LKLOG_CDECL        __attribute__((cdecl))
#	define LKLOG_STDCALL      __attribute__((stdcall))
#elif defined(LKLOG_COMPILER_CLANG)
#	define LKLOG_FORCEINLINE  __forceinline
#	define LKLOG_CDECL        __cdecl
#	define LKLOG_STDCALL      __stdcall
#endif

#if LKLOG_FORCE_INLINE
#define LKLOG_INLINE LKLOG_FORCEINLINE
#else
#define LKLOG_INLINE inline
#endif

#define LKLOG_CONCAT(a, b)        a##b
#define LKLOG_CONCAT_EXPAND(a, b) LKLOG_CONCAT(a, b)

namespace lklog {

    namespace internal {
	#ifdef SPDLOG_USE_STD_FORMAT
		namespace fmt = ::std;
	#else
		namespace fmt = ::fmt;
	#endif
    }

    template<typename... Args>
    using format_string = internal::fmt::format_string<Args...>;

    template<typename... Args>
    inline std::string format(format_string<Args...> fmt, Args&&... args)
    {
        return internal::fmt::format(fmt, std::forward<Args>(args)...);
    }
}

/** @todo: Proper assert handling */
#define LKLOG_ASSERT(Condition, ...) assert(Condition)

