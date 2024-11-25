#pragma once

#include "std/cstdint"

namespace util {
    constexpr auto ptr_to_addr(auto* ptr) {
        return reinterpret_cast<uintptr_t>(ptr);
    }

    constexpr auto ptr_to_addr(auto (*ptr)()) {
        return reinterpret_cast<uintptr_t>(ptr);
    }
} // namespace util
