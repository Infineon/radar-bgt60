cmake_minimum_required(VERSION 3.12.4)

set(prjtest bgt60-test)

# Test Sources 
set(Sources
    test_bgt60.cpp
)

# GCOV Coverage Targets 
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
set(GCOV_FILES_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/bgt60-corelib.dir/src)

# Binary and Output Coverage Files
file(GLOB_RECURSE GCOV_GNNO_GCDA_FILES ${CMAKE_BINARY_DIR}/*.gc??)

# Coverage Target
add_custom_target(gcov
    COMMAND ${CMAKE_COMMAND} -E make_directory coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Coverage Command
add_custom_command(TARGET gcov
    COMMAND ${CMAKE_COMMAND} -E echo "=================== GCOVR ===================="
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR}/src/corelib/ ${GCOV_FILES_DIR}/corelib -b -k --gcov-ignore-parse-errors --html --html-details -o ${CMAKE_BINARY_DIR}/coverage/coverage.html 
    COMMAND ${CMAKE_COMMAND} -E echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
    )

# Coverage Clean
add_custom_target(gcov_clean
    COMMAND ${CMAKE_COMMAND} -E remove -f ${GCOV_GNNO_GCDA_FILES}
    COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_dependencies(gcov ${prjtest})

# Executable
add_executable(${prjtest} ${Sources}) #${Headers})

# Required Libraries
target_link_libraries(${prjtest} PUBLIC
    gtest_main
    gmock_main
    bgt60-corelib
)

# Add Ctest
add_test(
    NAME ${prjtest}
    COMMAND ${prjtest}
)