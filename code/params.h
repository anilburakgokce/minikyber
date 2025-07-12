#define kyber_q 97
#define kyber_n 4
#define kyber_k 2
#define kyber_eta 1
#define kyber_seedlen (kyber_k*kyber_k*kyber_n)
#define kyber_sslen 32
#define kyber_mlen_bits kyber_n // mlen is in bits
#define kyber_mlen ((kyber_n+3)/4)

#define hash_len 32