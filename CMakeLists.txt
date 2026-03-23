cmake_minimum_required(VERSION 3.20...4.0)
project(lklog LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LKLOG_ADD_LOG_MACROS "Add log macros (LOG_DEBUG, LOG_INFO, ...)" ON)
option(LKLOG_BUILD_TESTS "Build tests" ON)
option(LKLOG_STD_PRINT "Use std::print" ON)
option(LKLOG_ENABLE_ASSERT "Enable asserts" OFF)
option(LKLOG_INTERNAL_DEBUG "Enable internal debug logs" OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif ()

#-------------------------------------------------------------------
# C++ version
#-------------------------------------------------------------------
if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
	if (CMAKE_CXX_STANDARD LESS 20)
		message(FATAL_ERROR "lklog requires at least C++20")
	endif()

	if (CMAKE_CXX_STANDARD LESS 23)
		set(LKLOG_STD_PRINT OFF CACHE BOOL "" FORCE)
	endif()
endif()

set(LKLOG_DEBUG OFF)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LKLOG_ENABLE_ASSERT ON)
	set(LKLOG_DEBUG ON)
endif()


#-------------------------------------------------------------------
# Target
#-------------------------------------------------------------------
set(HEADER_FILES
	include/lklog/lklog.h
	include/lklog/log.h
	include/lklog/internal/ansi_color.h
	include/lklog/internal/context.h
	include/lklog/internal/core.h
	include/lklog/internal/formatters.h
	include/lklog/internal/log_impl.h
	include/lklog/internal/module.h
	include/lklog/internal/utility.h
)
set(SOURCE_FILES
	src/lklog.cpp
	src/log.cpp
	src/utility.cpp
)

set(LKLOG_TARGET ${PROJECT_NAME})
add_library(${LKLOG_TARGET} STATIC ${SOURCE_FILES})
add_library(lklog:lklog ALIAS ${LKLOG_TARGET})
target_sources(${LKLOG_TARGET} PRIVATE ${HEADER_FILES})
target_include_directories(${LKLOG_TARGET} PUBLIC include)
target_include_directories(${LKLOG_TARGET} PRIVATE
	include/lklog
)

if (LKLOG_ADD_LOG_MACROS)
    target_compile_definitions(${LKLOG_TARGET} PUBLIC _LKLOG_LOG_MACROS)
endif()

if (LKLOG_INTERNAL_DEBUG)
    target_compile_definitions(${LKLOG_TARGET} PRIVATE LKLOG_INTERNAL_DEBUG)
endif()

if (LKLOG_STD_PRINT)
    target_compile_definitions(${LKLOG_TARGET} PUBLIC _LKLOG_STD_PRINT)
endif()


#-------------------------------------------------------------------
# Configuration.
#-------------------------------------------------------------------
if (MSVC)
	target_compile_definitions(${LKLOG_TARGET} PRIVATE
		_CRT_SECURE_NO_WARNINGS
	)
	target_compile_definitions(${LKLOG_TARGET} PUBLIC
		SPDLOG_USE_STD_FORMAT
		_LKLOG_COMPILER_MSVC
		_LKLOG_VA_OPT # /Zc:preprocessor
	)

	target_compile_options(${LKLOG_TARGET} PUBLIC
		/Zc:__cplusplus
		/Zc:preprocessor
		/utf-8
	)

	# Disable warnings.
	target_compile_options(${LKLOG_TARGET} PRIVATE
		/wd4068   # Unknown #pragma mark
		/wd4267   # Possible loss of data
		/wd4244   # Possible loss of data
		/wd4312   # Conversion of greater size
		/wd28020  # Static analysis warning
		/wd33011  # Static analysis warning
		/wd4307
		/wd26451
		/wd26813  # 'Use bitwise and'
	)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_compile_definitions(${LKLOG_TARGET} PUBLIC
		_LKLOG_COMPILER_GCC
		_LKLOG_VA_OPT
	)
	target_compile_options(${LKLOG_TARGET} PRIVATE
		-Wno-format-security
		-Wno-format
	)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	target_compile_definitions(${LKLOG_TARGET} PUBLIC
		_LKLOG_COMPILER_CLANG
		_LKLOG_VA_OPT
	)
	target_compile_options(${LKLOG_TARGET} PRIVATE
		-Wno-format-security
		-Wno-format
	)
endif()


#-------------------------------------------------------------------
# Dependencies.
#-------------------------------------------------------------------
set(SPDLOG_FOUND ON)
add_subdirectory(external)
target_include_directories(${LKLOG_TARGET} PUBLIC
	external/spdlog/include
)
target_link_libraries(${LKLOG_TARGET} PUBLIC
	spdlog::spdlog
)


#-------------------------------------------------------------------
# Generated files.
#-------------------------------------------------------------------
set(LKLOG_PROJECT_DIR "${CMAKE_SOURCE_DIR}")
set(LKLOG_BINARY_DIR "${CMAKE_BINARY_DIR}")
make_directory(${CMAKE_BINARY_DIR}/intermediate)
configure_file(
    include/lklog/internal/config.h.in
    ${CMAKE_BINARY_DIR}/intermediate/lklog_config.h
)
target_include_directories(${LKLOG_TARGET} PUBLIC ${CMAKE_BINARY_DIR}/intermediate)


#-------------------------------------------------------------------
# Tests
#-------------------------------------------------------------------
if (LKLOG_BUILD_TESTS)
	# TODO: Should check if Catch2 is present in current project
	find_package(Catch2 REQUIRED)
	set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
	add_subdirectory(test)
endif()

