cmake_minimum_required(VERSION 3.20...4.0)
project(lklog-test LANGUAGES C CXX)

set(TEST_TARGET ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${TEST_TARGET}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_module.cpp
)

if (LKLOG_STD_PRINT)
    target_compile_definitions(${TEST_TARGET} PRIVATE 
        LKLOG_STD_PRINT=1
    )
endif()

target_link_libraries(${TEST_TARGET} PRIVATE lklog::lklog)

set_target_properties(${TEST_TARGET} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
)

