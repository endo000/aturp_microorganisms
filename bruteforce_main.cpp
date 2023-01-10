#include <cstdint>
#include <iostream>
#include "io/input.h"
#include "bool_matrix/BoolMatrix.h"
#include "bruteforce/bruteforce.h"

#include <chrono>
#include <thread>

int main(int argc, char **argv) {
    std::string filename = argv[1];
    uint16_t h,w;

    BoolMatrix matrix = read_file(filename, h, w);

    uint32_t organisms_size = bruteforce(matrix, h, w);

    std::cout << organisms_size << std::endl;
    return 0;
}
