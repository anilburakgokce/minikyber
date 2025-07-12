#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include "minikyber.h"
void PrintArray(u8 *arr, int arrLen);
void PrintPoly(const poly *p);
void PrintPolyVec(const poly_vec *vec);
void PrintPolyMat(const poly_mat *mat);
void PrintSecretKey(const kyber_sk *sk);
void PrintPublicKey(const kyber_pk *pk);

#endif