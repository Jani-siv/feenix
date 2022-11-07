cmake_minimum_required (VERSION 3.0)

# project settings
project (bare-metal-arm C ASM)
set(NAME bare-metal-arm)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

if(DEFINED debugger)
    project(debugger)
    add_subdirectory(${CMAKE_SOURCE_DIR}/debugger)
endif()
