#include "cabi.hpp"
#include "std/cstdint"
#include "std/cstdio"

extern "C" {
[[gnu::interrupt("machine")]] void cabi_mtvec() {
    uintreg_t cause, val;

    asm volatile("csrr %0, mcause" : "=r"(cause));
    asm volatile("csrr %0, mtval" : "=r"(val));

    if (cause & (1ull << 63))
        return;

    std::printf("machine exception at %p: 0x%x\n", val, cause);
}

[[gnu::interrupt("supervisor")]] void cabi_stvec() {
    uintreg_t cause, val;

    asm volatile("csrr %0, scause" : "=r"(cause));
    asm volatile("csrr %0, stval" : "=r"(val));

    if (cause & (1ull << 63))
        return;

    std::printf("supervisor exception at %p: 0x%x\n", val, cause);
}
}