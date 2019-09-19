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



#ifndef H_GDT
#define H_GDT

//GDT helpers and defintions for 32 bit kload
//Symbols for the predefined GDT in GDT.c
#ifndef ASSEMBLY_INCLUDE
#include <stdint.h>
extern const uint64_t kload_gdt[];
extern const uint16_t kload_gdt_entries;
extern const struct gdt_desc kload_gdt_desc;

struct gdt_desc{
    uint16_t gdt_len;
    uint32_t gdt_start;
}__attribute__((packed));

typedef uint64_t u64;
#endif

//Helper typedef

//Helper macros
#define MASK_SHIFT_L64(x,m,s) (((u64)(x) & (m)) << (s))
#define MASK_SHIFT_R64(x,m,s) (((u64)(x) & (m)) >> (s))
//The shift values are calculated, so that the values end up in the correct location
#define GDT_LIMIT(x) (MASK_SHIFT_L64((x),0xFFFF,0) | MASK_SHIFT_L64((x),0xF0000,32))
#define GDT_BASE(x) (MASK_SHIFT_L64((x),0xFFFFFF,16) | MASK_SHIFT_L64((x),0xFF000000,32))
//Carefull, low order bits are reserved for limit
#define GRAN_BYTE 0x00
#define GRAN_PAGE 0x80

#define MODE32 0x40
#define MODE16 0x00

#define GDT_FLAGS(val) (MASK_SHIFT_L64(val,0xFF,48))

#define ACC_PRESENT   0x80
#define ACC_NOPRESENT 0x00

#define ACC_PRIV_KERNEL 0
#define ACC_PRIV_USER   0x60

//Direction bit:
//Data Selector: 1-Segment grows down 0-Segment grows up
//Code Selector: 1-Lower Privilege execution 0-Same Privilege execution
#define ACC_DC   0x04
#define ACC_NODC 0x00

#define ACC_RW   0x02
#define ACC_NORW 0x00

#define ACC_CODE 0x08
#define ACC_DATA 0x00

//We will only use C/D segments
#define ACC_CDS 0x10
#define ACC_SYS 0x00

#define GDT_ACCESS(val) (MASK_SHIFT_L64(val, 0xFF, 40))

//Reference for the GDT indices used by GDT.c

#define GDT_SEL_TOTAL 5

#define GDT_SEL_NULL            0x00
#define GDT_SEL_CODE32          0x08
#define GDT_SEL_DATA32          0x10
#define GDT_SEL_CODE16          0x18
#define GDT_SEL_DATA16          0x20
#endif
