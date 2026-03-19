#pragma once

#include "core.h"

namespace lklog::internal {
	struct log_module
	{
		std::string_view name;
	};
}


#define LKLOG_MODULE_DEFINE(name, ...) \
	extern ::lklog::internal::log_module _

