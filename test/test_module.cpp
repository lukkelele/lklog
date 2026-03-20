#include "test_module.h"

#if MODULE_DEFINED_IN_TEST_MODULE
LKLOG_MODULE_DEFINE(TestLogger);
#endif

void test_module_log_from_other_file()
{
#if MODULE_DECLARED
	constexpr auto loc = std::source_location::current();
	LKLOG_MOD_TRACE("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_DEBUG("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_INFO("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_WARN("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_ERROR("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_MOD_FATAL("Logging from -> {}:{}", loc.file_name(), loc.line());
	PRINTLN("");
#endif
}

