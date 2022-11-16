set(TESTNAME MemoryTests)

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

set(TESTNAME RegistersTests)

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

#mmu
set(TESTNAME MmuTests)

project(${TESTNAME})

set(BASEPATH "${CMAKE_SOURCE_DIR}")
enable_testing()
set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests/MmuTests.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Mmu.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/MemMsg.cpp
        ${CMAKE_SOURCE_DIR}/debugger/ElfLoader.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Memory.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Sections.cpp)

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)

#sections
set(TESTNAME SectionsTests)

project(${TESTNAME})

set(BASEPATH "${CMAKE_SOURCE_DIR}")
enable_testing()
set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests/SectionTests.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Sections.cpp)

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)

#dumpertests
set(TESTNAME DumpperTests)

project(${TESTNAME})

set(BASEPATH "${CMAKE_SOURCE_DIR}")
enable_testing()
set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests/DumpperTests.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/Dumpper.cpp)

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)

#ElfLoadertests
set(TESTNAME ElfLoaderTests)

project(${TESTNAME})

set(BASEPATH "${CMAKE_SOURCE_DIR}")
enable_testing()
set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests/ElfLoaderTests.cpp
        ${CMAKE_SOURCE_DIR}/debugger/ElfLoader.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/MemMsg.cpp)

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)

#cpuTests
set(TESTNAME CpuTests)

project(${TESTNAME})

set(BASEPATH "${CMAKE_SOURCE_DIR}")
enable_testing()
set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests/CoreTests.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/cpu/Core.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/registers/Registers.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Mmu.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/MemMsg.cpp
        ${CMAKE_SOURCE_DIR}/debugger/ElfLoader.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Memory.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Sections.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/Dumpper.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/cpu/Ticks.cpp
        )
enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)

#ticksTests
set(TESTNAME TicksTests)

project(${TESTNAME})

set(BASEPATH "${CMAKE_SOURCE_DIR}")
enable_testing()
set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests/TicksTests.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/cpu/Ticks.cpp)

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)
