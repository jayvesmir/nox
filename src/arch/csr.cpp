#include "arch/csr.hpp"

#define CSR_READ_DEF(REG_NAME, REG_ENUM)                    \
    template <> [[gnu::naked]] uintreg_t read<REG_ENUM>() { \
        asm volatile("csrr a0, " #REG_NAME "");             \
        asm volatile("ret");                                \
    }

#define CSR_WRITE_DEF(REG_NAME, REG_ENUM)                                   \
    template <> [[gnu::naked]] uintreg_t write<REG_ENUM>(uintreg_t value) { \
        asm volatile("mv a1, a0");                                          \
        asm volatile("csrrw a0, " #REG_NAME ", a1");                        \
        asm volatile("ret");                                                \
    }

#define CSR_SET_BITS_DEF(REG_NAME, REG_ENUM)                                   \
    template <> [[gnu::naked]] uintreg_t set_bits<REG_ENUM>(uintreg_t value) { \
        asm volatile("mv a1, a0");                                             \
        asm volatile("csrrs a0, " #REG_NAME ", a1");                           \
        asm volatile("ret");                                                   \
    }

#define CSR_CLEAR_BITS_DEF(REG_NAME, REG_ENUM)                                   \
    template <> [[gnu::naked]] uintreg_t clear_bits<REG_ENUM>(uintreg_t value) { \
        asm volatile("mv a1, a0");                                               \
        asm volatile("csrrc a0, " #REG_NAME ", a1");                             \
        asm volatile("ret");                                                     \
    }

namespace csr {
    CSR_READ_DEF(mstatus, csr::CSR_M_STATUS)
    CSR_READ_DEF(misa, csr::CSR_M_ISA)
    CSR_READ_DEF(mhartid, csr::CSR_M_HART_ID)
    CSR_READ_DEF(mtvec, csr::CSR_M_TVEC)
    CSR_READ_DEF(stvec, csr::CSR_S_TVEC)
    CSR_READ_DEF(mepc, csr::CSR_M_EPC)
    CSR_READ_DEF(vlenb, csr::CSR_VLENB)

    CSR_WRITE_DEF(mstatus, csr::CSR_M_STATUS)
    CSR_WRITE_DEF(mtvec, csr::CSR_M_TVEC)
    CSR_WRITE_DEF(stvec, csr::CSR_S_TVEC)
    CSR_WRITE_DEF(mepc, csr::CSR_M_EPC)

    CSR_SET_BITS_DEF(mstatus, csr::CSR_M_STATUS)

    CSR_CLEAR_BITS_DEF(mstatus, csr::CSR_M_STATUS)
} // namespace csr