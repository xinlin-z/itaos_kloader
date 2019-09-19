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



#include "terminal_driver.h"
#include "memutils.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;


size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = COLOR_ENTRY(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
uint16_t* terminal_buf = (uint16_t*) 0xB8000;

void terminal_clear()
{
    uint16_t* tbuf_ind = terminal_buf;
    size_t n = VGA_WIDTH*VGA_HEIGHT;
    while(n--){
        *tbuf_ind++ = VGA_CHAR(' ', terminal_color);
    }
    terminal_row = 0;
    terminal_column = 0;
}

void terminal_write(const char* str, size_t n)
{
    for(int si = 0; si < n; ++si){
        switch(str[si]){
            case '\n':
                terminal_row++;
                terminal_column = 0;
                break;
            default:
                //Print normal chars
                terminal_buf[terminal_row*VGA_WIDTH+terminal_column] = VGA_CHAR(str[si], terminal_color);
                terminal_column++;
                break;
        }
        if(terminal_column == VGA_WIDTH){
            terminal_row++;
            terminal_column = 0;
        }
        if(terminal_row == VGA_HEIGHT){
            //Terminal Scrolling
            memmove(terminal_buf, &terminal_buf[VGA_WIDTH],sizeof(uint16_t)*(VGA_HEIGHT-1)*VGA_WIDTH);
            for(int i=0; i < VGA_WIDTH; ++i){
                terminal_buf[(VGA_HEIGHT-1)*VGA_WIDTH+i] = VGA_CHAR(' ', terminal_color);
            }
            terminal_row = VGA_HEIGHT-1;
            //terminal_column = 0;
        }
    }
}

void tputs(const char* str)
{
    terminal_write(str, strlen(str));
}
