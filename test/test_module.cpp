#include "test_module.h"

#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#if MODULE_DEFINED_IN_TEST_MODULE
LKLOG_MODULE_DEFINE(TestLogger);
#endif

#if MODULE_DECLARED
TEST_CASE("separate_file", "[module]")
{
	test_begin();
	constexpr auto loc = std::source_location::current();
	LKLOG_TRACE("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_DEBUG("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_INFO("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_WARN("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_ERROR("Logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_FATAL("Logging from -> {}:{}", loc.file_name(), loc.line());
	test_end();
}
#endif

