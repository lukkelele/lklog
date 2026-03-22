#include <cstddef>

#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include "test_module.h"

#if MODULE_DECLARED && !MODULE_DEFINED_IN_TEST_MODULE
LKLOG_MODULE_DEFINE(TestLogger);
#endif

int main(int argc, char** argv)
{
	lklog::init(lklog::level::trace);
	return Catch::Session().run(argc, argv);
}

TEST_CASE("lklog_all", "[macros]")
{
	test_begin();
	LKLOG_INFO("Hello");
	LKLOG_INFO("Hello {}", "Lukas");
	LKLOG_WARN("warning from {} to {}", "Lukas", "lukkelele");
	test_end();
}

#ifdef _LKLOG_LOG_MACROS
TEST_CASE("standard", "[macros]")
{
	test_begin();
	LOG_TRACE("Logging with LOG_TRACE");
	LOG_TRACE("Logging with LOG_TRACE, {} {}", 123, "string arg");
	LOG_DEBUG("Logging with LOG_DEBUG");
	LOG_DEBUG("Logging with LOG_DEBUG, {} {} {}", 7.53f, 200, "lukas");
	LOG_INFO("Logging with LOG_INFO");
	LOG_INFO("Logging with LOG_INFO, {:.6f} {} {}", 145.53f, 200, "lukas");
	LOG_WARN("Logging with LOG_WARN");
	LOG_WARN("Logging with LOG_WARN, {:.2f} {} {}", 103.581f, 1.0, "lukkelele");
	LOG_ERROR("Logging with LOG_ERROR");
	LOG_ERROR("Logging with LOG_ERROR, {:.3f} {} {}", 103.581f, 1.0, "lukkelele");
	LOG_FATAL("Logging with LOG_FATAL");
	LOG_FATAL("Logging with LOG_FATAL, {:.9f} {} {}", 103.581f, 1.0, "lukkelele");
	test_end();
}
#endif

#ifdef _LKLOG_LOG_MACROS
TEST_CASE("standard_with_tags", "[macros]")
{
	test_begin();
	LOG_TRACE_TAG("subsystem", "Logging with LOG_TRACE");
	LOG_TRACE_TAG("subsystem", "Logging with LOG_TRACE, {} {}", 123, "string arg");
	LOG_DEBUG_TAG("subsystem", "Logging with LOG_DEBUG");
	LOG_DEBUG_TAG("subsystem", "Logging with LOG_DEBUG, {} {} {}", 7.53f, 200, "lukas");
	LOG_INFO_TAG("subsystem", "Logging with LOG_INFO");
	LOG_INFO_TAG("subsystem", "Logging with LOG_INFO, {:.6f} {} {}", 145.53f, 200, "lukas");
	LOG_WARN_TAG("subsystem", "Logging with LOG_WARN");
	LOG_WARN_TAG("subsystem", "Logging with LOG_WARN, {:.2f} {} {}", 103.581f, 1.0, "lukkelele");
	LOG_ERROR_TAG("subsystem", "Logging with LOG_ERROR");
	LOG_ERROR_TAG("subsystem", "Logging with LOG_ERROR, {:.3f} {} {}", 103.581f, 1.0, "lukkelele");
	LOG_FATAL_TAG("subsystem", "Logging with LOG_FATAL");
	LOG_FATAL_TAG("subsystem", "Logging with LOG_FATAL, {:.9f} {} {}", 103.581f, 1.0, "lukkelele");
	test_end();
}
#endif

TEST_CASE("all_levels", "[macro]")
{
	test_begin();
	LKLOG_TRACE("trace");
	LKLOG_TRACE("trace with {}", "formatted string arg");
	LKLOG_DEBUG("debug");
	LKLOG_DEBUG("debug {} {}", 123, "second arg");
	LKLOG_INFO("info");
	LKLOG_INFO("info with float {:.4f}", 2.50f);
	LKLOG_WARN("warn");
	LKLOG_ERROR("error");
	LKLOG_FATAL("error");
	test_end();
}

TEST_CASE("all_levels_with_tags", "[macro]")
{
	test_begin();
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
	test_end();
}

TEST_CASE("all_levels", "[function]")
{
	test_begin();
	lklog::log::trace("testing {} {:.3f}", 1, 5.20f);
	lklog::log::debug("testing {} {:.3f}", 1, 5.20f);
	lklog::log::info("testing {} {:.3f}", 1, 5.20f);
	lklog::log::warn("testing {} {:.3f}", 1, 5.20f);
	lklog::log::error("testing {} {:.3f}", 1, 5.20f);
	lklog::log::fatal("testing {} {:.3f}", 1, 5.20f);
	test_end();
}

TEST_CASE("all_levels_lklog_wrapped", "[function]")
{
	test_begin();
	lklog::trace("wrapped testing {} {:.3f}", 1, 5.20f);
	lklog::debug("wrapped testing {} {:.3f}", 1, 5.20f);
	lklog::info("wrapped testing {} {:.3f}", 1, 5.20f);
	lklog::warn("wrapped testing {} {:.3f}", 1, 5.20f);
	lklog::error("wrapped testing {} {:.3f}", 1, 5.20f);
	lklog::fatal("wrapped testing {} {:.3f}", 1, 5.20f);
	test_end();
}


TEST_CASE("println", "[function]")
{
	test_begin();
	lklog::log::println("message");
	lklog::log::println("message with some {}", "data");
	lklog::log::println("msg {} {}", "one", 2);
	lklog::log::println("println {} {}", 123, 2.0f);
	lklog::log::println("last print {} {}", "for sure", 4 * 5);
	test_end();
}

TEST_CASE("log_location", "[macro]")
{
	test_begin();
	constexpr auto loc = std::source_location::current();
	LKLOG_TRACE("logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_DEBUG("logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_INFO("logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_WARN("logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_ERROR("logging from -> {}:{}", loc.file_name(), loc.line());
	LKLOG_FATAL("logging from -> {}:{}", loc.file_name(), loc.line());
	test_end();
}

