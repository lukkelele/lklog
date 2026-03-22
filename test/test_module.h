#pragma once

#include <source_location>

#include <lklog/lklog.h>

#ifdef LKLOG_STD_PRINT
#	include <print>
#	define PRINTLN(...) std::println(__VA_ARGS__)
#else
#	define PRINTLN(...) std::printf("%s\n", __VA_ARGS__)
#endif

#define MODULE_DECLARED               1
#define MODULE_DEFINED_IN_TEST_MODULE 1

#if MODULE_DECLARED
LKLOG_MODULE_DECLARE(TestLogger);
#endif

inline void test_begin(const std::source_location _loc = std::source_location::current())
{
	std::println("---| START: {}:{}", _loc.file_name(), _loc.line());
}

inline void test_end(const std::source_location _loc = std::source_location::current())
{
	std::println("---| END:   {}:{}\n", _loc.file_name(), _loc.line());
}

