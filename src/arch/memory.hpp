#pragma once
#include "std/cstdint"

namespace memory {
    void init(uint8_t* begin, uint8_t* end);

    namespace linear {
        constexpr auto page_size = 4096;

        namespace detail {
            enum pte_bits : uint8_t {
                used = (1 << 0),
                last = (1 << 1),
            };

            struct pte {
                uint8_t flags;
            };

            struct pt {
                pte* pages;
                uintptr_t total_pages;

                void* pte_to_page(pte* entry);
                pte* page_to_pte(void* ptr);
                pte* find_allocation_end(pte* entry);
                pte* find_free_range(uint64_t n_pages);

                void dump_to_console();
            };

            extern uint8_t* mem_start;
            extern uint8_t* mem_end;
            extern uint8_t* usable_start;

            extern pt page_table;
        } // namespace detail

        void dealloc(void* ptr);
        void* alloc(uint64_t n_pages);

    } // namespace linear
} // namespace memory