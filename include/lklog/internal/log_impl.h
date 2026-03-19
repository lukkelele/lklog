#pragma once

namespace lklog {

	template<typename... Args>
	void logger::print_msg(const logger_type type, const level level, format_string<Args...> fmt, Args&&... args)
	{
		tag_details& details = tags[get_logger_name(type).data()];
		if (details.enabled && details.filter <= level) {
			auto& Logger = logger::get_logger(type);
			switch (level) {
				case level::trace:
					Logger->trace(fmt, std::forward<Args>(args)...);
					break;
				case level::debug:
					Logger->debug(fmt, std::forward<Args>(args)...);
					break;
				case level::info:
					Logger->info(fmt, std::forward<Args>(args)...);
					break;
				case level::warn:
					Logger->warn(fmt, std::forward<Args>(args)...);
					break;
				case level::error:
					Logger->error(fmt, std::forward<Args>(args)...);
					break;
				case level::fatal:
					Logger->critical(fmt, std::forward<Args>(args)...);
					break;
			}
		}
	}

	template<typename... Args>
	LKLOG_INLINE void logger::print_msg_with_tag(const logger_type type, const level level, std::string_view tag, format_string<Args...> fmt, Args&&... args)
	{
		const tag_details& details = tags[get_logger_name(type).data()];
		if (details.enabled && (details.filter <= level)) {
			const std::string msg = lklog::format(fmt, std::forward<Args>(args)...);
			auto& Logger = logger::get_logger(type);
			switch (level) {
				case level::trace:
					Logger->trace("[{0}] {1}", tag, msg);
					break;
				case level::debug:
					Logger->debug("[{0}] {1}", tag, msg);
					break;
				case level::info:
					Logger->info("[{0}] {1}", tag, msg);
					break;
				case level::warn:
					Logger->warn("[{0}] {1}", tag, msg);
					break;
				case level::error:
					Logger->error("[{0}] {1}", tag, msg);
					break;
				case level::fatal:
					Logger->critical("[{0}] {1}", tag, msg);
					break;
			}
		}
	}

	LKLOG_INLINE void logger::print_msg_with_tag(const logger_type type, const level level, std::string_view tag, std::string_view msg)
	{
		const tag_details& details = tags[get_logger_name(type).data()];
		if (details.enabled && details.filter <= level) {
			auto& Logger = get_logger(type);
			switch (level) {
				case level::trace:
					Logger->trace("[{0}] {1}", tag, msg);
					break;
				case level::debug:
					Logger->debug("[{0}] {1}", tag, msg);
					break;
				case level::info:
					Logger->info("[{0}] {1}", tag, msg);
					break;
				case level::warn:
					Logger->warn("[{0}] {1}", tag, msg);
					break;
				case level::error:
					Logger->error("[{0}] {1}", tag, msg);
					break;
				case level::fatal:
					Logger->critical("[{0}] {1}", tag, msg);
					break;
			}
		}
	}

	template<typename... Args>
	LKLOG_INLINE void logger::print_assert_msg(const logger_type type, std::string_view prefix, format_string<Args...> fmt, Args&&... args)
	{
		const std::string msg = format(fmt, std::forward<Args>(args)...);
		if (auto logger = get_logger(type); logger != nullptr) {
			logger->error("{0}: {1}", prefix, msg);
		} else {
			logger::println("{2}{0}: {1}{3}", prefix, msg, LKLOG_ANSI_COLOR_BG_BRIGHT_RED, LKLOG_ANSI_COLOR_RESET);
		}
	}

	LKLOG_INLINE void logger::print_assert_msg(const logger_type type, std::string_view msg)
	{
		if (auto logger = get_logger(type); logger != nullptr) {
			get_logger(type)->error("{0}", msg);
		} else {
			logger::println("{1}{0}{2}", msg, LKLOG_ANSI_COLOR_BG_BRIGHT_RED, LKLOG_ANSI_COLOR_RESET);
		}
	}
}
