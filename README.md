# MiniKyber

A minimal C implementation of a Kyber-like post-quantum key encapsulation mechanism (KEM), designed for educational purposes.

## Features

- Simple modular arithmetic over small primes
- Bit-based message encoding and decoding
- Basic CPA-secure key encapsulation and decapsulation
- Depends on the `getrandom` function from the Linux C library `sys/random.h`
- Easily readable

## Parameters

- q = 97
- n = 4 (polynomial degree)
- Coefficients in {-1,0,1} for small polynomials

## Build and Run

```bash
cd code
bash build.sh
../build/minikyber_test