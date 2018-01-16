//
// Created by Dzaposlav on 16/01/2018.
//

#ifndef BIOINF_ALGORITHMS_H
#define BIOINF_ALGORITHMS_H

#include <string>
#include <vector>
#include "sais.hpp"
#include "wavelet.h"
#include "alphabet_util.h"

std::string build_bwt(const std::string&);
std::vector<std::pair<uint32_t, uint32_t >> get_intervals(const std::pair<uint32_t, uint32_t >&, const wavelet&, const alphabet_util&);
#endif //BIOINF_ALGORITHMS_H
