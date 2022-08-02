#ifndef BITTER_H__
#define BITTER_H__

 /* ------------------------------------------------------------------------------*
 | BSD 2-Clause License                                                           |
 |                                                                                | 
 | Copyright (c) 2022, vcsaturninus -- vcsaturninus@protonmail.com                |
 | All rights reserved.                                                           |
 |                                                                                |
 | Redistribution and use in source and binary forms, with or without             |
 | modification, are permitted provided that the following conditions are met:    |
 |                                                                                |
 | 1. Redistributions of source code must retain the above copyright notice, this |
 |    list of conditions and the following disclaimer.                            |
 |                                                                                |
 | 2. Redistributions in binary form must reproduce the above copyright notice,   |
 |    this list of conditions and the following disclaimer in the documentation   |
 |    and/or other materials provided with the distribution.                      |
 |                                                                                |
 | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"    |
 | AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE      |
 | IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE |
 | DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE   |
 | FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL     |
 | DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR     |
 | SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER     |
 | CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,  |
 | OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  |
 | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.           |
 \*-------------------------------------------------------------------------------*/


#include <stdint.h>
#include <stdlib.h>


/* 
 * Bit array */
struct bitr{
    size_t size;
    uint8_t bits[];
};

/* 
 * Allocate new bit array big enough to hold num_bits */
struct bitr *Bitr_new(uint32_t num_bits, bool all_ones);

/*
 * Deallocate bitr */
void Bitr_destroy(struct bitr **bitr);

/*
 * Get the total number of bits the bit array can hold */
uint32_t Bitr_size(const struct bitr *bitr);

/*
 * Set bitr[n-1]. 
 * <-- return
 *     0 on success, -1 on failure (out of bounds).
 */
int Bitr_set(struct bitr *bitr, uint32_t n);

/*
 * Unset bitr[n-1]. 
 * <-- return
 *     0 on success, -1 on failure (out of bounds).
 */
int Bitr_clear(struct bitr *bitr, uint32_t n);

/*
 * Toggle bitr[n-1]. 
 * <-- return
 *     0 on success, -1 on failure (out of bounds).
 */
int Bitr_toggle(struct bitr *bitr, uint32_t n);

/*
 * Get bitr[n-1]. 
 * <-- return
 *     -1 on failure (out of bounds), else 1 if bitr[n-1] 
 *     is turned on, else 0 if bitr[n-1] is turned off.
 */
int Bitr_test(struct bitr *bitr, uint32_t n);


#endif
