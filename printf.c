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



#include <stdarg.h>
#include "printf.h"
#include "terminal_driver.h"
#include "memutils.h"
#include "convert.h"

#define DEFAULT_SINK terminal_write
#define PRINTF_BUFFER_SIZE 66


void vprintf(char_sink snk_w, const char* fmt, va_list args)
{
    char buffer[PRINTF_BUFFER_SIZE];

    while(*fmt){
        const char* fmt_spec_begin = strchr(fmt, '%');
        //Do we have a fmt specifier
        if(fmt_spec_begin){
            //First print the string before format begins
            size_t chars_til_fmt = fmt_spec_begin-fmt;
            snk_w(fmt, chars_til_fmt);
            //Advance in the fmt string
            fmt = fmt_spec_begin+1;
            int fmt_min_width = 0;
            int fmt_prepend_zeroes = 0;
            size_t token_length = 0;
            switch_begin:
            switch(*fmt){
                case '%':
                    //Just a literal %
                    snk_w("%",1);
                    ++fmt;
                    break;
                case 'd':
                    //Decimal conversion
                    itoa(10, buffer, va_arg(args, int));
                    for(int i=0;i<fmt_min_width - (int)strlen(buffer); ++i){
                        char filler = fmt_prepend_zeroes ? '0' : ' ';
                        snk_w(&filler, 1);
                    }
                    snk_w(buffer, strlen(buffer));
                    ++fmt;
                    break;
                case 'x':
                    //Hexadecimal
                    itoa(16, buffer, va_arg(args, int));
                    for(int i=0;i<fmt_min_width - (int)strlen(buffer); ++i){
                        char filler = fmt_prepend_zeroes ? '0' : ' ';
                        snk_w(&filler, 1);
                    }
                    snk_w(buffer, strlen(buffer));
                    ++fmt;
                    break;
                case 'c':
                    buffer[0] = va_arg(args, int);
                    buffer[1] = '\0';
                    for(int i=0;i<fmt_min_width - (int)strlen(buffer); ++i){
                        char filler = fmt_prepend_zeroes ? '0' : ' ';
                        snk_w(&filler, 1);
                    }
                    snk_w(buffer, strlen(buffer));
                    ++fmt;
                    break;
                case 's':
                    {
                        const char* str = va_arg(args, char*);
                        snk_w(str, strlen(str));
                    }
                    ++fmt;
                    break;
                case '0':
                    fmt_prepend_zeroes = 1;
                    ++fmt;
                    //We expect more
                    goto switch_begin;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    //Parse min length
                    token_length = strspn(fmt, "0123456789");
                    strncpy(buffer, fmt, token_length);
                    buffer[token_length] = '\0';
                    fmt_min_width = atoi(10, buffer);
                    fmt += token_length;
                    goto switch_begin;

                //After finishing a print we reset
                fmt_min_width = 0;
                fmt_prepend_zeroes = 0;
                token_length = 0;
            }
        }else{
            //Print the reset of the string
            snk_w(fmt, strlen(fmt));
            //We are at the end, stop the loop
            break;
        }
    }

    va_end(args);
}


void printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(CSINK(DEFAULT_SINK), fmt, args);
    va_end(args);
}
