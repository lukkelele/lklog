#pragma once

#include <algorithm>
#include <filesystem>

#include "core.h"
#include "lklog/level.h"

namespace lklog::internal {

	bool compare_logfiles(const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b);
	std::size_t count_logfiles_in_dir(const std::filesystem::path& dir);
	void clean_log_dir(const std::filesystem::path& dir, std::size_t max_logfiles);

	constexpr const char* to_string(const level level)
	{
		switch (level) {
			case level::trace:   return "trace";
			case level::debug:	 return "debug";
			case level::info:	 return "info";
			case level::warn:    return "warn";
			case level::error:   return "error";
			case level::fatal:   return "fatal";
		}
		return nullptr;
	}

	constexpr level level_from_string(std::string_view str)
	{
		std::basic_string<char> str_lower(str);
		std::transform(str_lower.begin(), str_lower.end(), str_lower.begin(), [](char c)
		{
			return static_cast<char>(std::tolower(c));
		});

		if (str_lower == "trace")        return level::trace;
		else if (str_lower == "debug")   return level::debug;
		else if (str_lower == "info")    return level::info;
		else if (str_lower == "warn")    return level::warn;
		else if (str_lower == "error")   return level::error;
		else if (str_lower == "fatal")   return level::fatal;

		return level::info;
	}

}