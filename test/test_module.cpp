#include "test_module.h"

#if MODULE_DEFINED_IN_TEST_MODULE
LKLOG_MODULE_DEFINE(TestLogger);
#endif

void test_module_log_from_other_file()
{
#if MODULE_DECLARED
	constexpr auto loc = std::source_location::current();
	LKLOG_TRACE("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_DEBUG("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_INFO("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_WARN("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_ERROR("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_FATAL("Logging from -> {}:{}", loc.file_name(), loc.line());
	PRINTLN("");
#endif
}

