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



#ifndef H_LOWLEVEL
#define H_LOWLEVEL
#include <stdint.h>

//Common Lowlevel inline assembly functions
//See OSDEV.org Inline assembly Examples
static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %[value], %[portnum]" : : [value] "a"(val), [portnum] "Nd" (port));
}

static inline void outw(uint16_t port, uint16_t val)
{
    asm volatile ("outw %[value], %[portnum]" : : [value] "a"(val), [portnum] "Nd" (port));
}

static inline void outl(uint16_t port, uint32_t val)
{
    asm volatile ("outl %[value], %[portnum]" : : [value] "a"(val), [portnum] "Nd" (port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t retv;
    asm volatile ("inb %[portnum],%[rec]" : [rec] "=a"(retv) : [portnum] "Nd"(port));
    return retv;
}

static inline uint16_t inw(uint16_t port)
{
    uint16_t retv;
    asm volatile ("inw %[portnum],%[rec]" : [rec] "=a"(retv) : [portnum] "Nd"(port));
    return retv;
}

static inline uint32_t inl(uint16_t port)
{
    uint32_t retv;
    asm volatile ("inl %[portnum],%[rec]" : [rec] "=a"(retv) : [portnum] "Nd"(port));
    return retv;
}

//Halt the machine indefinitely
static inline void halt_indef()
{
    asm volatile ("cli\nhlt\n");
    __builtin_unreachable();
}



#endif
