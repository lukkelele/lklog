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

	static const log_module* _lklog_module_ptr = nullptr;

	void log(const log_module& module, level lvl, std::string_view msg);
}

#define LKLOG_MODULE_DECLARE(name)                                   \
	extern const ::lklog::internal::log_module _lklog_module_##name;

#define LKLOG_MODULE_DEFINE(name, ...)                             \
	const ::lklog::internal::log_module _lklog_module_##name = {   \
		#name,                                                     \
		::lklog::internal::resolve_level(__VA_ARGS__)              \
	};                                                             \
	static const ::lklog::internal::module_registrar               \
	  lklog_module_registrar_##name{ &_lklog_module_##name };      \
	namespace lklog::internal {                                    \
		struct _lklog_module_assigner                              \
		{                                                          \
			_lklog_module_assigner()                               \
			{                                                      \
				LKLOG_ASSERT(_lklog_module_ptr == nullptr);        \
				_lklog_module_ptr = &_lklog_module_##name;         \
			}                                                      \
		};                                                         \
		static _lklog_module_assigner _lklog_module_assigner_inst; \
	}

#define _LKLOG_MOD_LOG(_lvl, ...)                                             \
	do {                                                                      \
		const auto* mod = ::lklog::internal::_lklog_module_ptr;               \
		if (mod && _lvl <= mod->lvl) {                                        \
			::lklog::internal::log(*mod, _lvl, ::lklog::format(__VA_ARGS__)); \
		} else if (mod == nullptr) {                                          \
			::lklog::log::print_msg(_lvl, __VA_ARGS__);                       \
		}                                                                     \
	} while (0)

