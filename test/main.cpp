#include <cstddef>
#include <print>

#include <lklog/internal/core.h>
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

	LKLOG_INFO("Hello");
	LKLOG_INFO("Hello {}", "Lukas");
	LKLOG_WARN("warning from {} to {}", "Lukas", "lukkelele");
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
	LKLOG_TRACE_TAG("tag", "trace longer message");
	LKLOG_TRACE_TAG("tag", "trace with {}", "formatted string arg");
	LKLOG_DEBUG_TAG("tag", "debug");
	LKLOG_DEBUG_TAG("tag", "debug {} {}", 123, "second arg");
	LKLOG_INFO_TAG("tag", "info");
	LKLOG_INFO_TAG("tag", "info with float {:.4f}", 2.50f);
	LKLOG_WARN_TAG("tag", "warn");
	LKLOG_WARN_TAG("second_tag", "warn a bit longer");
	LKLOG_ERROR_TAG("tag", "error");
	LKLOG_FATAL_TAG("tag", "fatal");
	PRINTLN("");
}

static void test_log_all_levels()
{
	lklog::log::trace("testing {} {:.3f}", 1, 5.20f);
	lklog::log::debug("testing {} {:.3f}", 1, 5.20f);
	lklog::log::info("testing {} {:.3f}", 1, 5.20f);
	lklog::log::warn("testing {} {:.3f}", 1, 5.20f);
	lklog::log::error("testing {} {:.3f}", 1, 5.20f);
	lklog::log::fatal("testing {} {:.3f}", 1, 5.20f);
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
	LKLOG_INFO("logging from -> {}:{}", loc.file_name(), loc.line());
}

