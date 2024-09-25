.global cabi_entry
.global cabi_main

.section .text
cabi_die:
    wfi
    j cabi_die

.section .text.entry
cabi_entry:
    csrr a0, mhartid  # get the current hart's id
    bnez a0, cabi_die # kill the current hart if it's id isn't 0

    la sp, stack_end # load the top of the stack to sp

    call cabi_main
    j cabi_die

.section .bss
stack_start:
    .space 32768 # 32KB stack
stack_end: