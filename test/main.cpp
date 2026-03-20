#include <cstddef>
#include <print>

#include "test_module.h"

#if MODULE_DECLARED && !MODULE_DEFINED_IN_TEST_MODULE
LKLOG_MODULE_DEFINE(TestLogger);
#endif

static void test_log_macros_all_levels();
static void test_log_macros_all_levels_with_tag();
static void test_log_all_levels();
static void test_log_println();
static void test_module();

int main(int argc, char** argv)
{
	lklog::init(lklog::level::trace);

	test_log_macros_all_levels();
	test_log_macros_all_levels_with_tag();
	test_log_all_levels();
	test_log_println();

	test_module();

	LKLOG_MOD_INFO("Hello");
	LKLOG_MOD_INFO("Hello {}", "Lukas");
	PRINTLN("");

	test_module_log_from_other_file();

	return 0;
}

static void test_log_macros_all_levels()
{
	LKLOG_TRACE("trace");
	LKLOG_DEBUG("debug");
	LKLOG_INFO("info");
	LKLOG_WARN("warn");
	LKLOG_ERROR("error");
	LKLOG_FATAL("error");
	PRINTLN("");
}

static void test_log_macros_all_levels_with_tag()
{
	LKLOG_TRACE_TAG("tag", "trace");
	LKLOG_DEBUG_TAG("tag", "debug");
	LKLOG_INFO_TAG("tag", "info");
	LKLOG_WARN_TAG("tag", "warn");
	LKLOG_ERROR_TAG("tag", "error");
	LKLOG_FATAL_TAG("tag", "fatal");
	PRINTLN("");
}

static void test_log_all_levels()
{
	lklog::log::info("info log");
	PRINTLN("");
}

static void test_log_println()
{
	lklog::log::println("message");
	lklog::log::println("message with some {}", "data");
	lklog::log::println("msg {} {}", "one", 2);
	lklog::log::println("println {} {}", 123, 2.0f);
	lklog::log::println("last print {} {}", "for sure", 4 * 5);
	PRINTLN("");
}

static void test_module()
{
	constexpr auto loc = std::source_location::current();
	LKLOG_MOD_INFO("logging from -> {}:{}", loc.file_name(), loc.line());
}

