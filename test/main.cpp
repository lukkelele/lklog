#include <cstddef>
#include <print>

#include <lklog/lklog.h>

int main(int argc, char** argv)
{
	lklog::init(lklog::level::trace);

	LKLOG_TRACE("trace");
	LKLOG_DEBUG("debug");
	LKLOG_INFO("info");
	LKLOG_WARN("warn");
	LKLOG_ERROR("error");

	std::println("\n");

	LKLOG_TRACE_TAG("module", "trace");
	LKLOG_DEBUG_TAG("module", "debug");
	LKLOG_INFO_TAG("module", "info");
	LKLOG_WARN_TAG("module", "warn");
	LKLOG_ERROR_TAG("module", "error");
	LKLOG_ERROR_TAG("module", "error");

	std::println("\n");

	lklog::logger::println("hejsan");
	lklog::logger::println("hejsan {}", "hoppsan");
	lklog::logger::println("hejsan {} {}", "hoppsan", "ookej");
	lklog::logger::println("hejsan {} {}", "hoppsan", 123);
	lklog::logger::println("hejsan {} {}", "hoppsan", 4 * 5);

	return 0;
}
