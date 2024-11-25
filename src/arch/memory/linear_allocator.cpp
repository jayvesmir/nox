#include "../memory.hpp"

#include "std/cstdio"
#include "std/cstring"
#include "util/cast.hpp"

#pragma clang optimize off

namespace memory {
    namespace linear {
        namespace detail {
            uint8_t* mem_start = nullptr;
            uint8_t* mem_end = nullptr;
            uint8_t* usable_start = nullptr;

            pt page_table = {nullptr, 0};

            pte* pt::find_free_range(uint64_t n_pages) {
                if (!pages || !total_pages)
                    return nullptr;

                for (auto base_i = 0ull; base_i < total_pages; base_i++) {
                    bool is_free = true;

                    for (auto page_i = 0ull; page_i < n_pages && base_i + page_i < total_pages; page_i++) {
                        if (pages[base_i + page_i].flags != 0) {
                            is_free = false;
                            break;
                        }
                    }

                    if (!is_free)
                        continue;

                    return &pages[base_i];
                }

                return nullptr;
            }

            pte* pt::find_allocation_end(pte* entry) {
                if (entry >= pages + total_pages || entry < pages)
                    return nullptr;

                while (entry < pages + total_pages) {
                    if (entry->flags & pte_bits::last || entry->flags == 0)
                        break;

                    entry++;
                }

                return entry;
            }

            pte* pt::page_to_pte(void* ptr) {
                if (ptr >= usable_start + total_pages || ptr < usable_start)
                    return nullptr;

                auto addr = util::ptr_to_addr(ptr);

                auto addr_offset = (addr - util::ptr_to_addr(usable_start));
                auto page_base = addr - (addr_offset) % page_size;
                auto page_index = ((page_base - util::ptr_to_addr(usable_start)) / page_size);
                return &pages[page_index];
            }

            void* pt::pte_to_page(pte* entry) {
                if (entry >= pages + total_pages || entry < pages)
                    return nullptr;

                const auto page_index = entry - pages;

                return (usable_start + (page_index * page_size));
            }

            void pt::dump_to_console() {
                std::printf("--- page table dump ---\n");

                bool found_allocations = false;
                auto free_pages = total_pages;

                for (auto base_i = 0ull; base_i < total_pages; base_i++) {
                    if ((pages[base_i].flags & pte_bits::used) == 0)
                        continue;

                    auto start_i = base_i;

                    std::printf("%p -> ", pte_to_page(&pages[base_i]));

                    for (; base_i < total_pages; base_i++) {
                        if (pages[base_i].flags & pte_bits::last) {
                            std::printf("%p (%u64 pages)", pte_to_page(&pages[base_i]), base_i - start_i + 1);
                            free_pages -= base_i - start_i + 1;
                            break;
                        }
                    }

                    std::printf("\n");

                    found_allocations = true;
                }

                if (!found_allocations) {
                    std::printf("no allocations\n");
                }

                std::printf("usage: %u64/%u64 (%u64 free)\n", total_pages - free_pages, total_pages, free_pages);
            }
        } // namespace detail

        void dealloc(void* ptr) {
            auto allocation_start = detail::page_table.page_to_pte(ptr);
            auto allocation_end = detail::page_table.find_allocation_end(allocation_start);

            while (allocation_start <= allocation_end)
                allocation_start++->flags = 0;
        }

        void* alloc(uint64_t n_pages) {
            auto free_ptes = detail::page_table.find_free_range(n_pages);
            if (!free_ptes)
                return nullptr;

            auto page_it = free_ptes;
            const auto range_end = free_ptes + n_pages;
            while (page_it < range_end)
                page_it++->flags |= detail::pte_bits::used;

            (page_it - 1)->flags |= detail::pte_bits::last;

            return detail::page_table.pte_to_page(free_ptes);
        }
    } // namespace linear
} // namespace memory