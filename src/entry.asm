.global cabi_entry
.global cabi_main
.global cabi_die

.global cabi_mtvec
.global cabi_stvec

.section .text
cabi_die:
    wfi
    j cabi_die

setup_exception_vectors:
    la t0, cabi_mtvec
    csrw mtvec, t0

    la t0, cabi_stvec
    csrw stvec, t0

    ret

.section .text.entry
cabi_entry:
    csrr t0, mhartid  # get the current hart's id
    bnez t0, cabi_die # kill the current hart if it's id isn't 0

    la sp, cabi_stack_end # load the top of the stack to sp

    # ensure we're in machine mode when we enter cabi_main
    li t0, (3 << 11) | (1 << 7) | (1 << 5)
    csrw mstatus, t0
    
    call setup_exception_vectors

    la t0, cabi_main
    csrw mepc, t0

    la ra, cabi_die # this is the return address for cabi_entry and cabi_main

    mret # returns to cabi_main as supervisor
    ret # failsafe: returns to cabi_die

.section .bss
cabi_stack_start:
    .space 65536 # 64KB stack
cabi_stack_end: