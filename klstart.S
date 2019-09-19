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



//16-bit Entry Point for kloader
#define ASSEMBLY_INCLUDE
#include "gdt.h"

.section .text
.code16

.globl klstart


klstart:
    //Save boot drive number
    pushl %edx
    //Load GDT
    lgdt (kload_gdt_desc)

    //Enable Protected Mode
    cli
    movl %cr0,%eax
    or $1,%eax
    movl %eax,%cr0


    jmp $GDT_SEL_CODE32,$p32mode_entry

.code32
p32mode_entry:
    //Load data Selectors
    movl $GDT_SEL_DATA32,%eax
    movl %eax,%fs
    movl %eax,%gs
    movl %eax,%es
    movl %eax,%ds
    movl %eax,%ss

    //Zero BSS
    xorl %eax,%eax
    movl $_bss_end,%ecx
    subl $_bss_begin,%ecx
    movl $_bss_begin,%edi
    rep stosb

    //Call C entry point kload_main
    call kload_main

    //halt
    hlt
