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

# ---------------------------------------------------------------------------------------
# Set UNITS_MASTER_PROJECT to ON if we are building Units
# ---------------------------------------------------------------------------------------
# Check if Units is being used directly or via add_subdirectory, but allow overriding
if(NOT DEFINED UNITS_MASTER_PROJECT)
	if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
		set(UNITS_MASTER_PROJECT ON)
		message(STATUS "Building Units as master project")
	else()
		set(UNITS_MASTER_PROJECT OFF)
	endif()
endif()

#---------------------------------------------------------------------------------------
# compiler config
#---------------------------------------------------------------------------------------
option(CODE_COVERAGE "Enable coverage reporting" OFF)
option(UNITS_BUILD_TESTS "Build unit tests" ${UNITS_MASTER_PROJECT})
option(UNITS_BUILD_EXAMPLES "Build example files" ${UNITS_MASTER_PROJECT})

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

if(UNITS_BUILD_TESTS)
	include(FetchContent)
	FetchContent_Declare(
	  Catch2
	  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	  GIT_TAG        v2.13.4)

	FetchContent_MakeAvailable(Catch2)

	enable_testing()
	add_subdirectory(tests)
endif()

if(UNITS_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

add_library(units STATIC
	src/Buffer.cpp
	src/Input.cpp
	src/Output.cpp
	src/Quantity.cpp
	src/Unit.cpp
	src/UnitData.cpp)

target_include_directories(units PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(UNITS_MASTER_PROJECT)
	target_include_directories(units PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
else()
	target_include_directories(units SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

set_target_properties(units PROPERTIES CXX_STANDARD 14)
set_target_properties(units PROPERTIES CXX_STANDARD_REQUIRED ON)

add_library(Units::Units ALIAS units)

#---------------------------------------------------------------------------------------
# Turn on compiler warnings
#---------------------------------------------------------------------------------------
if(UNITS_MASTER_PROJECT)
	target_enable_warnings(units)
endif()

#---------------------------------------------------------------------------------------
# Enable (or disable) features based on the given options
#---------------------------------------------------------------------------------------
if(CODE_COVERAGE)
	target_enable_coverage(units)
endif()
