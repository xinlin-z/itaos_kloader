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



#include "memutils.h"

//Find first null char and return length
size_t strlen(const char* str)
{
    size_t l = 0;
    while(*str++){++l;}
    return l;
}

//Handles overlapping memory areas
void* memmove(void* str1, const void* str2, size_t n)
{
    unsigned char* str1_in = str1;
    const unsigned char* str2_in = str2;
    if(str1_in < str2_in){
        //Copy from start of str2
        for(int i=0;i<n;++i){
            str1_in[i] = str2_in[i];
        }
    }else{
        for(int i=n-1;i>=0; --i){
            str1_in[i] = str2_in[i];
        }
    }
    return str1;
}


void* memset(void* str, int c, size_t n)
{
    unsigned char* str_in = str;
    unsigned char c_in = (unsigned char)c;
    while(n--){
        *str_in++ = c_in;
    }
    return str;
}

void* memcpy(void* str1, const void* str2, size_t n)
{
    char* str1_i = (char*)str1;
    const char* str2_i = (char*)str2;
    for(int i=0; i<n; ++i){
        str1_i[i] = str2_i[i];
    }
    return str1;
}

//Some string related functions

char* strcpy(char* dst, const char* src)
{
    char* old_dst = dst;
    while(*src){
        *dst++ = *src++;
    }
    //Copy null terminator
    *dst = '\0';
    return old_dst;
}
char* strncpy(char* dst, const char* src, size_t n)
{
    char* old_dst = dst;
    int i=0;
    while(*src && i<n){
        *dst++ = *src++;
        ++i;
    }
    for(;i<n;++i){
        *dst++ = '\0';
    }
    return old_dst;
}

char *strchr(const char *str, int c)
{
    char chr = (char)c;
    while(*str){
        if(*str == chr){return (char*)str;}
        //Else increment
        ++str;
    }
    return NULL;
}

size_t strspn(const char *str1, const char *str2)
{
    int span_l = 0;
    while(str1[span_l] && strchr(str2, str1[span_l])){
        ++span_l;
    }
    return span_l;
}
