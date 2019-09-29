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



#include <stdint.h>
#include "terminal_driver.h"
#include "a20gate.h"
#include "lowlevel.h"
#include "rmsr.h"
#include "printf.h"


void kload_main(uint8_t boot_drive_num)
{
    terminal_clear();
    printf("--ITAOS Kloader--\n");

    if(!(check_enableA20())){
        tputs("Failed to Enable A20 Gate...Halting\n");
        halt_indef();
    }
    printf("A20 Enabled\n");
    printf("Boot drive number is: %x\n", boot_drive_num);
    printf("halting...\n");
    halt_indef();
}
