//
// Created by Dzaposlav on 16/01/2018.
//

#include "algorithms.h"

/**
 * Burrows-Wheeler Transform algorithm
 * @param input_sequence Input sequence
 * @return Transformed sequence
 */
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

/**
 * Algorithm 2 from https://www.sciencedirect.com/science/article/pii/S1570866712001104
 * @param tree Wavelet tree
 * @param alphabet Alphabet utility helper
 * @return lcp array
 */
std::vector<int32_t> compute_lcp(const wavelet &tree, const alphabet_util &alphabet) {
  std::queue<std::pair<std::pair<uint32_t, uint32_t>, int32_t >> Q;
  auto sz = tree.length();
  std::vector<int32_t> lcp(sz + 1, UNDEF);
  lcp.at(0) = -1;
  lcp.at(sz) = -1;

  Q.push({{0u, sz - 1u}, 0});

  while (!Q.empty()) {
    auto front = Q.front();
    Q.pop();
    auto intervals = tree.get_intervals(front.first, alphabet);

    for (auto &interval : intervals) {
      if (lcp.at(interval.second + 1) == UNDEF) {
        lcp.at(interval.second + 1) = front.second;
        Q.emplace(interval, front.second + 1);
      }
    }
  }

  return lcp;
}

/**
 * Wrapper method for algorithm 2, gets input sequence, does all transformations and calculations adn then returns lcp array
 * @return lcp array
 */
std::vector<int32_t> compute_lcp(std::string &sequence) {
  alphabet_util alphabet(sequence);
  std::string bwt = build_bwt(sequence);
  wavelet tree(bwt);
  return compute_lcp(tree, alphabet);
}
