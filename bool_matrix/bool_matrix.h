//
// Created by aleksandr on 24.12.2022.
//

#ifndef MIKROORGANIZMI_BOOL_MATRIX_H
#define MIKROORGANIZMI_BOOL_MATRIX_H

#include "BoolMatrix.h"

bool get_cell(const BoolMatrix &matrix, const uint16_t &row, const uint16_t &col);

void set_cell(BoolMatrix &matrix, const uint16_t &row, const uint16_t &col, const bool &value);

#endif //MIKROORGANIZMI_BOOL_MATRIX_H
