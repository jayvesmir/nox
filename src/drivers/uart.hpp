#pragma once
#include "std/cstdint"

namespace drivers {
    class uart_ns16550a {
        uintptr_t m_base;

      public:
        uart_ns16550a() {}

        uart_ns16550a(uart_ns16550a&&) = delete;
        uart_ns16550a(const uart_ns16550a&) = delete;

        bool init(uintptr_t base);

        uint8_t read();
        void write(uint8_t byte);
    };
} // namespace drivers