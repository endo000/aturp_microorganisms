//
// Created by nsakn on 12/23/2022.
//

#include <cstdint>
#include <vector>
#include <algorithm>
#include "bruteforce.h"
#include "../bool_matrix/bool_matrix.h"

uint32_t bruteforce(const BoolMatrix &matrix, const uint16_t &h, const uint16_t &w) {
    // 0 - not explored
    // 1 - in progress
    // 2 - explored
    std::vector<std::vector<uint8_t>> matrix_state(h, std::vector<uint8_t>(w, 0));

    // Storing all unique shapes
    std::vector<std::vector<std::pair<int16_t, int16_t>>> shape_pool;

    for (uint16_t row_i = 0; row_i < h; ++row_i) {
        for (uint16_t col_i = 0; col_i < w; ++col_i) {
            std::vector<std::pair<int16_t, int16_t>> organism_shape;
            uint32_t cells = explore(matrix, matrix_state, row_i, col_i, h, w, organism_shape);
            if (cells > 0) {
                if (!find_shape(organism_shape, shape_pool)) {
                    set_shape_to_start(organism_shape);
                    shape_pool.push_back(organism_shape);
                }
            }
        }
    }

    return shape_pool.size();
}

bool find_shape(std::vector<std::pair<int16_t, int16_t>> shape,
                std::vector<std::vector<std::pair<int16_t, int16_t>>> &shape_pool) {
    if (shape_pool.empty()) {
        return false;
    }

    for (uint8_t i = 0; i < 4; ++i) {
        set_shape_to_start(shape);

        for (auto &it: shape_pool) {
            uint16_t cells_found = 0;
            bool found = true;

            for (const auto &cell: shape) {
                if (std::find(it.begin(), it.end(), cell) != it.end()) {
                    cells_found++;
                } else {
                    found = false;
                    break;
                }
            }
            if (found && cells_found == it.size()) {
                return true;
            }
        }
        rotate_shape(shape);
    }

    return false;
}

void set_shape_to_start(std::vector<std::pair<int16_t, int16_t>> &shape) {
    auto min = get_min(shape);
    for (auto &pos: shape) {
        pos.first = (int16_t) (pos.first - min.first);
        pos.second = (int16_t) (pos.second - min.second);
    }
}

// https://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d
void rotate_shape(std::vector<std::pair<int16_t, int16_t>> &shape) {
    std::pair<int16_t, int16_t> pivot = shape[0];

    for (uint32_t i = 1; i < shape.size(); ++i) {
        int16_t y = shape[i].first;
        int16_t x = shape[i].second;

        y = (int16_t) (y - pivot.first);
        x = (int16_t) (x - pivot.second);

        shape[i].first = (int16_t) (x + pivot.first);
        shape[i].second = (int16_t) (-y + pivot.second);
    }
}

std::pair<int16_t, int16_t> get_min(std::vector<std::pair<int16_t, int16_t>> shape) {
    const auto minY = *std::min_element(shape.begin(), shape.end(), [](const auto &first,
                                                                       const auto &second) {
        return first.first < second.first;
    });
    const auto minX = *std::min_element(shape.begin(), shape.end(), [](const auto &first,
                                                                       const auto &second) {
        return first.second < second.second;
    });

    return std::make_pair(minY.first, minX.second);
}

// Recursive function
uint32_t
explore(const BoolMatrix &matrix, std::vector<std::vector<uint8_t>> &matrix_state, const uint16_t &y, const uint16_t &x,
        const uint16_t &h, const uint16_t &w, std::vector<std::pair<int16_t, int16_t>> &organism_shape) {
    bool cell_state = get_cell(matrix, y, x);
    uint32_t cells = 0;
    if (cell_state && matrix_state[y][x] == 0) {
        cells = 1;
        matrix_state[y][x] = 1;
        organism_shape.emplace_back(y, x);

        if (y > 0 && matrix_state[y - 1][x] == 0) {
            // Explore top
            cells += explore(matrix, matrix_state, y - 1, x, h, w, organism_shape);
        }
        if (x > 0 && matrix_state[y][x - 1] == 0) {
            // Explore left
            cells += explore(matrix, matrix_state, y, x - 1, h, w, organism_shape);
        }
        if (x < w - 1 && matrix_state[y][x + 1] == 0) {
            // Explore right
            cells += explore(matrix, matrix_state, y, x + 1, h, w, organism_shape);
        }
        if (y < h - 1 && matrix_state[y + 1][x] == 0) {
            // Explore bottom
            cells += explore(matrix, matrix_state, y + 1, x, h, w, organism_shape);
        }
    }
    matrix_state[y][x] = 2;
    return cells;
}