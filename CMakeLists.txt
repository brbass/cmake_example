cmake_minimum_required (VERSION 3.1)

###########
# Project #
###########

# Set project name
project(CMakeExample)

# Set print option to TRUE or FALSE
set(print TRUE)

####################
# Compiler options #
####################

# Set build type (Debug or Release)
set(CMAKE_BUILD_TYPE Debug)

# Add C++ compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

# Set installation directory (./bin)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Print compiler options
if(print)
    message("\nCMake CXX Compiler:\t${CMAKE_CXX_COMPILER}")
    message("CMake C Compiler:\t${CMAKE_C_COMPILER}")
    message("CMake CXX Flags:\t${CMAKE_CXX_FLAGS}")
    message("CMake C Flags:\t${CMAKE_C_FLAGS}\n")
endif()

##########################
# Get header directories #
##########################

# Get header directories
# Should include all directories with a "*.h" file
include_directories(src)

# Print header directories
if(print)
    get_directory_property(directories INCLUDE_DIRECTORIES)
    message("Header directories:\t${directories}\n")
endif()

####################
# Get source files #
####################

# Find all source files in the "src" directory
# If there are source files (without "main") elsewhere, add them here
file(GLOB source_files src/*.cpp src/*.h)

# Create source library with all files in the "src" directory
# This compiles the library for use in an arbitrary number of executables
set(library_name src_library)
add_library(${library_name} ${source_files})
install(TARGETS ${library_name} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Print source file filepaths
if(print)
    message("Source files:\t${source_files}\n")
endif()

###########
# Testing #
###########

# Enable CTest
enable_testing()

# Get libraries to add to test
set(test_dependencies src_library)

# Function that includes a test in the project, with the parameters:
#     test_exec: the desired executable name
#     test_src: the test file containing the "main" function
#     test_args: command-line arguments for the test
# This assumes each executable will only be used for one test
macro(include_test test_exec test_src test_args)
    if(print)
        message("Test included:\t${test_exec} ${test_src} ${test_args}\n")
    endif()
    add_executable(${test_exec} ${test_src})
    target_link_libraries(${test_exec} ${test_dependencies})
    add_test(${test_exec} ${test_exec} ${test_args})
    install(TARGETS ${test_exec} DESTINATION ${CMAKE_INSTALL_PREFIX}/test)
endmacro()

# Include a sample test
set(addition_args 1 2 3)
include_test(tst_addition test/Test_Addition.cpp "${addition_args}")

##############
# Executable #
##############

# Set executable name and library dependencies
set(executable_name add)
set(executable_dependencies src_library)

# Get all files in "main" directory (one of which should contain "main" function)
file(GLOB main_files main/*.cpp main/*.h)

# Add and install executable
add_executable(${executable_name} ${main_files})
target_link_libraries(${executable_name} ${executable_dependencies})
install(TARGETS ${executable_name} DESTINATION ${CMAKE_INSTALL_PREFIX})
