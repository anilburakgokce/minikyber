#include "utils.h"

void PrintArray(u8 *arr, int arrLen){
    for(int i = 0; i < arrLen; i++){
        printf("%x ", arr[i]);
    }
}

void PrintPoly(const poly *p){
    for(int i = 0; i < kyber_n; i++){
        printf("%d ", p->coeffs[i]);
    }
}

void PrintPolyVec(const poly_vec *vec){
    printf("[\n");
    for(int i = 0; i < kyber_k; i++){
        PrintPoly(vec->elements + i);
        printf("\n");
    }
    printf("]");
}

void PrintPolyMat(const poly_mat *mat){
    printf("[\n");
    for(int i = 0; i < kyber_k; i++){
        for(int j = 0; j < kyber_k; j++){
            PrintPoly(mat->elements + i * kyber_k + j);
            printf("\t");
        }
        printf("\n");
    }
    printf("]");
}

void PrintSecretKey(const kyber_sk *sk){
    printf("{\ns = \n");
    PrintPolyVec(&sk->s);
    printf("\n}");
}

void PrintPublicKey(const kyber_pk *pk){
    printf("{\nseedA = \n");
    for(int i = 0; i < kyber_seedlen; i++){
        printf("%u ", pk->seed_A[i]);
    }
    printf("\nt = \n");
    PrintPolyVec(&pk->t);
    printf("\n}");
}
