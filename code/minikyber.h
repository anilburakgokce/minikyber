#ifndef _MINIKYBER_H
#define _MINIKYBER_H

#include "params.h"
#include "poly.h"
#include <sys/random.h>
#include <string.h>

typedef struct {
    poly elements[kyber_k];
} poly_vec;

typedef struct{
    poly elements[kyber_k * kyber_k]; // row-major kxk matrix
} poly_mat;

typedef struct{
    u8 seed_A[kyber_seedlen];
    poly_vec t;
} kyber_pk;

typedef struct{
    poly_vec s;
} kyber_sk;

typedef struct{
    poly_vec u;
    poly v;
} kyber_ct;


void GenerateA(poly_mat *A, const u8 *seed);
void add_vec(poly_vec *res, const poly_vec * a, const poly_vec *b);
void mul_vec(poly *res, const poly_vec * a, const poly_vec *b);
void MV_mul(poly_vec *res, const poly_mat *M, const poly_vec *v);
void MV_mul_transpose(poly_vec *res, const poly_mat * M, const poly_vec *v);
void KeyGeneration(kyber_sk *sk, kyber_pk *pk);
void Encapsulation(kyber_ct *ct, u8 *ss, const kyber_pk *pk);
void Decapsulation(u8 *ss, const kyber_ct *ct, const kyber_sk *sk);

#endif