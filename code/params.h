#define kyber_q 3329
#define kyber_n 32
#define kyber_k 2
#define kyber_eta 1
#define kyber_seedlen (kyber_k*kyber_k*kyber_n) // in bytes
#define kyber_sslen 32 // in bytes
#define kyber_mlen_bits kyber_n // message length in bits
#define kyber_mlen ((kyber_n+7)/8) // message length in bytes
#define kyber_root 69 // this is calculated for = 32 and q = 3329
#define kyber_psi 447 // square root of 69 in Zq

#define hash_len 32