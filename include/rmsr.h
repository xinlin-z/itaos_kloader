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



#ifndef H_RMSR
#define H_RMSR
#include <stdint.h>
#include <stddef.h>

struct reg_state{
    uint16_t ax, bx, cx, dx, si, di;
    uint16_t flags_ro; //The flags are read only
} __attribute__((packed));

void rmsr_int(struct reg_state* st, uint8_t int_num);

#endif
