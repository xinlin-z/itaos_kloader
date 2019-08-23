#ifndef H_GDT
#define H_GDT
#include <stdint.h>

//GDT helpers and defintions for 32 bit kload
//Symbols for the predefined GDT in GDT.c
extern const uint64_t kload_gdt[];
extern const uint16_t kload_gdt_entries;

//Helper typedef
typedef uint64_t u64;

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

#define GDT_FLAGS(g,m) (MASK_SHIFT_L64(g | m,0xFF,48))

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

#define GDT_ACCESS(pr, privl, s, ex, dc, rw) (MASK_SHIFT_L64(pr | privl | s | ex | dc | rw, 0xFF, 40))

//Example GDT's (incidentally the ones used for bootstrap)

//32-bit Code Selector with flat memory (4GB)
#define GDT_CODE_32 (GDT_LIMIT(0xFFFFF) | GDT_BASE(0x000000) | GDT_FLAGS(GRAN_PAGE, MODE32) | \
        GDT_ACCESS(ACC_PRESENT, ACC_PRIV_KERNEL, ACC_CDS, ACC_CODE, ACC_NODC, ACC_RW))

#define GDT_DATA_32 (GDT_LIMIT(0xFFFFF) | GDT_BASE(0x000000) | GDT_FLAGS(GRAN_PAGE, MODE32) | \
        GDT_ACCESS(ACC_PRESENT, ACC_PRIV_KERNEL, ACC_CDS, ACC_DATA, ACC_NODC, ACC_RW))

#endif
