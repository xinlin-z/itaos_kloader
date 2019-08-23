#include "gdt.h"

#define KLOAD_GDT_ENTRIES 2
const uint16_t  kload_gdt_entries = KLOAD_GDT_ENTRIES;
const uint64_t  kload_gdt[KLOAD_GDT_ENTRIES] = {GDT_CODE_32,GDT_DATA_32};
