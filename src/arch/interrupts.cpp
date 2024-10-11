#include "std/cstdint"
#include "std/cstdio"

namespace interrupt_handlers {
    [[gnu::interrupt("machine")]] void machine_trap() {
        uintreg_t cause, val;

        asm volatile("csrr %0, mcause" : "=r"(cause));
        asm volatile("csrr %0, mtval" : "=r"(val));

        if (cause & (1ull << 63))
            return;

        std::printf("machine exception at %p: 0x%x\n", val, cause);
    }

    [[gnu::interrupt("supervisor")]] void supervisor_trap() {
        uintreg_t cause, val;

        asm volatile("csrr %0, scause" : "=r"(cause));
        asm volatile("csrr %0, stval" : "=r"(val));

        if (cause & (1ull << 63))
            return;

        std::printf("supervisor exception at %p: 0x%x\n", val, cause);
    }
} // namespace interrupt_handlers