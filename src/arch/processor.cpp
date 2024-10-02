#include "arch/processor.hpp"
#include "arch/csr.hpp"

namespace processor {
    namespace ext {
        bool supports_f() {
            return csr::read<csr::CSR_MISA>() & (1 << 5);
        }

        bool supports_v() {
            return csr::read<csr::CSR_MISA>() & (1 << 21);
        }

        void enable_v() {
            csr::set_bits<csr::CSR_MSTATUS>(3 << 9);
        }

        void enable_f() {
            csr::set_bits<csr::CSR_MSTATUS>(3 << 13);
        }

        void disable_v() {
            csr::clear_bits<csr::CSR_MSTATUS>(3 << 9);
        }

        void disable_f() {
            csr::clear_bits<csr::CSR_MSTATUS>(3 << 13);
        }
    } // namespace ext

} // namespace processor