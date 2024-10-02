#include "std/init.hpp"
#include "drivers/uart.hpp"

namespace std {
    namespace detail {
        extern drivers::uart_ns16550a stdout_serial;
    }

    bool init_stdio() {
        return detail::stdout_serial.init(0x10000000);
    }
} // namespace std