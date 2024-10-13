.global cabi_entry
.global cabi_mmain
.global cabi_die

.section .text
cabi_die:
    wfi
    j cabi_die

.section .text.entry
cabi_entry:
    csrr t0, mhartid # check ifthe currect hart is the main one
    bnez t0, cabi_die # kill any harts that don't have an id of 0

    la sp, cabi_stack_end # load the top of the stack to sp
    j cabi_mmain

.section .bss
cabi_stack_start:
    .space 65536 # 64KB stack
cabi_stack_end: