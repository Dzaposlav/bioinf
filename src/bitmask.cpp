//
// Created by ledasko on 16-Jan-18.
//

#include "bitmask.h"

bitmask::bitmask(uint32_t size) {
    mask.assign(size, false);
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

const uint32_t bitmask::rank0(uint32_t idx) const {
    check_idx(idx);
    auto it = mask.begin();
    return (uint32_t) std::count(it, it + idx, false);
}

const uint32_t bitmask::rank1(uint32_t idx) const {
    return idx - rank0(idx);
}

const uint32_t bitmask::size() const {
    return (uint32_t) mask.size();
}