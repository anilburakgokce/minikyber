#include "minikyber.h"
#include "utils.h"

/// @brief a simple and non-secure hash function
/// @param out: u8 array of length hash_len
/// @param in: u8 array of length inLen
/// @param inLen: the length of in 
void simple_hash(u8* out, const u8 *in, int inLen){
    memset(out, 0, hash_len);
    
    for(int i = 0; i < hash_len; i++){
        out[i] = in[i % inLen];
    }

    for(int i = 0; i < hash_len; i++){
        out[i] = ((out[i] << 3) | (out[i] >> 5)) ^ out[(i+1)%hash_len];
        out[i] ^= 0xA5 ^ i;
    }
}

// m: u8 array of length kyber_mlen
void generate_message(u8 *m){
    getrandom(m, kyber_mlen, 0);
    m[0] &= 0x0f;
}

void add_vec(poly_vec *res, const poly_vec * a, const poly_vec *b){
    for(int i = 0; i < kyber_k; i++){
        add(res->elements + i, a->elements + i, b->elements + i);
    }
}

void acc_vec(poly_vec *res, const poly_vec * a, const poly_vec *b){
    for(int i = 0; i < kyber_k; i++){
        acc(res->elements + i, a->elements + i, b->elements + i);
    }
}

void mul_vec(poly *res, const poly_vec * a, const poly_vec *b){
    memset(res, 0, sizeof(poly));
    for(int i = 0; i < kyber_k; i++){
        madd(res, a->elements + i, b->elements + i);
    }
}

// returns M*v
void MV_mul(poly_vec *res, const poly_mat * M, const poly_vec *v){
    memset(res, 0, sizeof(poly_vec));
    for(int row = 0; row < kyber_k; row++){
        for(int col = 0; col < kyber_k; col++){
            madd(res->elements + row, M->elements + col + row * kyber_k, v->elements + col);
        }
    }
}

// returns M^T * v
void MV_mul_transpose(poly_vec *res, const poly_mat * M, const poly_vec *v){
    memset(res, 0, sizeof(poly_vec));
    for(int row = 0; row < kyber_k; row++){
        for(int col = 0; col < kyber_k; col++){
            madd(res->elements + row, M->elements + col * kyber_k + row, v->elements + col);
        }
    }
}

// generates a polynomial matrix from seed
// seed: a u8 array of length kyber_seedlen
void GenerateA(poly_mat *A, const u8 *seed){
    for(int i = 0; i < kyber_k; i++){
        for (int j = 0; j < kyber_k; j++){
            for(int k = 0; k < kyber_n; k++){
                A->elements[i*kyber_k + j].coeffs[k] = seed[(i * kyber_k + j) * kyber_n + k] % kyber_q;
            }
        }
    }
}

// generates pk-sk pair and returns them
void KeyGeneration(kyber_sk *sk, kyber_pk *pk){
    
    // getrandom(pk->seed_A, kyber_seedlen, 0);
    for(int i = 0; i < kyber_seedlen; i++){
        pk->seed_A[i] = i%2;
    }
    
    poly_mat A = {0};
    GenerateA(&A, pk->seed_A);
    
    // PrintPolyMat(&A);

    for(int i = 0; i < kyber_k; i++){
        sample_small_poly(sk->s.elements + i);
    }

    // printf("sk:\n");
    // PrintPolyVec(&sk->s);
    // printf("\n");

    poly_vec e = {0};
    for(int i = 0; i < kyber_k; i++){
        sample_small_poly(e.elements + i);
    }

    // printf("e:\n");
    // PrintPolyVec(&e);
    // printf("\n");

    MV_mul(&pk->t, &A, &sk->s);
    add_vec(&pk->t, &pk->t, &e);

    // printf("t:\n");
    // PrintPolyVec(&pk->t);
    // printf("\n");
}

// ss: shared secret, length = kyber_sslen
void Encapsulation(kyber_ct *ct, u8 *ss, const kyber_pk *pk){
    poly_vec r = {0}, e1 = {0};
    poly e2 = {0};
    memset(ct, 0, sizeof(kyber_ct));

    // sample small r, e1, and e2
    sample_small_poly(r.elements);
    sample_small_poly(r.elements + 1);
    sample_small_poly(e1.elements);
    sample_small_poly(e1.elements + 1);
    sample_small_poly(&e2);

    poly_mat A = {0};
    GenerateA(&A, pk->seed_A);
    MV_mul_transpose(&ct->u, &A, &r);
    add_vec(&ct->u, &ct->u, &e1);

    u8 m[kyber_mlen] = {0};
    generate_message(m);

    poly pm = {0};
    encode(&pm, m);
    
    mul_vec(&ct->v, &pk->t, &r);

    // printf("tr:\n");
    // PrintPoly(&ct->v);
    // printf("\n");

    // printf("e2:\n");
    // PrintPoly(&e2);
    // printf("\n");

    // printf("pm_enc:\n");
    // PrintPoly(&pm);
    // printf("\n");

    acc(&ct->v, &e2, &pm);

    // printf("res:\n");
    // PrintPoly(&ct->v);
    // printf("\n");

    simple_hash(ss, m, kyber_mlen);

    // printf("m_enc:\n");
    // PrintArray(m, kyber_mlen);
    // printf("\n");

}

// ss: shared secret, length = kyber_sslen
void Decapsulation(u8 *ss, const kyber_ct *ct, const kyber_sk *sk){
    poly pm = {0};
    u8 m[kyber_mlen] = {0};

    mul_vec(&pm, &ct->u, &sk->s);
    
    // printf("v:\n");
    // PrintPoly(&ct->v);
    // printf("\n");

    // printf("u.s:\n");
    // PrintPoly(&pm);
    // printf("\n");

    sub(&pm, &ct->v, &pm);

    // printf("pm_dec:\n");
    // PrintPoly(&pm);
    // printf("\n");
    
    decode(m, &pm);

    // printf("m_dec:\n");
    // PrintArray(m, kyber_mlen);
    // printf("\n");

    simple_hash(ss, m, kyber_mlen);
}
