//
// Created by nsakn on 12/23/2022.
//

#ifndef MIKROORGANIZMI_BRUTEFORCE_H
#define MIKROORGANIZMI_BRUTEFORCE_H

#include "../bool_matrix/BoolMatrix.h"

uint32_t bruteforce(const BoolMatrix &matrix, const uint16_t &h, const uint16_t &w);

uint32_t
explore(const BoolMatrix &matrix, std::vector<std::vector<uint8_t>> &matrix_state, const uint16_t &y, const uint16_t &x,
        const uint16_t &h, const uint16_t &w, std::vector<std::pair<int16_t, int16_t>> &organism_shape);

bool find_shape(std::vector<std::pair<int16_t, int16_t>> shape,
                std::vector<std::vector<std::pair<int16_t, int16_t>>> &shape_pool);

std::pair<int16_t, int16_t> get_min(std::vector<std::pair<int16_t, int16_t>> shape);

void rotate_shape(std::vector<std::pair<int16_t, int16_t>> &shape);

void set_shape_to_start(std::vector<std::pair<int16_t, int16_t>> &shape);

#endif //MIKROORGANIZMI_BRUTEFORCE_H
