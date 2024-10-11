#pragma once
#include "std/cstdint"

extern "C" {
extern void cabi_mmain();
extern void cabi_entry();
extern void cabi_die();

extern uint8_t *cabi_ram_start, *cabi_ram_end;
extern uint8_t *cabi_bss_start, *cabi_bss_end;
extern uint8_t *cabi_stack_start, *cabi_stack_end;
}