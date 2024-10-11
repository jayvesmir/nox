#include "arch/csr.hpp"

namespace csr {
    template <> [[gnu::naked]] uintreg_t read<csr::CSR_M_STATUS>() {
        asm volatile("csrr a0, mstatus");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t write<csr::CSR_M_STATUS>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrw a0, mstatus, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t set_bits<csr::CSR_M_STATUS>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrs a0, mstatus, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t clear_bits<csr::CSR_M_STATUS>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrc a0, mstatus, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t read<csr::CSR_M_ISA>() {
        asm volatile("csrr a0, misa");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t read<csr::CSR_M_HART_ID>() {
        asm volatile("csrr a0, mhartid");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t read<csr::CSR_M_TVEC>() {
        asm volatile("csrr a0, mtvec");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t write<csr::CSR_M_TVEC>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrw a0, mtvec, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t read<csr::CSR_S_TVEC>() {
        asm volatile("csrr a0, stvec");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t write<csr::CSR_S_TVEC>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrw a0, stvec, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t read<csr::CSR_M_EPC>() {
        asm volatile("csrr a0, mepc");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t write<csr::CSR_M_EPC>(uintreg_t value) {
        asm volatile("mv a1, a0");
        asm volatile("csrrw a0, mepc, a1");
        asm volatile("ret");
    }

    template <> [[gnu::naked]] uintreg_t read<csr::CSR_VLENB>() {
        asm volatile("csrr a0, vlenb");
        asm volatile("ret");
    }
} // namespace csr