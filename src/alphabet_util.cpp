//
// Created by Dzaposlav on 16/01/2018.
//

#include "alphabet_util.h"
alphabet_util::alphabet_util(const std::string &str) {
  std::string copy;
  std::copy(str.begin(), str.end(), std::back_inserter(str));
  std::sort(copy.begin(), copy.end());
  uint32_t curr = 1;
  uint32_t csum = 0;
  uint32_t idx = 0;
  this->idxToAlpha[0] = copy.at(0);
  for (uint32_t i = 1; i < copy.length(); ++i) {
    auto &c = copy[i];
    if (c != copy[i - 1]) {
      this->idxToAlpha[++idx] = c;
      this->sum[c] = csum;
      csum += curr;
      curr = 0;
    } else {
      ++curr;
    }
  }
}
const uint32_t alphabet_util::get_sum(uint32_t idx) const {
  return this->sum[this->idxToAlpha[idx]];
}
