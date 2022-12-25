cmake_minimum_required(VERSION 3.23)
project(microorganisms)

set(CMAKE_CXX_STANDARD 14)

add_executable(microorganisms main.cpp io/input.cpp io/output.cpp bruteforce/bruteforce.cpp bool_matrix/bool_matrix.cpp)
