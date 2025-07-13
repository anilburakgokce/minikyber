#include "poly.h"
#include "utils.h"

void encode(poly *p, const u8 *m){
    // handle all bytes but not the most significant one
    for(int i = 0; i < kyber_mlen - 1; i++){
        for(int j = 0; j < 8*sizeof(u8); j++){
            p->coeffs[i*8*sizeof(u8) + j] = (((m[i] >> j) & 0x01) == 1) ? kyber_q/2 : 0;
            // printf("j = %d\n", j);
            // PrintPoly(p);
            // printf("\n");
        }
    }

    // handle the last byte
    for(int i = 8 * (kyber_mlen - 1); i < kyber_mlen_bits; i++){
        p->coeffs[i] = (((m[kyber_mlen-1] >> (i&0x7)) & 0x01) == 1) ? kyber_q/2 : 0;
    }
}

void decode(u8 *m, const poly *p){
    memset(m, 0, kyber_mlen);

    // handle all bytes but not the most significant one
    for(int i = 0; i < kyber_mlen - 1; i++){
        for(int j = 0; j < 8*sizeof(u8); j++){
            i16 coeff = p->coeffs[i*8*sizeof(u8)+j];
            m[i] |= ((coeff>kyber_q/4 && coeff<=3*(kyber_q/4)) ? 0x01 : 0x00) << j;
        }
    }

    // handle the last byte
    for(int i = 8 * (kyber_mlen - 1); i < kyber_mlen_bits; i++){
            i16 coeff = p->coeffs[i];
            m[kyber_mlen - 1] |= ((coeff>kyber_q/4 && coeff<=3*(kyber_q/4)) ? 0x01 : 0x00) << (i&0x07);
    }
}

void modq(poly *p){
    for(int i = 0; i < kyber_n; i++){
        p->coeffs[i] = ((p->coeffs[i] % kyber_q) + kyber_q) % kyber_q;
    }
}

// add two polynomials in Rq
void add(poly *out, const poly *a, const poly *b){
    for(int i = 0; i < kyber_n; i++){
        out->coeffs[i] = (a->coeffs[i] + b-> coeffs[i]) % kyber_q;
    }
}

// subtract b from a in Rq
void sub(poly *out, const poly *a, const poly *b){
    for(int i = 0; i < kyber_n; i++){
        out->coeffs[i] = (a->coeffs[i] - b-> coeffs[i] + kyber_q) % kyber_q;
    }
}

// returns out = out + a + b
void acc(poly *out, const poly *a, const poly *b){
    for(int i = 0; i < kyber_n; i++){
        out->coeffs[i] += a->coeffs[i] + b-> coeffs[i];
        out->coeffs[i] %= kyber_q;
    }
}

// multiply two polynomials in Rq
void mul(poly *out, const poly *a, const poly *b){
    i32 res[2*kyber_n-1] = {0};
    for(int i = 0; i < kyber_n; i++){
        for(int j = 0; j < kyber_n; j++){
            res[i+j] += ((i32) a->coeffs[i] * b-> coeffs[j]) % kyber_q;
        }
    }

    for(int i = 0; i < kyber_n - 1; i++){
        out->coeffs[i] = (res[i] - res[i + kyber_n] + kyber_q) % kyber_q;
    } out->coeffs[kyber_n - 1] = res[kyber_n - 1] % kyber_q;
}

// returns out <= out + a * b
void madd(poly *out, const poly *a, const poly *b){
    i32 res[2*kyber_n-1] = {0};
    for(int i = 0; i < kyber_n; i++){
        for(int j = 0; j < kyber_n; j++){
            res[i+j] += ((i32) a->coeffs[i] * b-> coeffs[j]) % kyber_q;
        }
    }
    for(int i = 0; i < kyber_n - 1; i++){
        out->coeffs[i] += (res[i] - res[i + kyber_n] + kyber_q) % kyber_q;
    } out->coeffs[kyber_n - 1] += res[kyber_n - 1] % kyber_q;
    modq(out);
}

// returns a small polynomial with rej.sampling
void sample_small_poly(poly *out){
    u8 buf = 0;
    int i = 0;
    while (i < kyber_n){
        getrandom(&buf, 1, 0);
        buf &= 0x03;
        if(buf == 0x03){
            continue;
        }
        out->coeffs[i] = buf - 1;
        i++;
    }
    // PrintPoly(out);
}

// rejection sampling for random polynomial
void sample_random_poly(poly *out){
    u8 buf;
    int i = 0;
    while(i < 4){
        getrandom(&buf, 1, 0);
        if(buf > 254){
            continue;
        }
        out->coeffs[i] = buf % kyber_q;
        i++;
    }
}