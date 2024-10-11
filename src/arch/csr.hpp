#pragma once
#include "std/cstdint"

namespace csr {
    enum csr_register {
        CSR_M_ISA = 0x10000000,
        CSR_M_HART_ID,
        CSR_M_STATUS,
        CSR_M_TVEC,
        CSR_M_EPC,

        CSR_S_TVEC = 0x20000000,

        CSR_VLENB = 0x80000000,
    };

    template <csr::csr_register reg_t> uintreg_t read();
    template <csr::csr_register reg_t> uintreg_t write(uintreg_t value);
    template <csr::csr_register reg_t> uintreg_t set_bits(uintreg_t value);
    template <csr::csr_register reg_t> uintreg_t clear_bits(uintreg_t value);
} // namespace csr