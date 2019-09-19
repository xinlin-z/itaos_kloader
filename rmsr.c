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



#include "rmsr.h"
#include "idt.h"
//Implementation in rmsr_impl.S
extern void rmsr_int_impl(struct reg_state* st, uint8_t inum);

//Calls a real mode interrupt

void rmsr_int(struct reg_state* st, uint8_t inum)
{
    //We save the current IDT and load the one at 0x00
    struct idt_desc old_idt;
    struct idt_desc real_mode_idt = {0x3FF, 0x00};
    sidt(&old_idt);
    lidt(&real_mode_idt);

    rmsr_int_impl(st, inum);

    lidt(&old_idt);
}
