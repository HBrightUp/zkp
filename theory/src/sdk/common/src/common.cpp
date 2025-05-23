#include<vector>
#include"../include/common.h"

void swap(long a, long b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

bool is_repeat(const std::vector<ull>& v) {

    const ull size = v.size();
    if (size == 0) {
        return false;
    }

    for(ull i = 0; i < size; ++i) {
        for(ull j = i + 1; j < size; ++j) {
            if (v[i] == v[j]) {
                return true;
            }
        }
    }

    return false;
}