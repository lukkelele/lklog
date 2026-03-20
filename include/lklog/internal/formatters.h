#pragma once

#include <string>
#include <filesystem>

#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "core.h"

namespace lklog::internal {

	class level_name_formatter final : public spdlog::custom_flag_formatter
	{
	public:
		void format(const spdlog::details::log_msg& msg, const std::tm& time, spdlog::memory_buf_t& dst) override
		{
			LKLOG_UNUSED(time);
			const std::string_view level_name = get_level_name(msg.level);
			dst.append(level_name.data(), level_name.data() + level_name.size());
		}

		[[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override
		{
			return spdlog::details::make_unique<level_name_formatter>();
		}

	private:
		[[nodiscard]] static std::string_view get_level_name(const spdlog::level::level_enum level)
		{
			switch (level) {
				case spdlog::level::trace:
					return "trace";
				case spdlog::level::debug:
					return "debug";
				case spdlog::level::info:
					return "info";
				case spdlog::level::warn:
					return "warn";
				case spdlog::level::err:
					return "error";
				case spdlog::level::critical:
					return "fatal";
				case spdlog::level::off:
					return "off";
				default:
					return "unknown";
			}
		}
	};
}

template<>
struct lklog::internal::fmt::formatter<std::filesystem::path> : lklog::internal::fmt::formatter<std::string>
{
	template<typename FormatContext>
	auto format(const std::filesystem::path& input, FormatContext& ctx) const
	{
		return lklog::internal::fmt::format_to(ctx.out(), "{}", input.generic_string());
	}
};

