
SECTIONS{
    . = 0x2100;
    real_stack_top = .;
    _payload_begin = .;
    .text : { *(.text) }
    .data : { *(.data) *(.rodata)}
    _payload_end = .;
    _payload_size_sector = (_payload_end - _payload_begin) / 512 + 1;
    _bss_begin = .;
    .bss  : { *(.bss) }
    _bss_end = .;
    _bss_size = _bss_end - _bss_begin;
    .mbr_block 0x7C00 : { *(.mbr_block) }
}
