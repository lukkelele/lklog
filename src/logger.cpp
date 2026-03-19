#include "lklog/logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "internal/context.h"
#include "internal/utility.h"

/* Internal debug logging. */
#ifdef LKLOG_DEBUG
#define LKLOG_LOG_PRINTLN(...) LKLOG_PRINTLN(__VA_ARGS__)
#else
#define LKLOG_LOG_PRINTLN(...)
#endif

namespace lklog {

	static std::string current_timestamp(std::string_view format = "%Y-%m-%d-%H%M%S")
    {
        using namespace std::chrono;
        time_point<system_clock> now = system_clock::now();
        std::time_t time = system_clock::to_time_t(now);

        std::stringstream stream;
        stream << std::put_time(std::localtime(&time), format.data());

        return stream.str();
    }

	logger::logger()
	{
		const auto& ctx = internal::context::get();
		LKLOG_LOG_PRINTLN("log directory: {}", ctx.log_directory);
	}

	logger& logger::get()
	{
		static logger inst;
		return inst;
	}

	void logger::init(std::string_view logfile)
	{
		get(); /* Make sure instance exists. */
		auto& ctx = internal::context::get();

		if (!logfile.empty()) {
			ctx.logfile = lklog::format("{}/{}-{}.log", ctx.log_directory, logfile, current_timestamp());
		} else {
			ctx.logfile = lklog::format("{}/{}-{}.log", ctx.log_directory, ctx.filename, current_timestamp());
		}
		LKLOG_LOG_PRINTLN("logfile: {}", ctx.logfile);

		std::vector<spdlog::sink_ptr> core_sinks = {
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(ctx.logfile, true),
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
		};

		internal::clean_log_dir(ctx.log_directory, 2);

		/**
		 * Index 0: file
		 * Index 1: stdout
		 */
		core_sinks[0]->set_pattern("[%T] [%l] [%n] %v");
		core_sinks[1]->set_pattern("%^[%T] [%l] %v%$");

		logger_core = std::make_shared<spdlog::logger>("CORE", core_sinks.begin(), core_sinks.end());
		logger_core->set_level(spdlog::level::trace);
		logger_core->flush_on(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& logger::get_logger(const logger_type type)
	{
		switch (type) {
			case logger_type::core: return logger_core;
		}
		LKLOG_ASSERT(false, "Unsupported logger type: {}", static_cast<int>(type));
		return logger_core;
	}

	std::string_view logger::get_logger_name(const logger_type type)
	{
		switch (type) {
			case logger_type::core: return logger_core->name();
		}
		LKLOG_ASSERT(false, "Unknown logger type: {}", static_cast<int>(type));
		return "";
	}

	void logger::set_level(const level level)
	{
		tag_details& details = tags[get_logger_name(logger_type::core).data()];
		details.filter = level;
	}

	void logger::set_level(const logger_type logger, const level level)
	{
		tag_details& details = tags[get_logger_name(logger).data()];
		details.filter = level;
	}

}

