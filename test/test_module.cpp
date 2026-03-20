#include "test_module.h"

void test_module_log_from_other_file()
{
	constexpr auto loc = std::source_location::current();
	LKLOG_MOD_TRACE("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_DEBUG("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_INFO("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_WARN("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_ERROR("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_FATAL("Logging from -> {}:{}", loc.file_name(), loc.line());
	PRINTLN("");
}

