cmake_minimum_required(VERSION 3.4...3.18)

project(bgt60_py)

set(CMAKE_CXX_FLAGS "-DBGT60_FRAMEWORK=BGT60_FRMWK_RPI")

# Search for include Files
include_directories(
    pal/
    wrapper/
)

set(Headers
    pal/
    wrapper/
    )

set(Sources
    pal/bgt60-pal-gpio-rpi.cpp
    wrapper/bgt60-rpi.cpp
    wrapper/bgt60-pybind.cpp
    )

# add_subdirectory(tools/pybind11)
find_package(pybind11 REQUIRED)

pybind11_add_module(bgt60_py ${Sources} ${Headers})

find_library(wiringPi_LIB wiringPi)

# Required Libraries
target_link_libraries(bgt60_py PUBLIC
bgt60-corelib
wiringPi
)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(bgt60_py PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})