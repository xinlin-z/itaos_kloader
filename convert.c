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



#include "convert.h"
#include "terminal_driver.h"
#include "memutils.h"
#include <stddef.h>

//Convert integer to string
char* itoa(int base, char buf[66], int num)
{
    if(base < 2 || base > 16){buf[0] = '\0'; return NULL;}
    char* buf_ptr = buf;

    while(num){
        *buf_ptr++ = "0123456789abcdef"[num % base];
        num /= base;
    }

    char* buf_lr = buf;
    char* buf_rr = buf_ptr-1;
    char* buf_term = buf_ptr;

    while(buf_lr < buf_rr){
        char tmp = *buf_lr;
        *buf_lr = *buf_rr;
        *buf_rr = tmp;
        ++buf_lr; --buf_rr;
    }
    *buf_term = '\0';
    return buf;
}
//Convert string to integer
int atoi(int base, char buf[66])
{
    if(base < 2 || base > 16){return 0;}
    int value = 0;
    int base_power = 1;

    size_t num_length = strlen(buf);
    for(int i=num_length-1;i>=0;--i){
        value += base_power * (buf[i]-'0');
        base_power *= base;
    }
    return value;
}
