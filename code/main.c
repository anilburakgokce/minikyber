#include <stdio.h>
#include "minikyber.h"
#include "utils.h"

void TestMul(){
#if 1
    poly a = {3,6,2,13}, b = {16,4,11,3}, c = {0};
#else
    poly a = {11,15,1,9}, b = {13,1,1,10}, c = {0};
#endif
    // for(int i = 0; i < kyber_k; i++){
    //     sample_random_poly(a.elements + i);
    //     sample_random_poly(b.elements + i);
    // }
    printf("a: ");
    PrintPoly(&a);
    printf("\n");
    printf("b: ");
    PrintPoly(&b);
    printf("\n");

    mul(&c, &a, &b);
    printf("c: ");
    PrintPoly(&c);
    printf("\n");
}

void TestAddVec(){
    poly_vec a = {3,6,2,13,11,15,1,9}, b = {16,4,11,3,13,1,1,10}, res = {0};
    // for(int i = 0; i < kyber_k; i++){
    //     sample_random_poly(a.elements + i);
    //     sample_random_poly(b.elements + i);
    // }
    
    printf("a: ");
    PrintPolyVec(&a);
    printf("\n");
    printf("b: ");
    PrintPolyVec(&b);
    printf("\n");

    add_vec(&res, &a, &b);
    printf("res: ");
    PrintPolyVec(&res);
    printf("\n");
}

void TestMulVec(){
    poly_vec a = {3,6,2,13,11,15,1,9}, b = {16,4,11,3,13,1,1,10};
    // for(int i = 0; i < kyber_k; i++){
    //     sample_random_poly(a.elements + i);
    //     sample_random_poly(b.elements + i);
    // }
    printf("a: ");
    PrintPolyVec(&a);
    printf("\n");
    printf("b: ");
    PrintPolyVec(&b);
    printf("\n");

    poly res = {0};
    mul_vec(&res, &a, &b);
    printf("res: ");
    PrintPoly(&res);
    printf("\n");
}

void TestMVmul(){
    poly_vec a = {1,0,1,0, 0,1,0,1}, res = {0};
    poly_mat m = {1,1,1,1, 0,0,2,0,
                  0,1,2,3, 1,1,0,0};
    // for(int i = 0; i < kyber_k; i++){
    //     sample_random_poly(a.elements + i);
    //     sample_random_poly(b.elements + i);
    // }
    printf("m: ");
    PrintPolyMat(&m);
    printf("\n");
    printf("a: ");
    PrintPolyVec(&a);
    printf("\n");

    MV_mul(&res, &m, &a);
    printf("res: ");
    PrintPolyVec(&res);
    printf("\n");
}

void TestMVmulTranspose(){
    poly_vec a = {1,0,1,0, 0,1,0,1}, res = {0};
    poly_mat m = {1,1,1,1, 0,1,2,3,
                  0,0,2,0, 1,1,0,0};
    // for(int i = 0; i < kyber_k; i++){
    //     sample_random_poly(a.elements + i);
    //     sample_random_poly(b.elements + i);
    // }
    printf("m: ");
    PrintPolyMat(&m);
    printf("\n");
    printf("a: ");
    PrintPolyVec(&a);
    printf("\n");

    MV_mul_transpose(&res, &m, &a);
    printf("res: ");
    PrintPolyVec(&res);
    printf("\n");
}

void TestEncodeDecode(){
    u8 buf1[kyber_mlen] = {0}, buf2[kyber_mlen] = {0};
    getrandom(buf1, kyber_mlen, 0);
    for(int i = 0; i < kyber_mlen; i++){
        buf1[i] %= kyber_q;
    }

    poly p1 = {0}, p2 = {0};
    encode(&p1, buf1);
    decode(buf2, &p1);
    encode(&p2, buf2);

    printf("buf1: ");
    PrintArray(buf1, kyber_mlen);
    printf("\n");

    printf("p1: ");
    PrintPoly(&p1);
    printf("\n");

    printf("buf2: ");
    PrintArray(buf2, kyber_mlen);
    printf("\n");

    printf("p2: ");
    PrintPoly(&p2);
    printf("\n");
    
}

void TestGenerateA(){
    u8 seed[kyber_seedlen] = {0};
    poly_mat A = {0};

    for(int i = 0; i < kyber_seedlen; i++){
        seed[i] = i*i;
    }

    printf("seed: ");
    for(int i = 0; i < kyber_seedlen; i++){
        printf("%u ", seed[i]);
    }
    printf("\n");

    GenerateA(&A, seed);

    printf("A: \n");
    PrintPolyMat(&A);
    printf("\n");
}

void TestKeyGen(){
    kyber_sk sk = {0};
    kyber_pk pk = {0};
    
    KeyGeneration(&sk, &pk);

    // printf("pk = \n");
    // PrintPublicKey(&pk);
    // printf("\n");

    // printf("sk = \n");
    // PrintSecretKey(&sk);
    // printf("\n");
}

void TestEncapsulation(){
    kyber_sk sk = {0};
    kyber_pk pk = {0};
    
    KeyGeneration(&sk, &pk);

    // printf("pk = \n");
    // PrintPublicKey(&pk);
    // printf("\n");

    // printf("sk = \n");
    // PrintSecretKey(&sk);
    // printf("\n");

    kyber_ct ct = {0};
    u8 ss[32] = {0};
    Encapsulation(&ct, ss, &pk);

    // printf("ct.u:\n");
    // PrintPolyVec(&ct.u);
    // printf("\n");

    // printf("ct.v:\n");
    // PrintPoly(&ct.v);
    // printf("\n");

    // printf("ss: ");
    // for(int i = 0; i < kyber_sslen; i++){
    //     printf("%x ", ss[i]);
    // } printf("\n");
}

// returns 0 iff success
int TestFull(){
    kyber_sk sk = {0};
    kyber_pk pk = {0};
    
    KeyGeneration(&sk, &pk);

    // printf("pk = \n");
    // PrintPublicKey(&pk);
    // printf("\n");

    // printf("sk = \n");
    // PrintSecretKey(&sk);
    // printf("\n");

    kyber_ct ct = {0};
    u8 ss[kyber_sslen] = {0};
    Encapsulation(&ct, ss, &pk);

    // printf("ct.u:\n");
    // PrintPolyVec(&ct.u);
    // printf("\n");

    // printf("ct.v:\n");
    // PrintPoly(&ct.v);
    // printf("\n");

    // printf("ss: ");
    // for(int i = 0; i < kyber_sslen; i++){
    //     printf("%x ", ss[i]);
    // } printf("\n");

    u8 ss_prime[kyber_sslen] = {0};
    Decapsulation(ss_prime, &ct, &sk);

    // printf("ss_prime: ");
    // for(int i = 0; i < kyber_sslen; i++){
    //     printf("%x ", ss_prime[i]);
    // } printf("\n");

    int cmp = memcmp(ss, ss_prime, kyber_sslen);

    return cmp;
}

int main(){
    int res = 0;
    for(int i = 0; i < (1<<16); i++){
        res = TestFull();
        if(res != 0){
            printf("Error! at i = %d\n", i);
            break;
        }
    }
    printf("Test Ended with %s!\n", (res == 0) ? "success" : "failure");
    return 0;
}