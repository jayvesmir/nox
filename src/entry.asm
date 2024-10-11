.global cabi_entry
.global cabi_mmain
.global cabi_die

.global cabi_mtvec
.global cabi_stvec

.section .text
cabi_die:
    wfi
    j cabi_die

.section .text.entry
cabi_entry:
    la sp, cabi_stack_end # load the top of the stack to sp
    j cabi_mmain

.section .bss
cabi_stack_start:
    .space 65536 # 64KB stack
cabi_stack_end: