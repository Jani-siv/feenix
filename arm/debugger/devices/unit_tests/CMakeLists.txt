set(TESTNAME Memory)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.8.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

project(${TESTNAME})

set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests/MemoryTests.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Memory.cpp
        )

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)

#REGISTERS UT

set(TESTNAME Registers)

project(${TESTNAME})

set(BASEPATH "${CMAKE_SOURCE_DIR}")
enable_testing()
set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests/RegistersTests.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/registers/Registers.cpp)

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)
