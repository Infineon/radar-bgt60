cmake_minimum_required(VERSION 3.12.4)  

# Arduino Library Template 
set(bgt60core bgt60-corelib)

project(${bgt60core} CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
set(CMAKE_C_OUTPUT_EXTENSION_REPLACE ON)

# Search for include Files
include_directories(
    src/config
    src/corelib
    src/pal
)

# Header & Source Files
set(Headers
    src/config
    src/corelib
    src/pal
    )

set(Sources
    src/corelib/bgt60-logger.cpp
    src/corelib/bgt60.cpp
    )

# Add Library
add_library(${bgt60core} ${Sources} ${Headers})

# Currently only using this target for rasbperry pi host
if (CMAKE_HOST_UNIX)
    # Add directory
    add_subdirectory(src/framework/raspberrypi)
endif()

# If the googletest library is in the project folder
if (EXISTS ${CMAKE_SOURCE_DIR}/googletest)
    # Coverage Flags
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -DBGT60_LOGGER_ENABLED=0")
    set(CMAKE_C_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

    # Enable Testing with CTest
    enable_testing()

    # Add GoogleTest 
    add_subdirectory(googletest)
    # Add Tests Folder
    add_subdirectory(test/unit)
endif()