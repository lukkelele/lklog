#pragma once

#include <source_location>

#include <lklog/lklog.h>

#ifdef LKLOG_STD_PRINT
#	define PRINTLN(...) std::println(__VA_ARGS__)
#else
#	define PRINTLN(...) std::printf("%s\n", __VA_ARGS__)
#endif

#define MODULE_DECLARED 1
#define MODULE_DEFINED_IN_TEST_MODULE 1

#if MODULE_DECLARED
LKLOG_MODULE_DECLARE(TestLogger);
#endif

void test_module_log_from_other_file();

