//
// Created by ledasko on 16-Jan-18.
//

#ifndef BIOINF_WAVELET_H
#define BIOINF_WAVELET_H

#include <cstdint>
#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include "bitmask.h"
#include "alphabet_util.h"

using interval = std::pair<uint32_t, uint32_t>;

/**
 * Represents a single wavelet tree.
 * Used to answer rank queries.
 */
class wavelet {

private:
    // main parts
    bitmask *mask;
    std::unordered_map<char, bool> alpha;

    // pointers
    const wavelet *parent;
    wavelet *left;
    wavelet *right;

    wavelet(const wavelet *parent, const std::string &str);

    /**
     * Find leaf node which contains only given characters
     *
     * @param c character
     * @return leaf node
     */
    const wavelet *findLeaf(char c) const;

    /**
     * @return is this node a leaf node
     */
    inline const bool leaf() const {
        return left == nullptr && right == nullptr;
    }

    /**
     * check if wavelet has given element
     * @param elem element
     * @return true if wavelet has that element
     */
    inline const bool has_elem(char elem) const {
        return alpha.find(elem) != alpha.end();
    }

    void get_intervals_rec(const interval &,
                           const interval &,
                           const alphabet_util &,
                           std::vector<interval> &);

    inline const uint32_t rank0(const uint32_t idx){
        return mask->rank0(idx);
    }

public:

    explicit wavelet(const std::string &str) : wavelet(nullptr, str) {};

    const char operator[](uint32_t idx);

    const uint32_t rank(char elem, uint32_t idx) const;

    const uint32_t length() const;

    const uint32_t alpha_length() const;

    std::vector<interval> get_intervals(const interval &, const alphabet_util &);
};


#endif //BIOINF_WAVELET_H
