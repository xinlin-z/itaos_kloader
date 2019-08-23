//Code embedded into the master boot record
//Loaded by the bios at 0x7C00

//Default value for now
#define EMBED_IMG_LBA 1


.section .mbr_block
.code16
mbr_begin:
    cld
    xorw %ax,%ax
    movw %ax,%fs
    movw %ax,%gs
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%ss
    movw $real_stack_top,%sp
    movb %dl,(b_dl)

    //Test for extension support
    movb $0x41,%ah
    movw $0x55AA,%bx
    movb $0x80,%dl
    int $0x13
    jc lba_fail

    cli
    hlt

//BIOS print routine
BIOS_PRINT:
    lodsb
    orb %al,%al
    jz BIOS_PRINT_DONE
    movb $0x0E,%ah
    int $0x10
    jmp BIOS_PRINT
BIOS_PRINT_DONE:
    ret

//If LBA failes halt indefinitely
lba_fail:
    movw $failed_lba_msg,%si
    call BIOS_PRINT
    cli
    hlt

b_dl:
    .byte 0x00
failed_lba_msg:
    .ascii "LBAFAIL\0"

//Make this sector bootable
.org 510
.byte 0x55
.byte 0xAA
