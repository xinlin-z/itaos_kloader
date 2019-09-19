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



#include "a20gate.h"
#include <stdint.h>
#include <stddef.h>
#include "lowlevel.h"

#define KEYBOARD_PORT1 0x64
#define KEYBOARD_PORT2 0x60

int check_a20_set()
{
    uint32_t* addr1 = (uint32_t*)0x112345;
    uint32_t* addr2 = (uint32_t*)0x012345;

    uint32_t old_val1;
    uint32_t old_val2;

    old_val1 = *addr1;
    old_val2 = *addr2;

    *addr1 = (uint32_t)0xFF;
    *addr2 = (uint32_t)0x00;

    int a20set = (*addr1 == *addr2) ? 0 : 1;

    *addr1 = old_val1;
    *addr2 = old_val2;

    return a20set;
}

static void keyboard_wait_input_buffer()
{
    //Wait until Keyboard controller data input buffer empty
    uint8_t k;
    do{
        k = inb(KEYBOARD_PORT1);
    }while(k & 0x2);
}

static void keyboard_send_cmd(uint8_t cmd)
{
    keyboard_wait_input_buffer();
    outb(KEYBOARD_PORT1, cmd);
}

static void keyboard_wait_output_buffer()
{
    //Waits till output buffer of keyboard controller filled
    uint8_t k;
    do{
        k = inb(KEYBOARD_PORT1);
    }while(!(k & 1));
}

static uint8_t keyboard_get_data()
{
    keyboard_wait_output_buffer();
    return inb(KEYBOARD_PORT2);
}

static void keyboard_send_data(uint8_t d)
{
    keyboard_wait_input_buffer();
    outb(KEYBOARD_PORT2, d);
}

void enableA20Keyboard()
{
    uint8_t d;
    //Request controller output byte
    keyboard_send_cmd(0xD0);
    d=keyboard_get_data();
    //Enable A20 Gate bit
    d = d | 0x2;
    //Send byte to output port
    keyboard_send_cmd(0xD1);
    keyboard_send_data(d);
}

void enableA20Fast()
{
    uint8_t b;
    b = inb(0x92);
    outb(0x92,b|2);
}

int check_enableA20()
{
    if(check_a20_set()){return 1;}
    enableA20Fast();
    if(check_a20_set()){return 1;}
    enableA20Keyboard();
    if(check_a20_set()){return 1;}
    return 0;
}
