OUTPUT_ARCH(riscv)
ENTRY(cabi_entry)

MEMORY {
    ram (RWX) : ORIGIN = 0x80000000, LENGTH = 256M
}

PHDRS {
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS {
    .text : ALIGN(4K) {
        *(.text.entry) *(.text) *(.text.*)
    } > ram AT > ram :text

    .data : ALIGN(4K) {
        *(.data) *(.data.*)
        *(.sdata) *(.sdata.*)
    } > ram AT > ram :data

    .rodata : ALIGN(4K) {
        *(.rodata) *(.rodata.*)
        *(.srodata) *(.srodata.*)
    } > ram AT > ram :data

    .bss : ALIGN(4K) {
        cabi_bss_start = .;

        *(.bss) *(.bss.*)
        *(.sbss) *(.sbss.*)
        . = ALIGN(32);

        cabi_bss_end = .;
    } > ram AT > ram :bss

    . = ALIGN(4K);

    cabi_ram_start = .;
    cabi_ram_end = ORIGIN(ram) + LENGTH(ram);
}