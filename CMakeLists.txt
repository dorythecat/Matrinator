cmake_minimum_required(VERSION 3.28)
project(Matrinator)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "using ${CMAKE_GENERATOR}")

# This isn't really necessary, but it's nice to have to avoid errors
if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "No build type selected, defaulting to Debug")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -Wall -Wextra -Wundef -Wdouble-promotion -Wformat=2 -fno-common -Wconversion -pedantic -Wno-unused-parameter") # Bundle the necessary static libraries, as well as enable some useful warnings, and disable some nasty ones
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -Og -DDEBUG") # Enable debug symbols and optimisations for debug builds
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3") # Enable full optimisations for release builds

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

add_executable(Matrinator main.cpp
        matrix.hpp)
