#pragma once
#include "std/concepts"
#include "std/cstdint"

namespace std {
    template <typename T> struct formatter {
        uint64_t operator()(char* buf, uint64_t capacity, const T& value);
    };
} // namespace std

namespace std {
    template <std::is_integral T> struct formatter<T> {
        static inline char get_hex_digit(T val, bool capital = false) {
            const auto base = capital ? 'A' : 'a';
            if (val >= 10)
                return base + ((val % 16) - 10);
            return '0' + (val % 16);
        }

        uint64_t operator()(char* buf, uint64_t capacity, const T& value, uint32_t radix = 10, bool capital = false) {
            uint64_t output_len = 0;
            T val = value;

            if (val < 0) {
                buf[0] = '-';
                val = -val;
                output_len++;
            }

            char last_digit = get_hex_digit(val % radix, capital);
            val /= radix;

            char tmp[64] = {0};
            auto* it = tmp;
            for (it = tmp; val != 0 && it != (tmp + 64); it++) {
                *it = get_hex_digit(val % radix, capital);
                val /= radix;
            }

            for (auto i = output_len; it != tmp && output_len <= capacity; i++) {
                buf[i] = *--it;
                output_len++;
            }

            if (output_len < capacity) {
                buf[output_len] = last_digit;
                output_len++;
            }

            if (output_len < capacity)
                buf[output_len] = 0;

            return output_len;
        }
    };
} // namespace std