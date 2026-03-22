#pragma once

#include <filesystem>
#include <map>
#include <string>

#ifdef _LKLOG_STD_PRINT
#	include <print>
#endif

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/fmt.h>

#include "internal/ansi_color.h"
#include "internal/core.h"
#include "internal/formatters.h"
#include "internal/module.h"
#include "level.h"

namespace lklog {

	class log
	{
	private:
		log();

	public:
		log(log&&) = delete;
		log(const log&) = delete;
		~log() = default;

		log& operator=(log&&) = delete;
		log& operator=(const log&) = delete;

		static log& get();
		static void init(level lvl = level::info, std::string_view logfile = "");
		static void set_level(level level);

		template<typename... Args>
		static void print(format_string<Args...> fmt, Args&&... args)
		{
#ifdef _LKLOG_STD_PRINT
			std::print("{}", lklog::format(fmt, std::forward<Args>(args)...));
#else
			const std::string str = lklog::format(fmt, std::forward<Args>(args)...);
			std::printf("%s", str.c_str());
			std::fflush(stdout);
#endif
		}

		template<typename... Args>
		static void println(format_string<Args...> fmt, Args&&... args)
		{
#ifdef _LKLOG_STD_PRINT
			std::println("{}", lklog::format(fmt, std::forward<Args>(args)...));
#else
			const std::string str = lklog::format(fmt, std::forward<Args>(args)...);
			std::printf("%s\n", str.c_str());
			std::fflush(stdout);
#endif
		}

		template<typename... Args>
		static void print_msg(level Level, format_string<Args...> format, Args&&... args);

		template<typename... Args>
		static void print_msg_with_tag(level Level, std::string_view Tag, format_string<Args...> format, Args&&... args);
		static void print_msg_with_tag(level Level, std::string_view Tag, std::string_view Message);

		template<typename... Args>
		static void print_assert_msg(std::string_view prefix, format_string<Args...> Message, Args&&... args);
		static void print_assert_msg(std::string_view prefix);

		template<typename... Args>
		static void trace(format_string<Args...> fmt, Args&&... args)
		{
			print_msg(level::trace, "{}", lklog::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void debug(format_string<Args...> fmt, Args&&... args)
		{
			print_msg(level::debug, "{}", lklog::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void info(format_string<Args...> fmt, Args&&... args)
		{
			print_msg(level::info, "{}", lklog::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void warn(format_string<Args...> fmt, Args&&... args)
		{
			print_msg(level::warn, "{}", lklog::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void error(format_string<Args...> fmt, Args&&... args)
		{
			print_msg(level::error, "{}", lklog::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void fatal(format_string<Args...> fmt, Args&&... args)
		{
			print_msg(level::fatal, "{}", lklog::format(fmt, std::forward<Args>(args)...));
		}

	private:
		_LKLOG_FORCEINLINE static spdlog::logger* get_logger() { return logger_impl.get(); }

	private:
		static inline std::unique_ptr<spdlog::logger> logger_impl;
	};
}

#define LKLOG_PRINT(...)   ::lklog::log::print(__VA_ARGS__)
#define LKLOG_PRINTLN(...) ::lklog::log::println(__VA_ARGS__)

#define LKLOG_TRACE(...) _LKLOG_MOD_LOG(::lklog::level::trace, ##__VA_ARGS__)
#define LKLOG_DEBUG(...) _LKLOG_MOD_LOG(::lklog::level::debug, ##__VA_ARGS__)
#define LKLOG_INFO(...)  _LKLOG_MOD_LOG(::lklog::level::info, ##__VA_ARGS__)
#define LKLOG_WARN(...)  _LKLOG_MOD_LOG(::lklog::level::warn, ##__VA_ARGS__)
#define LKLOG_ERROR(...) _LKLOG_MOD_LOG(::lklog::level::error, ##__VA_ARGS__)
#define LKLOG_FATAL(...) _LKLOG_MOD_LOG(::lklog::level::fatal, ##__VA_ARGS__)

#define LKLOG_TRACE_TAG(tag, ...) ::lklog::log::print_msg_with_tag(::lklog::level::trace, tag, __VA_ARGS__)
#define LKLOG_DEBUG_TAG(tag, ...) ::lklog::log::print_msg_with_tag(::lklog::level::debug, tag, __VA_ARGS__)
#define LKLOG_INFO_TAG(tag, ...)  ::lklog::log::print_msg_with_tag(::lklog::level::info, tag, __VA_ARGS__)
#define LKLOG_WARN_TAG(tag, ...)  ::lklog::log::print_msg_with_tag(::lklog::level::warn, tag, __VA_ARGS__)
#define LKLOG_ERROR_TAG(tag, ...) ::lklog::log::print_msg_with_tag(::lklog::level::error, tag, __VA_ARGS__)
#define LKLOG_FATAL_TAG(tag, ...) ::lklog::log::print_msg_with_tag(::lklog::level::fatal, tag, __VA_ARGS__)

#ifdef _LKLOG_LOG_MACROS
#	if defined(LOG_TRACE) || defined(LOG_DEBUG) || defined(LOG_INFO) || defined(LOG_ERROR) || defined(LOG_FATAL)
#		error "Log macros are occupied"
#	endif
#	define LOG_TRACE(...) LKLOG_TRACE(__VA_ARGS__)
#	define LOG_DEBUG(...) LKLOG_DEBUG(__VA_ARGS__)
#	define LOG_INFO(...)  LKLOG_INFO(__VA_ARGS__)
#	define LOG_WARN(...)  LKLOG_WARN(__VA_ARGS__)
#	define LOG_ERROR(...) LKLOG_ERROR(__VA_ARGS__)
#	define LOG_FATAL(...) LKLOG_FATAL(__VA_ARGS__)
#
#	define LOG_TRACE_TAG(_tag, ...) LKLOG_TRACE_TAG(_tag, __VA_ARGS__)
#	define LOG_DEBUG_TAG(_tag, ...) LKLOG_DEBUG_TAG(_tag, __VA_ARGS__)
#	define LOG_INFO_TAG(_tag, ...)  LKLOG_INFO_TAG(_tag, __VA_ARGS__)
#	define LOG_WARN_TAG(_tag, ...)  LKLOG_WARN_TAG(_tag, __VA_ARGS__)
#	define LOG_ERROR_TAG(_tag, ...) LKLOG_ERROR_TAG(_tag, __VA_ARGS__)
#	define LOG_FATAL_TAG(_tag, ...) LKLOG_FATAL_TAG(_tag, __VA_ARGS__)
#endif /* _LK_LOG_MACROS */

#include "internal/log_impl.h"

