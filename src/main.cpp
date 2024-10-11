#include "arch/csr.hpp"
#include "arch/interrupts.hpp"
#include "arch/processor.hpp"
#include "cabi.hpp"
#include "std/cstdint"
#include "std/cstdio"
#include "std/init.hpp"

namespace init {
    void clear_bss() {
        const auto start = reinterpret_cast<uint64_t*>(&cabi_bss_start);
        const auto end = reinterpret_cast<uint64_t*>(&cabi_bss_end);
        for (auto it = start; it < end; it++)
            *it = 0;
    }

    void setup_serial_console() {
        std::init_stdio();
    }
} // namespace init

void main() {
    std::printf("\n+ nox started +\n");
    std::printf("* formatting test *\n- %p %i32 %i64 %x32 %x64 %f32 %f64\n", main, (-1), (-1ll), (-1), (-1ull), -1.0f, -1.0);

    cabi_die();
}

extern "C" {
[[clang::noinline]] void cabi_mmain() {
    if (csr::read<csr::CSR_M_HART_ID>() != 0)
        cabi_die();

    init::clear_bss();
    init::setup_serial_console();

    // setup exception vectors
    csr::write<csr::CSR_M_TVEC>(reinterpret_cast<uintreg_t>(interrupt_handlers::machine_trap));
    csr::write<csr::CSR_S_TVEC>(reinterpret_cast<uintreg_t>(interrupt_handlers::supervisor_trap));

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

    csr::write<csr::CSR_M_EPC>(reinterpret_cast<uintreg_t>(main));
    asm volatile("mret");
}
}