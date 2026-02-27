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
// make them available as symbols

#ifdef BRUTUS_NAME
const char brutus_name[] = BRUTUS_NAME;
#endif

#ifdef CRYPTO_KEYBYTES
const int brutus_keybytes = (CRYPTO_KEYBYTES);
#endif

#ifdef CRYPTO_NSECBYTES
const int brutus_nsecbytes = (CRYPTO_NSECBYTES);
#endif

#ifdef CRYPTO_NPUBBYTES
const int brutus_npubbytes = (CRYPTO_NPUBBYTES);
#endif

#ifdef CRYPTO_ABYTES
const int brutus_abytes = (CRYPTO_ABYTES);
#endif

#ifdef CRYPTO_NOOVERLAP
const int brutus_nooverlap = (CRYPTO_NOOVERLAP);
#endif
