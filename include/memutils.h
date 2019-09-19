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



#ifndef H_MEMUTILS
#define H_MEMUTILS
#include <stddef.h>
#include <stdint.h>

void *memmove(void* str1, const void* str2, size_t n);
void *memset(void* str, int c, size_t n);
size_t strlen(const char* str);
char* strcpy(char* dst, const char* src);
void* memcpy(void* str1, const void* str2, size_t n);
char *strchr(const char *str, int c);
size_t strspn(const char *str1, const char *str2);
char* strncpy(char* dst, const char* src, size_t n);
#endif
