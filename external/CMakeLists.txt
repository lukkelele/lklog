#####################################################
# External dependencies.
#####################################################

# Catch2
if (LKLOG_BUILD_TESTS)
	if (NOT Catch2_FOUND)
		add_subdirectory(Catch2)
	endif()
endif()

# spdlog
if (SPDLOG_FOUND)
    if (MSVC)
        set(SPDLOG_USE_STD_FORMAT ON)
    endif()
    add_subdirectory(spdlog)
endif()

