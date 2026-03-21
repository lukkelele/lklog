#pragma once

namespace lklog {

	template<typename... Args>
	LKLOG_INLINE void log::print_msg(const level level, format_string<Args...> fmt, Args&&... args)
	{
		auto* logger = get_logger();
		LKLOG_ASSERT(logger);
		switch (level) {
			case level::trace:
				logger->trace(fmt, std::forward<Args>(args)...);
				break;
			case level::debug:
				logger->debug(fmt, std::forward<Args>(args)...);
				break;
			case level::info:
				logger->info(fmt, std::forward<Args>(args)...);
				break;
			case level::warn:
				logger->warn(fmt, std::forward<Args>(args)...);
				break;
			case level::error:
				logger->error(fmt, std::forward<Args>(args)...);
				break;
			case level::fatal:
				logger->critical(fmt, std::forward<Args>(args)...);
				break;
		}
	}

	template<typename... Args>
	LKLOG_INLINE void log::print_msg_with_tag(const level level, std::string_view tag, format_string<Args...> fmt, Args&&... args)
	{
		auto* logger = get_logger();
		LKLOG_ASSERT(logger);
		switch (level) {
			case level::trace:
				logger->trace("[{}] {}", tag, lklog::format(fmt, std::forward<Args>(args)...));
				break;
			case level::debug:
				logger->debug("[{}] {}", tag, lklog::format(fmt, std::forward<Args>(args)...));
				break;
			case level::info:
				logger->info("[{}] {}", tag, lklog::format(fmt, std::forward<Args>(args)...));
				break;
			case level::warn:
				logger->warn("[{}] {}", tag, lklog::format(fmt, std::forward<Args>(args)...));
				break;
			case level::error:
				logger->error("[{}] {}", tag, lklog::format(fmt, std::forward<Args>(args)...));
				break;
			case level::fatal:
				logger->critical("[{}] {}", tag, lklog::format(fmt, std::forward<Args>(args)...));
				break;
		}
	}

	LKLOG_INLINE void log::print_msg_with_tag(const level level, std::string_view tag, std::string_view msg)
	{
		auto* logger = get_logger();
		LKLOG_ASSERT(logger);
		switch (level) {
			case level::trace:
				logger->trace("[{0}] {1}", tag, msg);
				break;
			case level::debug:
				logger->debug("[{0}] {1}", tag, msg);
				break;
			case level::info:
				logger->info("[{0}] {1}", tag, msg);
				break;
			case level::warn:
				logger->warn("[{0}] {1}", tag, msg);
				break;
			case level::error:
				logger->error("[{0}] {1}", tag, msg);
				break;
			case level::fatal:
				logger->critical("[{0}] {1}", tag, msg);
				break;
		}
	}

	template<typename... Args>
	LKLOG_INLINE void log::print_assert_msg(std::string_view prefix, format_string<Args...> fmt, Args&&... args)
	{
		if (auto logger = get_logger(); logger != nullptr) {
			logger->error("{}: {}", prefix, lklog::format(fmt, std::forward<Args>(args)...));
		} else {
			using namespace internal;
			log::println("{2}{0}: {1}{3}",
				prefix, lklog::format(fmt, std::forward<Args>(args)...),
				ansi_color::bg::bright_red, ansi_color::reset);
		}
	}

	LKLOG_INLINE void log::print_assert_msg(std::string_view msg)
	{
		if (auto logger = get_logger(); logger != nullptr) {
			logger->error("{0}", msg);
		} else {
			using namespace internal;
			log::println("{1}{0}{2}", msg, ansi_color::bg::bright_red, ansi_color::reset);
		}
	}
}
