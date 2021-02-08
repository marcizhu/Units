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
add_catch_test(Units.test       Units.cpp       LIBRARIES Units::Units CXX_STANDARD 14)
add_catch_test(Input.test       Input.cpp       LIBRARIES Units::Units CXX_STANDARD 14)
add_catch_test(Errors.test      Errors.cpp      LIBRARIES Units::Units CXX_STANDARD 14)
add_catch_test(Comparisons.test Comparisons.cpp LIBRARIES Units::Units CXX_STANDARD 14)

add_executable(fuzz fuzz.cpp)
target_link_libraries(fuzz PRIVATE Units::Units)

set_target_properties(fuzz PROPERTIES CXX_STANDARD 14)
set_target_properties(fuzz PROPERTIES CXX_STANDARD_REQUIRED ON)

# Set test timeout to 10 seconds
set_tests_properties(Units.test       PROPERTIES TIMEOUT 10)
set_tests_properties(Input.test       PROPERTIES TIMEOUT 10)
set_tests_properties(Errors.test      PROPERTIES TIMEOUT 10) 
set_tests_properties(Comparisons.test PROPERTIES TIMEOUT 10)      

#---------------------------------------------------------------------------------------
# Turn on compiler warnings
#---------------------------------------------------------------------------------------
target_enable_warnings(Units.test)
target_enable_warnings(Input.test)
target_enable_warnings(Errors.test)
target_enable_warnings(Comparisons.test)
target_enable_warnings(fuzz)

#---------------------------------------------------------------------------------------
# Enable (or disable) features based on the given options
#---------------------------------------------------------------------------------------
if(CODE_COVERAGE)
	target_enable_coverage(Units.test)
	target_enable_coverage(Input.test)
	target_enable_coverage(Errors.test)
	target_enable_coverage(Comparisons.test)
	target_enable_coverage(fuzz)
endif()
