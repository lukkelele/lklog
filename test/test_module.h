#pragma once

#include <source_location>

#include <lklog/lklog.h>

#ifdef LKLOG_STD_PRINT
#	define PRINTLN(...) std::println(__VA_ARGS__)
#else
#	define PRINTLN(...) std::printf("%s\n", __VA_ARGS__)
#endif

LKLOG_MODULE_DECLARE(TestLogger);

void test_module_log_from_other_file();

