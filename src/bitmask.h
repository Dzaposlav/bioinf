//
// Created by ledasko on 16-Jan-18.
//

#ifndef PROJECT_BITMASK_H
#define PROJECT_BITMASK_H

#include <vector>
#include <algorithm>

class bitmask {

private:
    std::vector<bool> mask;

    bitmask(uint32_t size);

    inline const void check_idx(uint32_t idx) const {
        if (idx >= mask.size()) {
            throw std::out_of_range("Index out of bounds for bitmask");
        }
    }

public:

    bitmask &set(uint32_t idx, bool b);

    const bool get(uint32_t idx) const;

    const uint32_t select01(uint32_t idx, bool b) const;

    const uint32_t rank0(uint32_t idx) const;

    const uint32_t rank1(uint32_t idx) const;

    const uint32_t size(void) const;

};


#endif //PROJECT_BITMASK_H
