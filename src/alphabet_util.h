//
// Created by Dzaposlav on 16/01/2018.
//

#ifndef BIOINF_ALPHABET_SUM_H
#define BIOINF_ALPHABET_SUM_H

#include <cstdint>
#include <string>
#include <algorithm>
class alphabet_util {
 private:
  uint32_t sum[256];
  char idxToAlpha[256];
 public:
  explicit alphabet_util(std::string& str);
  const uint32_t get_sum(uint32_t idx) const;
};

#endif //BIOINF_ALPHABET_SUM_H
