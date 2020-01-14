add_executable(minimal minimal_example.cpp)
add_executable(comparisons comparisons.cpp)
add_executable(quantities quantities_in_functions.cpp)

target_link_libraries(minimal PRIVATE units)
target_link_libraries(comparisons PRIVATE units)
target_link_libraries(quantities PRIVATE units)
