#include "../memory.hpp"

#include "std/cstring"

namespace memory {
    void init(uint8_t* begin, uint8_t* end) {
        std::memset(begin, 0, end - begin);

        linear::detail::mem_end = end;
        linear::detail::mem_start = begin;

        linear::detail::page_table.total_pages = (linear::detail::mem_end - linear::detail::mem_start) / linear::page_size;

        linear::detail::usable_start = linear::detail::mem_start + linear::detail::page_table.total_pages;
        linear::detail::page_table.pages = reinterpret_cast<linear::detail::pte*>(linear::detail::mem_start);
    }
} // namespace memory