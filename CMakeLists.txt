cmake_minimum_required(VERSION 3.1)
project(Units VERSION 0.0.1 LANGUAGES CXX)

#---------------------------------------------------------------------------------------
# include CMake modules
#---------------------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(AddCatchTest)   # Function add_catch_test()
include(EnableCoverage) # Function target_enable_coverage()
include(EnableWarnings) # Function target_enable_warnings()

#---------------------------------------------------------------------------------------
# set default build to debug
#---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
endif()

#---------------------------------------------------------------------------------------
# compiler config
#---------------------------------------------------------------------------------------
option(CODE_COVERAGE "Enable coverage reporting" OFF)
option(UNITS_BUILD_TESTS "Build unit tests" OFF)
option(UNITS_BUILD_EXAMPLES "Build example files" OFF)

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

if(UNITS_BUILD_TESTS)
	enable_testing()
	add_subdirectory(deps/Catch2)
	add_subdirectory(tests)
endif()

if(UNITS_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

add_subdirectory(deps/gcem)

add_library(units STATIC src/Input.cpp src/Output.cpp src/Buffer.cpp)
target_include_directories(units PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(units PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(units SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/gcem/include)

set_target_properties(units PROPERTIES CXX_STANDARD 14)
set_target_properties(units PROPERTIES CXX_STANDARD_REQUIRED ON)

add_library(Units::Units ALIAS units)

#---------------------------------------------------------------------------------------
# Turn on compiler warnings
#---------------------------------------------------------------------------------------
target_enable_warnings(units)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	add_compile_definitions(_USE_MATH_DEFINES)
endif()

#---------------------------------------------------------------------------------------
# Enable (or disable) features based on the given options
#---------------------------------------------------------------------------------------
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_enable_coverage(units)
endif()
