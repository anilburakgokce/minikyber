#ifndef _POLY_H
#define _POLY_H

#include<inttypes.h>
#include<sys/random.h>
#include "params.h"

typedef uint8_t u8;
typedef int16_t i16;
typedef int32_t i32;
typedef struct {
    i16 coeffs[kyber_n];
} poly;

void add(poly *out, const poly *a, const poly *b);
void sub(poly *out, const poly *a, const poly *b);
void acc(poly *out, const poly *a, const poly *b);
void mul(poly *out, const poly *a, const poly *b);
void madd(poly *out, const poly *a, const poly *b);
void sample_small_poly(poly *out);
void sample_random_poly(poly *out);
void encode(poly *p, const u8 *m);
void decode(u8 *m, const poly *p);
void modq(poly *p);

i16 modexp(i16 base, int exp, int mod);

#endif