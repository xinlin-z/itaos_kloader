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



#ifndef H_IDT
#define H_IDT
#include <stdint.h>
//The IDT Descriptor passed to lidt
struct idt_desc{
    uint16_t  idt_len;
    uint32_t  idt_start;
} __attribute__((packed));

static inline void lidt(struct idt_desc* p_idt)
{
    asm volatile ("lidt (%[pointer])" : : [pointer] "r" (p_idt) : "memory");
}

static inline void sidt(struct idt_desc* p_idt)
{
    asm volatile ("sidt (%[pointer])" : : [pointer] "r" (p_idt) : "memory");
}

#endif
