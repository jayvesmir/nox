#include "arch/csr.hpp"
#include "arch/interrupts.hpp"
#include "arch/memory.hpp"
#include "arch/processor.hpp"
#include "cabi.hpp"
#include "std/cstdint"
#include "std/cstdio"
#include "std/cstring"
#include "std/init.hpp"
#include "util/cast.hpp"

namespace init {
    void clear_bss() {
        const auto start = reinterpret_cast<uint64_t*>(&cabi_bss_start);
        const auto end = reinterpret_cast<uint64_t*>(&cabi_bss_end);

        // can't use memset here because it'd corrupt its own stack
        for (auto it = start; it < end; it++)
            *it = 0;
    }

    void everything() {
        std::init_stdio();
        memory::init(reinterpret_cast<uint8_t*>(&cabi_ram_start), reinterpret_cast<uint8_t*>(&cabi_ram_end));
    }

    // not actually testing anything, but if something is wrong you'll see it in the output yourself
    void run_tests() {
        std::printf("* formatting test *\n- %p %i32 %i64 %x32 %x64 %f32 %f64\n", cabi_entry, (-1), (-1ll), (-1), (-1ull), -1.0f,
                    -1.0);

        std::printf("* page allocator test *\n\n");

        constexpr auto n_test_pages = 16;

        auto single = memory::page::allocate_page(1);
        std::printf("- allocated page: %p\n", single);

        std::printf("\n");
        memory::page::detail::page_table.dump_to_console();
        std::printf("\n");

        auto many = memory::page::allocate_page(n_test_pages);
        std::printf("- allocated %i32 pages: %p\n\n", n_test_pages, many);

        memory::page::detail::page_table.dump_to_console();
        std::printf("\n");

        memory::page::deallocate_page(single);
        std::printf("- deallocated page: %p\n\n", single);

        memory::page::detail::page_table.dump_to_console();
        std::printf("\n");

        memory::page::deallocate_page(many);
        std::printf("- deallocated %i32 pages: %p\n\n", n_test_pages, many);

        memory::page::detail::page_table.dump_to_console();
        std::printf("\n");
    }
} // namespace init

void main() {
    std::printf("\n+ nox started +\n");
    init::run_tests();

    cabi_die();
}

extern "C" {
[[clang::noinline]] void cabi_mmain() {
    init::clear_bss();
    init::everything();

    // setup exception vectors
    csr::write<csr::CSR_M_TVEC>(util::ptr_to_addr(interrupt_handlers::machine_trap));
    csr::write<csr::CSR_S_TVEC>(util::ptr_to_addr(interrupt_handlers::supervisor_trap));

    csr::set_bits<csr::CSR_M_STATUS>(3 << 11); // set MPP to supervisor
    csr::set_bits<csr::CSR_M_STATUS>(1 << 7); // enable machine interrupts
    csr::set_bits<csr::CSR_M_STATUS>(1 << 5); // enable supervisor interrupts

    if (processor::ext::supports_f()) {
        processor::ext::enable_f();
        std::printf("* enabled F extension\n");
    }

    if (processor::ext::supports_v()) {
        processor::ext::enable_v();
        std::printf("* enabled V extension: VLEN=%i64\n", csr::read<csr::CSR_VLENB>() * 8);
    }

    csr::write<csr::CSR_M_EPC>(util::ptr_to_addr(main));
    asm volatile("mret");
}
}