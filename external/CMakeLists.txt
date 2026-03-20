#####################################################
# External dependencies.
#####################################################

# Catch2
if (LKLOG_BUILD_TESTS)
	add_subdirectory(Catch2)
endif()

# spdlog
if (LKLOG_COMPILER_MSVC)
	set(SPDLOG_USE_STD_FORMAT ON)
endif()
add_subdirectory(spdlog)

