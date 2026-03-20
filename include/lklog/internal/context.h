#pragma once

#include <string>
#include <filesystem>

#include "lklog_config.h"

namespace lklog::internal {
	struct context
	{
		static constexpr std::string_view filename = "lklog";
		std::string logfile;
		std::filesystem::path log_directory = LKLOG_LOGS_DIR; /* @todo: Make optional */

		static context& get()
		{
			static context ctx;
			return ctx;
		}
	};
}
