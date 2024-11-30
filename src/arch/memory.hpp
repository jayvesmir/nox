#pragma once
#include "std/cstdint"

namespace memory {
    namespace page {
        namespace detail {
            struct pte {
                enum flag_bits : uint8_t {
                    used = (1 << 0),
                    last = (1 << 1),
                };

                uint8_t flags;
            };

            struct pt {
                pte* pages;
                uintptr_t total_pages;

                pte* page_to_pte(void* ptr);
                void* pte_to_page(pte* entry);
                pte* find_allocation_end(pte* entry);
                pte* find_free_range(uint64_t n_pages);

                void dump_to_console();
            };

            extern uint8_t* mem_start;
            extern uint8_t* mem_end;
            extern uint8_t* usable_start;

            extern pt page_table;
        } // namespace detail

        constexpr auto page_size = 4096;

        void deallocate_page(void* ptr);
        void* allocate_page(uint64_t n_pages);
    } // namespace page

    namespace sv39 {
        
    }

    void init(uint8_t* begin, uint8_t* end);
} // namespace memory