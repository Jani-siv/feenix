cmake_minimum_required (VERSION 3.0)

set(BASEPATH "${CMAKE_SOURCE_DIR}")
set(PROJECT_NAME feenixDebug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

project (Debugger-arm-m3)
set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/debugger/main.cpp
        ${CMAKE_SOURCE_DIR}/debugger/Init.cpp
        ${CMAKE_SOURCE_DIR}/debugger/ElfLoader.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Mmu.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Memory.cpp
        ${CMAKE_SOURCE_DIR}/debugger/devices/memory/Sections.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(DEFINED unittest)
    project(unitTests)
    add_subdirectory(${CMAKE_SOURCE_DIR}/debugger/devices/unit_tests)
endif()
