//
// Created by ledasko on 16-Jan-18.
//

#include "bitmask.h"

bitmask *bitmask::create(uint32_t size) {
    return new bitmask(size);
}

bitmask &bitmask::set(uint32_t idx, bool b) {
    check_idx(idx);
    mask[idx] = b;
    return *this;
}

const bool bitmask::get(uint32_t idx) const {
    check_idx(idx);
    return mask[idx];
}

const uint32_t bitmask::select01(uint32_t idx, bool b) const {
    uint32_t sol = 0;
    for (auto it = mask.begin(); it != mask.end(); it++) {
        if (*it == b) {
            if (--idx == 0) {
                return sol;
            }
        }
        sol++;
    }
    throw std::out_of_range("No such value");
}

const uint32_t bitmask::rank0(uint32_t idx) const {
    check_idx(idx);
    auto it = mask.begin();
    return (uint32_t) std::count(it, it + idx + 1, false);
}

const uint32_t bitmask::rank1(uint32_t idx) const {
    return idx + 1 - rank0(idx);
}

const uint32_t bitmask::size(void) const {
    return (uint32_t) mask.size();
}