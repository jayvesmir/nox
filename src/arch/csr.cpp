#include "arch/csr.hpp"

namespace csr {
    template <> [[gnu::naked]] uintreg_t read<csr::CSR_MSTATUS>() {
        asm volatile("csrr a0, mstatus");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t write<csr::CSR_MSTATUS>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrw a0, mstatus, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t set_bits<csr::CSR_MSTATUS>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrs a0, mstatus, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t clear_bits<csr::CSR_MSTATUS>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrc a0, mstatus, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t read<csr::CSR_MISA>() {
        asm volatile("csrr a0, misa");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t write<csr::CSR_MISA>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrw a0, misa, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t set_bits<csr::CSR_MISA>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrs a0, misa, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t clear_bits<csr::CSR_MISA>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrc a0, misa, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t read<csr::CSR_VLENB>() {
        asm volatile("csrr a0, vlenb");
        asm volatile("ret");
    }
} // namespace csr