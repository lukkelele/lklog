#pragma once

#include <string_view>
#include <vector>

#include "lklog/level.h"

namespace lklog::internal {

	struct log_module
	{
		std::string_view name;
		level lvl;
	};

	inline std::vector<const log_module*>& registry()
	{
		static std::vector<const log_module*> modules;
		return modules;
	}

	struct module_registrar
	{
		explicit module_registrar(const log_module* mod)
		{
			registry().push_back(mod);
		}
	};

	constexpr level resolve_level()
	{
		return level::info;
	}

	constexpr level resolve_level(level lvl)
	{
		return lvl;
	}

	void log(const log_module& module, level lvl, std::string_view msg);
}

#define LKLOG_MODULE_DECLARE(name)                                   \
	extern const ::lklog::internal::log_module _lklog_module_##name; \
	namespace lklog::internal {                                      \
		const ::lklog::internal::log_module* _lklog_module_ptr();    \
	}

#define LKLOG_MODULE_DEFINE(name, ...)                           \
	const ::lklog::internal::log_module _lklog_module_##name = { \
		#name,                                                   \
		::lklog::internal::resolve_level(__VA_ARGS__)            \
	};                                                           \
	static const ::lklog::internal::module_registrar             \
	  lklog_module_registrar_##name{ &_lklog_module_##name };    \
	namespace lklog::internal {                                  \
		const ::lklog::internal::log_module* _lklog_module_ptr() \
		{                                                        \
			return &_lklog_module_##name;                        \
		}                                                        \
	}

#define _LKLOG_MOD_LOG(_lvl, _fmt, ...)                                                           \
	do {                                                                                          \
		const auto* mod = ::lklog::internal::_lklog_module_ptr();                                 \
		if (mod && _lvl <= mod->lvl) {                                                            \
			::lklog::internal::log(*mod, _lvl, ::lklog::format(_fmt __VA_OPT__(, ) __VA_ARGS__)); \
		} else if (mod == nullptr) {                                                              \
			::lklog::log::print_msg(_lvl, _fmt __VA_OPT__(, ) __VA_ARGS__);                       \
		}                                                                                         \
	} while (0)

#define LKLOG_MOD_TRACE(fmt, ...) _LKLOG_MOD_LOG(::lklog::level::trace, fmt, ##__VA_ARGS__)
#define LKLOG_MOD_DEBUG(fmt, ...) _LKLOG_MOD_LOG(::lklog::level::debug, fmt, ##__VA_ARGS__)
#define LKLOG_MOD_INFO(fmt, ...)  _LKLOG_MOD_LOG(::lklog::level::info, fmt, ##__VA_ARGS__)
#define LKLOG_MOD_WARN(fmt, ...)  _LKLOG_MOD_LOG(::lklog::level::warn, fmt, ##__VA_ARGS__)
#define LKLOG_MOD_ERROR(fmt, ...) _LKLOG_MOD_LOG(::lklog::level::error, fmt, ##__VA_ARGS__)
#define LKLOG_MOD_FATAL(fmt, ...) _LKLOG_MOD_LOG(::lklog::level::fatal, fmt, ##__VA_ARGS__)

