#pragma once

#include "internal/module.h"
#include "log.h"

namespace lklog {

	void init(level lvl = level::info, std::string_view logfile = "");

	template<typename... Args>
	inline void trace(format_string<Args...> fmt, Args&&... args)
	{
		log::trace("{}", lklog::format(fmt, std::forward<Args>(args)...));
	}

	template<typename... Args>
	inline void debug(format_string<Args...> fmt, Args&&... args)
	{
		log::debug("{}", lklog::format(fmt, std::forward<Args>(args)...));
	}

	template<typename... Args>
	inline void info(format_string<Args...> fmt, Args&&... args)
	{
		log::info("{}", lklog::format(fmt, std::forward<Args>(args)...));
	}

	template<typename... Args>
	inline void warn(format_string<Args...> fmt, Args&&... args)
	{
		log::warn("{}", lklog::format(fmt, std::forward<Args>(args)...));
	}

	template<typename... Args>
	inline void error(format_string<Args...> fmt, Args&&... args)
	{
		log::error("{}", lklog::format(fmt, std::forward<Args>(args)...));
	}

	template<typename... Args>
	inline void fatal(format_string<Args...> fmt, Args&&... args)
	{
		log::fatal("{}", lklog::format(fmt, std::forward<Args>(args)...));
	}

}
