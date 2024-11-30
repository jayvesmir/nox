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

        uintreg_t vec_val = 0;
        for (auto it = reinterpret_cast<uint8_t*>(&vec_val); it < reinterpret_cast<uint8_t*>(&vec_val) + sizeof(vec_val); it++)
            *it = val;

        while (it_vec + 1 < reinterpret_cast<uintreg_t*>(end))
            *it_vec++ = vec_val;

        auto it_byte = reinterpret_cast<uint8_t*>(it_vec);
        while (it_byte < end)
            *it_byte++ = val;
    }

    void memcpy(void* src, void* dst, uint64_t n_bytes) {
        for (auto i = 0ull; i < n_bytes; i++)
            reinterpret_cast<uint8_t*>(dst)[i] = reinterpret_cast<uint8_t*>(src)[i];
    }

    void memmove(void* src, void* dst, uint64_t n_bytes) {
        uint8_t* const src_it = reinterpret_cast<uint8_t*>(src);
        uint8_t* const dst_it = reinterpret_cast<uint8_t*>(dst);

        if (src_it + n_bytes >= dst_it) {
            uint8_t* tmp = reinterpret_cast<uint8_t*>(__builtin_alloca(n_bytes));
            memcpy(src_it, tmp, n_bytes);
            memcpy(tmp, dst_it, n_bytes);
            return;
        }

        memcpy(src, dst, n_bytes);
    }
} // namespace std