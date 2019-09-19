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



#include "gdt.h"

/*
 * The below macros define a 64-bit number which represents a GDT Entry with the chosen properties
 * To add another Entry, simply define a macro with the wanted properties and append it to kload_gdt
 * Then increment GDT_SEL_TOTAL in include/gdtind.h and #define a selector with the corresponding number
 *
 */

//32-bit Code/Data selectors with flat memory (4GB)
#define GDT_CODE_32 (GDT_LIMIT(0xFFFFF) | GDT_BASE(0x000000) | GDT_FLAGS(GRAN_PAGE | MODE32) | \
        GDT_ACCESS(ACC_PRESENT | ACC_PRIV_KERNEL | ACC_CDS | ACC_CODE | ACC_NODC | ACC_RW))

#define GDT_DATA_32 (GDT_LIMIT(0xFFFFF) | GDT_BASE(0x000000) | GDT_FLAGS(GRAN_PAGE | MODE32) | \
        GDT_ACCESS(ACC_PRESENT | ACC_PRIV_KERNEL | ACC_CDS | ACC_DATA | ACC_NODC | ACC_RW))

//16-bit Code/Data selectors for the first MB of memory
#define GDT_CODE_16 (GDT_LIMIT(0xFFFFF) | GDT_BASE(0x000000) | GDT_FLAGS(GRAN_BYTE | MODE16) | \
        GDT_ACCESS(ACC_PRESENT | ACC_PRIV_KERNEL | ACC_CDS | ACC_CODE | ACC_NODC | ACC_RW))

#define GDT_DATA_16 (GDT_LIMIT(0xFFFFF) | GDT_BASE(0x000000) | GDT_FLAGS(GRAN_BYTE | MODE16) | \
        GDT_ACCESS(ACC_PRESENT | ACC_PRIV_KERNEL | ACC_CDS | ACC_DATA | ACC_NODC | ACC_RW))
//Null Descriptor
#define GDT_NULL 0

const uint16_t  kload_gdt_entries = GDT_SEL_TOTAL;
//The Global Descriptor Table that is used during execution of Kloader
const uint64_t  kload_gdt[GDT_SEL_TOTAL] =
    {GDT_NULL,
    GDT_CODE_32,
    GDT_DATA_32,
    GDT_CODE_16,
    GDT_DATA_16};
//GDT descriptor structure given to LGDT
const struct gdt_desc kload_gdt_desc = {GDT_SEL_TOTAL*8-1, (uint32_t)(&kload_gdt)};
