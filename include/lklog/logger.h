#pragma once

#include <cstdio>
#include <filesystem>
#include <map>
#include <string>

#ifdef LKLOG_STD_PRINT
#include <print>
#endif

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/fmt.h>

#include "internal/ansi_color.h"
#include "internal/core.h"
#include "internal/formatters.h"
#include "level.h"

namespace lklog {

    enum class logger_type
    {
        core,
    };

    class logger
    {
    public:
        struct tag_details
        {
            bool enabled = true;
            level filter = level::debug;

            tag_details() = default;
            tag_details(const level in_filter) : filter(in_filter) {}
        };

        logger();
        ~logger() = default;

        static logger& get();

        static void init(std::string_view logfile = "");

		static std::shared_ptr<spdlog::logger>& get_logger(logger_type type);
		static std::string_view get_logger_name(logger_type type);

        template<typename... Args>
        static void print_msg(const logger_type type, const level Level, format_string<Args...> format, Args&&... args);

        template<typename... Args>
        static void print_msg_with_tag(logger_type type, const level Level, std::string_view Tag, format_string<Args...> format, Args&&... args);
        static void print_msg_with_tag(logger_type type, const level Level, std::string_view Tag, std::string_view Message);

        template<typename... Args>
        static void print_assert_msg(logger_type type, std::string_view prefix, format_string<Args...> Message, Args&&... args);
        static void print_assert_msg(logger_type type, std::string_view prefix);

		template<typename... Args>
		static void print(format_string<Args...> fmt, Args&&... args)
		{
		#ifdef LKLOG_STD_PRINT
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
		#ifdef LKLOG_STD_PRINT
			std::println("{}", lklog::format(fmt, std::forward<Args>(args)...));
		#else
			const std::string str = lklog::format(fmt, std::forward<Args>(args)...);
			std::printf("%s\n", str.c_str());
			std::fflush(stdout);
		#endif
		}

		static void set_level(level level);
		static void set_level(logger_type logger, level level);

    private:
        static inline std::map<std::string, tag_details> tags;
        static inline std::shared_ptr<spdlog::logger> logger_core = nullptr;
    };
}

#include "internal/log_impl.h"

/**
 * Standard print functions.
 */
#define LKLOG_PRINT(...)    ::lklog::logger::print(__VA_ARGS__)
#define LKLOG_PRINTLN(...)  ::lklog::logger::println(__VA_ARGS__)

/**
 * Core logging.
 */
#define LKLOG_TRACE(...)            ::lklog::logger::print_msg(::lklog::logger_type::core, ::lklog::level::trace, __VA_ARGS__)
#define LKLOG_DEBUG(...)            ::lklog::logger::print_msg(::lklog::logger_type::core, ::lklog::level::debug, __VA_ARGS__)
#define LKLOG_INFO(...)             ::lklog::logger::print_msg(::lklog::logger_type::core, ::lklog::level::info, __VA_ARGS__)
#define LKLOG_WARN(...)             ::lklog::logger::print_msg(::lklog::logger_type::core, ::lklog::level::warn, __VA_ARGS__)
#define LKLOG_ERROR(...)            ::lklog::logger::print_msg(::lklog::logger_type::core, ::lklog::level::error, __VA_ARGS__)
#define LKLOG_FATAL(...)            ::lklog::logger::print_msg(::lklog::logger_type::core, ::lklog::level::fatal, __VA_ARGS__)

#define LKLOG_TRACE_TAG(tag, ...)   ::lklog::logger::print_msg_with_tag(::lklog::logger_type::core, ::lklog::level::trace, tag, __VA_ARGS__)
#define LKLOG_DEBUG_TAG(tag, ...)   ::lklog::logger::print_msg_with_tag(::lklog::logger_type::core, ::lklog::level::debug, tag, __VA_ARGS__)
#define LKLOG_INFO_TAG(tag, ...)    ::lklog::logger::print_msg_with_tag(::lklog::logger_type::core, ::lklog::level::info, tag, __VA_ARGS__)
#define LKLOG_WARN_TAG(tag, ...)    ::lklog::logger::print_msg_with_tag(::lklog::logger_type::core, ::lklog::level::warn, tag, __VA_ARGS__)
#define LKLOG_ERROR_TAG(tag, ...)   ::lklog::logger::print_msg_with_tag(::lklog::logger_type::core, ::lklog::level::error, tag, __VA_ARGS__)
#define LKLOG_FATAL_TAG(tag, ...)   ::lklog::logger::print_msg_with_tag(::lklog::logger_type::core, ::lklog::level::fatal, tag, __VA_ARGS__)

