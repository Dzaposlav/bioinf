//
// Created by ledasko on 16-Jan-18.
//

#ifndef PROJECT_BITMASK_H
#define PROJECT_BITMASK_H

#include <cstdint>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>

class bitmask {

private:
    std::vector<bool> mask;

    inline const void check_idx(uint32_t idx) const {
        if (idx > mask.size()) {
            throw std::out_of_range("Index out of bounds for bitmask " + std::to_string(idx) + " >= " + std::to_string(mask.size()));
        }
    }

public:

    explicit bitmask(uint32_t size);

    bitmask &set(uint32_t idx, bool b);

    const bool get(uint32_t idx) const;

    const uint32_t rank0(uint32_t idx) const;

    const uint32_t rank1(uint32_t idx) const;

    const uint32_t size() const;

};


#endif //PROJECT_BITMASK_H
