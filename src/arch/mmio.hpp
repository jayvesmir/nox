#pragma once
#include "std/cstdint"

namespace mmio {
    template <typename T> static T read(uintptr_t base, uintptr_t offset_in_T);
    template <typename T> static void write(uintptr_t base, uintptr_t offset_in_T, const T& value);

    template <typename T> static T read_byte_offset(uintptr_t base, uintptr_t offset_in_bytes);
    template <typename T> static void write_byte_offset(uintptr_t base, uintptr_t offset_in_bytes, const T& value);
} // namespace mmio

/* IMPLEMENTATION */

namespace mmio {
    template <typename T> static T read(uintptr_t base, uintptr_t offset_in_T) {
        auto* const base_p = reinterpret_cast<T*>(base);
        return *(base_p + offset_in_T);
    }

    template <typename T> static void write(uintptr_t base, uintptr_t offset_in_T, const T& value) {
        auto* const base_p = reinterpret_cast<T*>(base);
        *(base_p + offset_in_T) = value;
    }

    template <typename T> static T read_byte_offset(uintptr_t base, uintptr_t offset_in_bytes) {
        auto* const base_p = reinterpret_cast<uint8_t*>(base);
        return *reinterpret_cast<T*>(base_p + offset_in_bytes);
    }

    template <typename T> static void write_byte_offset(uintptr_t base, uintptr_t offset_in_bytes, const T& value) {
        auto* const base_p = reinterpret_cast<uint8_t*>(base);
        *reinterpret_cast<T*>(base_p + offset_in_bytes) = value;
    }
} // namespace mmio