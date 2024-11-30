#include "../memory.hpp"

#include "std/cstring"

namespace memory {
    void init(uint8_t* begin, uint8_t* end) {
        std::memset(begin, 0, end - begin);

        page::detail::mem_end = end;
        page::detail::mem_start = begin;

        page::detail::page_table.total_pages = (page::detail::mem_end - page::detail::mem_start) / page::page_size;

        page::detail::usable_start = page::detail::mem_start + page::detail::page_table.total_pages;
        page::detail::page_table.pages = reinterpret_cast<page::detail::pte*>(page::detail::mem_start);
    }
} // namespace memory