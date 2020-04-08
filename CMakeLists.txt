cmake_minimum_required(VERSION 3.1)
project(Units VERSION 0.0.1 LANGUAGES CXX)

#---------------------------------------------------------------------------------------
# set default build to debug
#---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
endif()

#---------------------------------------------------------------------------------------
# compiler config
#---------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_library(units STATIC src/Input.cpp src/Output.cpp)
target_include_directories(units PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(units PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(units SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/gcem/include)
#target_link_libraries(units PUBLIC gcem)

#---------------------------------------------------------------------------------------
# Turn on compiler warnings
#---------------------------------------------------------------------------------------
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
	target_compile_options(units PUBLIC
		-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align
		-Wunused -Woverloaded-virtual -Wconversion -pedantic
		-Wsign-conversion -Wdouble-promotion -Wformat=2)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(units PUBLIC /W3 )
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	add_compile_definitions(_USE_MATH_DEFINES)
endif()

#---------------------------------------------------------------------------------------
# Enable (or disable) features based on the given options
#---------------------------------------------------------------------------------------
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(units PUBLIC -O0 -g --coverage)

	if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
		target_link_options(units PUBLIC --coverage)
	else()
		target_link_libraries(units PUBLIC --coverage)
	endif()
endif()

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE units)
