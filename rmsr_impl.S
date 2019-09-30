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



#define ASSEMBLY_INCLUDE
#include "gdt.h"

//Call a real mode interrupt with a machine state passed by higher level code

.globl rmsr_int_impl
rmsr_int_impl:
    pushl %ebp
    movl  %esp,%ebp
    //Save general register state
    pushal
    //Self-modify Interrupt instruction
    movl 0xC(%ebp),%eax
    movb %al,(INT_OPC)
    //Jump to 16-bit protected mode
    jmp $GDT_SEL_CODE16,$pmod16

    .code16
    pmod16:
    movw $GDT_SEL_DATA16,%ax
    movw %ax,%fs
    movw %ax,%gs
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%ss

    //Disable protected mode
    movl %cr0,%eax
    dec %eax
    movl %eax,%cr0

    jmp $0x00,$real_mode

    real_mode:
    //We use the first segment only
    xorw %ax,%ax
    movw %ax,%fs
    movw %ax,%gs
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%ss

    //Set up the register state that was passed to us
    //Save Base Pointer to stack-frame
    pushw %bp
    movw 0x8(%bp),%bp //BP -> Base of reg_state
    movw (%bp),%ax
    movw 0x2(%bp),%bx
    movw 0x4(%bp),%cx
    movw 0x6(%bp),%dx
    movw 0x8(%bp),%si
    movw 0xA(%bp),%di


    //Execute interrupt
    sti
    .byte 0xCD
    INT_OPC:
    .byte 0x00
    cli

    //Move register values to reg_state
    movw %ax,(%bp)
    movw %bx,0x2(%bp)
    movw %cx,0x4(%bp)
    movw %dx,0x6(%bp)
    movw %si,0x8(%bp)
    movw %di,0xA(%bp)
    //Save FLAGS to the struct
    pushf
    movw %sp,%bx
    movw (%bx),%bx
    movw %bx,0xC(%bp)
    add $0x2,%sp
    popw %bp //Restore old frame

    //Now go back to 32-bit protected mode
    movl %cr0,%eax
    or $1,%eax
    movl %eax,%cr0

    jmp $GDT_SEL_CODE32,$ret_mode32
    .code32
    ret_mode32:
    movl $GDT_SEL_DATA32,%eax
    movl %eax,%fs
    movl %eax,%gs
    movl %eax,%ds
    movl %eax,%es
    movl %eax,%ss
    //Restore register state
    popal
    movl %ebp,%esp
    popl %ebp
    ret
