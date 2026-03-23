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
			static constexpr std::string_view pad_str{"     "};
			constexpr int width = pad_str.size();
			const std::string_view lvl = to_string(msg.level);

			if (lvl.size() < width) {
				dst.append(lvl.data(), lvl.data() + lvl.size());
				const int padding = width - static_cast<int>(lvl.size());
				dst.append(pad_str.data(), pad_str.data() + padding);
			} else {
				dst.append(lvl.data(), lvl.data() + lvl.size());
			}
		}

		[[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override
		{
			return spdlog::details::make_unique<level_name_formatter>();
		}

	private:
		[[nodiscard]] static constexpr std::string_view to_string(const spdlog::level::level_enum level)
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
struct lklog::fmt::formatter<std::filesystem::path> : lklog::fmt::formatter<std::string>
{
	template<typename FormatContext>
	auto format(const std::filesystem::path& input, FormatContext& ctx) const
	{
		return lklog::fmt::format_to(ctx.out(), "{}", input.generic_string());
	}
};

