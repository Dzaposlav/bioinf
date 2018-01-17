//
// Created by ledasko on 16-Jan-18.
//

#include "wavelet.h"
#include <unordered_set>

// private

wavelet::wavelet(const wavelet *parent, const std::string &str) : parent(parent) {

    mask = new bitmask((uint32_t) str.length());

    // create alphabet
    std::unordered_set<char> chars;
    std::copy(str.begin(), str.end(), std::inserter(chars, chars.end()));
    std::string alphabet;
    std::copy(chars.begin(), chars.end(), std::back_inserter(alphabet));
    std::sort(alphabet.begin(), alphabet.end());

    if (alphabet.length() == 1) {
        alpha[alphabet[0]] = false;
        left = nullptr;
        right = nullptr;
        return;
    }

    std::string sleft, sright;
    auto half = (uint8_t) ((alphabet.length() - 1) / 2);

    for (uint32_t i = 0; i < alphabet.length(); ++i) {
        bool right = i > half;
        char a = alphabet[i];
        alpha[a] = right;
    }

    for (uint32_t j = 0; j < str.length(); ++j) {
        char c = str[j];
        bool right = alpha[c];
        mask->set(j, right);
        if (right) {
            sright += c;
        } else {
            sleft += c;
        }
    }

    left = new wavelet(this, sleft);
    right = new wavelet(this, sright);
}

// public

const char wavelet::operator[](uint32_t idx) {
    // leaf node
    if (leaf()) { return alpha.begin()->first; }

    // recurse
    if (mask->get(idx)) { return (*right)[mask->rank1(idx) - 1]; }
    else { return (*left)[mask->rank0(idx) - 1]; }
}

const uint32_t wavelet::rank(char elem, uint32_t idx) const {
    if (!has_elem(elem)) { return 0; }

    if (leaf()) { return mask->rank0(idx); }

    uint32_t rnk;
    if (alpha.at(elem)) {
        rnk = mask->rank1(idx);
    } else {
        rnk = mask->rank0(idx);
    }

    if (rnk-- == 0) { return 0; }
    return (alpha.at(elem) ? right : left)->rank(elem, rnk);
}

const wavelet *wavelet::findLeaf(char c) const {
    if (leaf()) {
        return this;
    }

    return (alpha.at(c) ? right : left)->findLeaf(c);
}

const uint32_t wavelet::length() const {
    return mask->size();
}

const uint32_t wavelet::alpha_length() const {
    return (uint32_t) alpha.size();
}

/**
 * Helper method for algorithm 1
 * @param curr_interval Current interval
 * @param interval Current alphabet interval
 * @param alphabet Alphabet utility helper
 * @param list Return list
 */
void wavelet::get_intervals_rec(const interval &curr_interval,
                                const interval &alpha_interval,
                                const alphabet_util &alphabet,
                                std::vector<interval> &list) const {
    if (alpha_interval.first == alpha_interval.second) {
        auto C = alphabet.get_sum(alpha_interval.first);
        list.emplace_back(C + curr_interval.first, C + curr_interval.second);
    } else {
        auto a0 = rank0(curr_interval.first);
        auto b0 = rank0(curr_interval.second + 1);
        auto a1 = curr_interval.first - a0;
        auto b1 = curr_interval.second + 1 - b0;

        auto m = (alpha_interval.first + alpha_interval.second) / 2u;

        if (b0 > a0)
            this->left->get_intervals_rec({a0, b0 - 1}, {alpha_interval.first, m}, alphabet, list);
        if (b1 > a1)
            this->right->get_intervals_rec({a1, b1 - 1}, {m + 1, alpha_interval.second}, alphabet, list);
    }
}

/**
 * Algorithm 1 from https://www.sciencedirect.com/science/article/pii/S1570866712001104
 * @param curr_interval Current interval
 * @param tree Wavelet tree
 * @param alphabet Alphabet utility helper
 * @return Intervals
 */
const std::vector<std::pair<uint32_t, uint32_t >> wavelet::get_intervals(const interval &curr_interval,
                                                                         const alphabet_util &alphabet) const {
    std::vector<interval> list;
    get_intervals_rec(curr_interval, {0, alpha_length() - 1}, alphabet, list);
    return list;
}


