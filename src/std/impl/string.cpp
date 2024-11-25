#include "std/cstring"
namespace std {
    int32_t memcmp(const void* buf1, const void* buf2, uint64_t n_bytes) {
        auto it1 = reinterpret_cast<const uint8_t*>(buf1);
        auto it2 = reinterpret_cast<const uint8_t*>(buf2);
        const auto end = it1 + n_bytes;
        for (; it1 != end; it1++, it2++) {
            if (*it1 < *it2)
                return -1;
            if (*it1 > *it2)
                return 1;
        }
        return 0;
    }

    void memset(void* buf, const uint8_t val, uint64_t n_bytes) {
        const auto end = reinterpret_cast<uint8_t*>(buf) + n_bytes;
        auto it_vec = reinterpret_cast<uintreg_t*>(buf);

        auto vec_val = *it_vec;
        for (auto it = reinterpret_cast<uint8_t*>(&vec_val); it < reinterpret_cast<uint8_t*>(&vec_val) + sizeof(vec_val); it++)
            *it = val;

        while (it_vec < reinterpret_cast<uintreg_t*>(end))
            *it_vec++ = vec_val;

        auto it_byte = reinterpret_cast<uint8_t*>(it_vec - 1);
        while (it_byte < end)
            *it_byte++ = val;
    }
} // namespace std