cmake_minimum_required(VERSION 3.1)

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

add_executable(Units.test Units.cpp)
add_executable(Input.test Input.cpp)
add_executable(Errors.test Errors.cpp)
add_executable(Comp.test Comparisons.cpp)

target_link_libraries(Units.test PRIVATE Catch2::Catch2 Units::Units)
target_link_libraries(Input.test PRIVATE Catch2::Catch2 Units::Units)
target_link_libraries(Errors.test PRIVATE Catch2::Catch2 Units::Units)
target_link_libraries(Comp.test PRIVATE Catch2::Catch2 Units::Units)

add_test(NAME Units.test  COMMAND ${CMAKE_BINARY_DIR}/tests/Units.test)
add_test(NAME Input.test  COMMAND ${CMAKE_BINARY_DIR}/tests/Input.test)
add_test(NAME Errors.test COMMAND ${CMAKE_BINARY_DIR}/tests/Errors.test)
add_test(NAME Comp.test   COMMAND ${CMAKE_BINARY_DIR}/tests/Comp.test)

#---------------------------------------------------------------------------------------
# Turn on compiler warnings
#---------------------------------------------------------------------------------------
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
	target_compile_options(Units.test  PUBLIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -pedantic -Wsign-conversion -Wdouble-promotion -Wformat=2)
	target_compile_options(Input.test  PUBLIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -pedantic -Wsign-conversion -Wdouble-promotion -Wformat=2)
	target_compile_options(Errors.test PUBLIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -pedantic -Wsign-conversion -Wdouble-promotion -Wformat=2)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(Units.test  PUBLIC /W3)
	target_compile_options(Input.test  PUBLIC /W3)
	target_compile_options(Errors.test PUBLIC /W3)

	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	add_compile_definitions(_USE_MATH_DEFINES)
endif()

#---------------------------------------------------------------------------------------
# Enable (or disable) features based on the given options
#---------------------------------------------------------------------------------------
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(Units.test PUBLIC -O0 -g --coverage)
	target_compile_options(Input.test PUBLIC -O0 -g --coverage)
	target_compile_options(Errors.test PUBLIC -O0 -g --coverage)
	target_compile_options(Comp.test PUBLIC -O0 -g --coverage)

	if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
		target_link_options(Units.test PUBLIC --coverage)
		target_link_options(Input.test PUBLIC --coverage)
		target_link_options(Errors.test PUBLIC --coverage)
		target_link_options(Comp.test PUBLIC --coverage)
	else()
		target_link_libraries(Units.test PUBLIC --coverage)
		target_link_libraries(Input.test PUBLIC --coverage)
		target_link_libraries(Errors.test PUBLIC --coverage)
		target_link_libraries(Comp.test PUBLIC --coverage)
	endif()
endif()
