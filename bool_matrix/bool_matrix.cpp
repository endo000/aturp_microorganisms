//
// Created by aleksandr on 24.12.2022.
//

#include <cstdint>
#include <vector>
#include "bool_matrix.h"
#include "BoolMatrix.h"

bool get_cell(const BoolMatrix &matrix, const uint16_t &row, const uint16_t &col) {
    const std::vector<uint8_t> &m_row = matrix[row];

    uint16_t m_col = col / 8;
    uint8_t bit_index = col % 8;

    return (m_row[m_col] >> bit_index) & 1;
}

void set_cell(BoolMatrix &matrix, const uint16_t &row, const uint16_t &col, const bool &value) {
    std::vector<uint8_t> &m_row = matrix[row];

    uint16_t m_col = col / 8;
    uint8_t bit_index = col % 8;

    m_row[m_col] ^= (-value ^ m_row[m_col]) & (1 << bit_index);
}