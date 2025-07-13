# MiniKyber

A minimal C implementation of a Kyber-like post-quantum key encapsulation mechanism (KEM), designed for educational purposes.

## Features

- Simple modular arithmetic over small primes
- Bit-based message encoding and decoding
- Basic CPA-secure key encapsulation and decapsulation
- Easily readable

## Dependencies

- `getrandom` function from the Linux C library `sys/random.h`
- `stdio.h`
- `string.h`
- `inttypes.h`

## Parameters

- q = 3329
- n = 32 (polynomial degree)
- Coefficients in {-1,0,1} for small polynomials

## Build and Run

```bash
cd code
bash build.sh
../build/minikyber_test