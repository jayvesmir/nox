#include "arch/mmio.hpp"
#include "drivers/uart.hpp"

namespace drivers {
    constexpr auto thr_offset = 0;
    constexpr auto rbr_offset = 0;
    constexpr auto dll_offset = 0;
    constexpr auto ier_offset = 1;
    constexpr auto dlm_offset = 1;
    constexpr auto iir_offset = 2;
    constexpr auto fcr_offset = 2;
    constexpr auto lcr_offset = 3;
    constexpr auto mcr_offset = 4;
    constexpr auto lsr_offset = 5;
    constexpr auto msr_offset = 6;

    bool uart_ns16550a::init(uintptr_t base) {
        m_base = base;

        // enable 14-byte fifo
        mmio::write<uint8_t>(m_base, fcr_offset, 0xc7);

        // 8/1/n | enable dlab
        mmio::write<uint8_t>(m_base, lcr_offset, 0x83);

        // 115200 baud rate
        mmio::write<uint8_t>(m_base, dll_offset, 0x01);
        mmio::write<uint8_t>(m_base, dlm_offset, 0x00);

        // 8/1/n | disable dlab
        mmio::write<uint8_t>(m_base, lcr_offset, 0x03);

        return true;
    }

    uint8_t uart_ns16550a::read() {
        return mmio::read<uint8_t>(m_base, rbr_offset);
    }

    void uart_ns16550a::write(uint8_t byte) {
        mmio::write(m_base, thr_offset, byte);
    }
} // namespace drivers