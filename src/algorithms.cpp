//
// Created by Dzaposlav on 16/01/2018.
//

#include "algorithms.h"
std::string build_bwt(const std::string &input_sequence) {
  std::string bwt;
  auto length = input_sequence.length();
  auto suffix_array = new int[length];
  saisxx(input_sequence.c_str(), suffix_array, (int) length);

  bwt.resize(length);
  for (auto i = 0; i < length; ++i)
    bwt[i] = suffix_array[i] ? input_sequence[suffix_array[i] - 1] : '$';

  return bwt;
}

void get_intervals_rec(const std::pair<uint32_t, uint32_t> &curr_interval,
                       const std::pair<uint32_t, uint32_t> &alpha_interval,
                       const wavelet &tree,
                       std::vector<std::pair<uint32_t, uint32_t >> &list) {
  if (alpha_interval.first == alpha_interval.second) {
    auto C = 0u; // actually get cumulative sum for letter
    list.emplace_back(C + curr_interval.first, C + curr_interval.second);
  } else {
    auto a0 = tree.rank('A', 0); // replace with real data
    auto b0 = tree.rank('A', 0); // replace with real data
    auto a1 = curr_interval.first - a0;
    auto b1 = curr_interval.second + 1 - b0;

    auto m = (alpha_interval.first + alpha_interval.second) / 2u;

    if (b0 > a0) {
      get_intervals_rec({a0, b0 - 1}, {alpha_interval.first, m}, tree, list);
    }
    if (b1 > a1) {
      get_intervals_rec({a1, b1 - 1}, {m + 1, alpha_interval.second}, tree, list);
    }
  }
}

std::vector<std::pair<uint32_t, uint32_t >> get_intervals(const std::pair<uint32_t, uint32_t> &curr_interval,
                                                          const wavelet &tree) {
  std::vector<std::pair<uint32_t, uint32_t >> list;
  get_intervals_rec(curr_interval, {0, tree.alpha_length()}, tree, list);
  return list;
}

