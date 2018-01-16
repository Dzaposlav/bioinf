//
// Created by Dzaposlav on 16/01/2018.
//

#include "algorithms.h"
std::string build_bwt(const std::string& input_sequence){
  std::string bwt;
  auto length = input_sequence.length();
  auto suffix_array = new int[length];
  saisxx(input_sequence.c_str(), suffix_array, (int) length);

  bwt.resize(length);
  for (auto i = 0; i < length; ++i)
    bwt[i] = suffix_array[i] ? input_sequence[suffix_array[i] - 1] : '$';

  return bwt;
}
