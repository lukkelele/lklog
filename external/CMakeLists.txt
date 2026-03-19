#####################################################
# External dependencies.
#####################################################

# spdlog
if (LKLOG_COMPILER_MSVC)
	set(SPDLOG_USE_STD_FORMAT ON)
endif()
add_subdirectory(spdlog)

