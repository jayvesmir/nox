#include "std/cstring"

namespace std {
    int32_t memcmp(const void* buf1, const void* buf2, uint64_t n) {
        auto it1 = reinterpret_cast<const uint8_t*>(buf1);
        auto it2 = reinterpret_cast<const uint8_t*>(buf2);
        const auto end = it1 + n;
        for (; it1 != end; it1++, it2++) {
            if (*it1 < *it2)
                return -1;
            if (*it1 > *it2)
                return 1;
        }
        return 0;
    }
} // namespace std