// aead_params.c
// 21-Sep-14  Markku-Juhani O. Saarinen <mjos@iki.fi>

// Modifications Copyright (c) 2026 pasze88

// get the encryption parameters

#include "aes.hpp"
#include "api.h"
#include <string.h>

// helper functions for implementations
extern "C" {
int crypto_verify_16(const unsigned char *x, const unsigned char *y) {
  return memcmp(x, y, 16) == 0 ? 0 : -1;
}

int crypto_verify_32(const unsigned char *x, const unsigned char *y) {
  return memcmp(x, y, 32) == 0 ? 0 : -1;
}

void crypto_core_aes128encrypt(void *out, void *in, void *k, int flag) {

  Cipher::Aes<128> aes((unsigned char *)k);
  aes.encrypt_block((unsigned char *)out, (unsigned char *)in);
}

void crypto_core_aes256encrypt(void *out, void *in, void *k, int flag) {
  Cipher::Aes<256> aes((unsigned char *)k);
  aes.encrypt_block((unsigned char *)out, (unsigned char *)in);
}

void crypto_core_aes128decrypt(void *out, void *in, void *k, int flag) {
  Cipher::Aes<128> aes((unsigned char *)k);
  aes.decrypt_block((unsigned char *)out, (unsigned char *)in);
}

void crypto_core_aes256decrypt(void *out, void *in, void *k, int flag) {
  Cipher::Aes<256> aes((unsigned char *)k);
  aes.decrypt_block((unsigned char *)out, (unsigned char *)in);
}
}
