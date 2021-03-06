//
// Created by Dzaposlav on 16/01/2018.
//

#ifndef BIOINF_ALGORITHMS_H
#define BIOINF_ALGORITHMS_H

#include <string>
#include <vector>
#include <queue>
#include "sais.hpp"
#include "wavelet.h"
#include "alphabet_util.h"

const int32_t UNDEF = -2;

std::string build_bwt(const std::string &);
std::vector<int32_t> compute_lcp(const wavelet &, const alphabet_util &);
std::vector<int32_t> compute_lcp(std::string&);
#endif //BIOINF_ALGORITHMS_H
