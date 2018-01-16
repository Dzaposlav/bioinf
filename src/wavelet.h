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

/**
 * Represents a single wavelet tree.
 * Used to answer rank/select queries.
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
        return left==nullptr && right==nullptr;
    }

    /**
     * check if wavelet has given element
     * @param elem element
     * @return true if wavelet has that element
     */
    inline const bool has_elem(char elem) const {
        return alpha.find(elem)!=alpha.end();
    }

    /**
     * Recursive select, goes from leaf to root node
     *
     * @param idx index for select
     * @param b value selected
     * @return final select
     */
    const uint32_t select_rec(uint32_t idx, bool b) const;

public:

    explicit wavelet(const std::string &str) : wavelet(nullptr, str) {};

    const char operator[](uint32_t idx);
    const uint32_t rank(char elem, uint32_t idx) const;
    const uint32_t select(char elem, uint32_t idx) const;
    const uint32_t length() const;
};



#endif //BIOINF_WAVELET_H
