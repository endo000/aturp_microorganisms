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

    std::cout << "Sleep 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    BoolMatrix matrix = read_file(filename, h, w);

    std::cout << "Sleep 2" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    uint32_t organisms_size = bruteforce(matrix, h, w);
    std::cout << "Sleep 3" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    std::cout << organisms_size << std::endl;
    return 0;
}
