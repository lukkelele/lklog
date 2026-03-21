#include "lklog/log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "internal/context.h"
#include "internal/module.h"
#include "internal/utility.h"

/* Internal debug logging. */
#ifdef LKLOG_INTERNAL_DEBUG
#	define LKLOG_LOG_PRINTLN(...) LKLOG_PRINTLN(__VA_ARGS__)
#else
#	define LKLOG_LOG_PRINTLN(...)
#endif

namespace lklog {

	static std::unique_ptr<spdlog::formatter> create_console_formatter()
	{
		auto formatter = std::make_unique<spdlog::pattern_formatter>();
		formatter->add_flag<lklog::internal::level_name_formatter>('L');
		formatter->set_pattern("%^[%T] [%L] %v%$");
		return formatter;
	}

	static std::unique_ptr<spdlog::formatter> create_file_formatter()
	{
		auto formatter = std::make_unique<spdlog::pattern_formatter>();
		formatter->add_flag<lklog::internal::level_name_formatter>('L');
		formatter->set_pattern("[%T] [%L] [%n] %v");
		return formatter;
	}

	log::log()
	{
		const auto& ctx = internal::context::get();
		LKLOG_LOG_PRINTLN("log directory: {}", ctx.log_directory);
	}

	log& log::get()
	{
		static log inst;
		return inst;
	}

	void log::init(std::string_view logfile)
	{
		get(); /* Make sure instance exists. */
		auto& ctx = internal::context::get();

		if (!logfile.empty()) {
			ctx.logfile = lklog::format("{}/{}-{}.log", ctx.log_directory, logfile, internal::current_timestamp());
		} else {
			ctx.logfile = lklog::format("{}/{}-{}.log", ctx.log_directory, ctx.filename, internal::current_timestamp());
		}
		LKLOG_LOG_PRINTLN("logfile: {}", ctx.logfile);

		internal::clean_log_dir(ctx.log_directory, 2);

		std::vector<spdlog::sink_ptr> sinks = {
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(ctx.logfile, true),
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
		};

		/**
		 * Index 0: file
		 * Index 1: stdout
		 */
		sinks[0]->set_formatter(create_file_formatter());
		sinks[1]->set_formatter(create_console_formatter());

		logger_impl = std::make_unique<spdlog::logger>("lklog", sinks.begin(), sinks.end());
		logger_impl->set_level(spdlog::level::trace);
		logger_impl->flush_on(spdlog::level::trace);
	}

	static constexpr spdlog::level::level_enum to_spdlog_level(const level level)
	{
		switch (level) {
			case level::trace: return spdlog::level::trace;
			case level::debug: return spdlog::level::debug;
			case level::info:  return spdlog::level::info;
			case level::warn:  return spdlog::level::warn;
			case level::error: return spdlog::level::err;
			case level::fatal: return spdlog::level::critical;
		}
		return spdlog::level::info;
	}

	void log::set_level(const level level)
	{
		auto logger = get_logger();
		LKLOG_ASSERT(logger);
		logger->set_level(to_spdlog_level(level));
	}

}

