//
// Created by Dzaposlav on 16/01/2018.
//

#include "alphabet_util.h"

alphabet_util::alphabet_util(std::string &str) {
  std::string copy;
  std::copy(str.begin(), str.end(), std::back_inserter(copy));
  std::sort(copy.begin(), copy.end());

  uint32_t curr = 0;
  uint32_t csum = 0;
  uint32_t idx = 0;

  for (uint32_t i = 0; i < copy.length(); ++i) {
    if (i == 0 || copy[i] != copy[i - 1]) {
      csum += curr;
      this->sum[idx++] = csum;
      curr = 0;
    }
    curr++;
  }
}
const uint32_t alphabet_util::get_sum(uint32_t idx) const {
  return this->sum[idx];
}
