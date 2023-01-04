cmake_minimum_required(VERSION 3.23)
project(microorganisms)

set(CMAKE_CXX_STANDARD 14)

add_executable(bruteforce bruteforce_main.cpp io/input.cpp io/output.cpp bruteforce/bruteforce.cpp bool_matrix/bool_matrix.cpp)
add_executable(optimal optimal_main.cpp)
