/*
*    This file is part of itaos_kloader, a Hobbyist Operating System Loader
*    Copyright (C) <2019>  <Henri Gerigk>
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/



//Code embedded into the master boot record
//Loaded by the bios at 0x7C00
#include "buildvar.h"

#ifndef EMBED_IMG_LBA
//If no value is given, use a sane default
#define EMBED_IMG_LBA 1
#endif

//"ax" Marks this section as executable/alloc and is important for objcopy
.section .mbr_block, "ax"
.code16
mbr_begin:
    //Set up a default state
    cld
    xorw %ax,%ax
    movw %ax,%fs
    movw %ax,%gs
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%ss
    movw $real_stack_top,%sp
    //Save boot drive number
    movb %dl,(b_dl)

    //Test for extension support
    movb $0x41,%ah
    movw $0x55AA,%bx
    movb $0x80,%dl
    int $0x13
    jc lba_fail

    movw $early_msg,%si
    call BIOS_PRINT

    //Load the real bootloader and execute it
    movw $dapack,%si
    movb $0x42,%ah
    movb (b_dl),%dl
    int $0x13
    jmp klstart


    cli
    hlt

//This struture is set up correctly at compile time
.align 4
dapack:
    .byte 0x10
    .byte 0x00
    .word _payload_size_sector
    .word _payload_begin
    .word 0x0000
    .long EMBED_IMG_LBA
    .long 0x00


//BIOS print routine
.globl BIOS_PRINT
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
early_msg:
    .ascii "EARLY\0"

//Ensure size of 512-bytes
.org 510
//Make this sector bootable
.byte 0x55
.byte 0xAA
