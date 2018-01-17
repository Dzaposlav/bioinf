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
 * Helper method for algorithm 1
 * @param curr_interval Current interval
 * @param alpha_interval Current alphabet interval
 * @param tree Wavelet tree
 * @param alphabet Alphabet utility helper
 * @param list Return list
 */
void get_intervals_rec(const std::pair<uint32_t, uint32_t> &curr_interval,
                       const std::pair<uint32_t, uint32_t> &alpha_interval,
                       const wavelet &tree,
                       const alphabet_util &alphabet,
                       std::vector<std::pair<uint32_t, uint32_t >> &list) {
  if (alpha_interval.first == alpha_interval.second) {
    auto C = alphabet.get_sum(alpha_interval.first); // replace with real letter
    list.emplace_back(C + curr_interval.first, C + curr_interval.second);
  } else {
    auto a0 = tree.rank('A', 0); // replace with real data
    auto b0 = tree.rank('A', 0); // replace with real data
    auto a1 = curr_interval.first - a0;
    auto b1 = curr_interval.second + 1 - b0;

    auto m = (alpha_interval.first + alpha_interval.second) / 2u;

    if (b0 > a0) {
      get_intervals_rec({a0, b0 - 1}, {alpha_interval.first, m}, tree, alphabet, list);
    }
    if (b1 > a1) {
      get_intervals_rec({a1, b1 - 1}, {m + 1, alpha_interval.second}, tree, alphabet, list);
    }
  }
}

/**
 * Algorithm 1 from https://www.sciencedirect.com/science/article/pii/S1570866712001104
 * @param curr_interval Current interval
 * @param tree Wavelet tree
 * @param alphabet Alphabet utility helper
 * @return Intervals
 */
std::vector<std::pair<uint32_t, uint32_t >> get_intervals(const std::pair<uint32_t, uint32_t> &curr_interval,
                                                          const wavelet &tree,
                                                          const alphabet_util &alphabet) {
  std::vector<std::pair<uint32_t, uint32_t >> list;
  get_intervals_rec(curr_interval, {0, tree.alpha_length()}, tree, alphabet, list);
  return list;
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

  Q.emplace({0, sz - 1}, 0);

  while (!Q.empty()) {
    auto front = Q.front();
    Q.pop();
    auto intervals = get_intervals(front.first, tree, alphabet);
    for (auto &interval : intervals) {
      if (lcp.at(interval.second) == UNDEF) {
        lcp.at(interval.second) = front.second;
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
std::vector<int32_t> compute_lcp(const std::string &sequence) {
  alphabet_util alphabet(sequence);
  wavelet tree(build_bwt(sequence));
  return compute_lcp(tree, alphabet);
}
