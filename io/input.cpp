//
// Created by nsakn on 12/23/2022.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "input.h"
#include "../bool_matrix/BoolMatrix.h"

BoolMatrix read_file(const std::string &filename, uint16_t &h, uint16_t &w) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File doesn't exist" << std::endl;
        exit(1);
    }

    file >> h >> w;

    BoolMatrix matrix;
    matrix.resize(h);

    const uint8_t byte_size = 8;
    // How many elements in a row
    uint16_t row_size = w / byte_size;
    if (w % 8 > 0) {
        row_size++;
    }

    // How many bits will we use for one uint8_t element
    uint16_t element_size = std::min((uint16_t) byte_size, w);

    uint8_t cell;
    for (int row_i = 0; row_i < h; ++row_i) {
        std::vector<uint8_t> row;
        row.resize(row_size);

        for (int col_i = 0; col_i < row_size; ++col_i) {
            uint8_t temp = 0;

            for (int bit_index = 0; bit_index < element_size; ++bit_index) {
                file >> cell;
                if (cell == '1') {
                    temp |= 1 << bit_index;
                }

                if (col_i == row_size - 1 && w > 8 && bit_index + 1 == w - 8 * (row_size - 1)) {
                    break;
                }

                if (file.peek() == EOF) {
                    break;
                }
            }
            row[col_i] = temp;

            if (file.peek() == EOF) {
                break;
            }
        }
        matrix[row_i] = row;

        if (file.peek() == EOF) {
            break;
        }
    }

    return matrix;
}
