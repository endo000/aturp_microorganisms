//
// Created by nsakn on 12/23/2022.
//

#ifndef MIKROORGANIZMI_INPUT_H
#define MIKROORGANIZMI_INPUT_H

#include <vector>

std::vector<std::vector<uint8_t>> read_file(const std::string &filename, uint16_t &h, uint16_t &w);

#endif //MIKROORGANIZMI_INPUT_H
