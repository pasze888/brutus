/*
 * Copyright 2002-2020 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#define AES_ENCRYPT 1
#define AES_DECRYPT 0

#define AES_MAXNR 14

/* This should be a hidden type, but EVP requires that the size be known */
struct aes_key_st {
#ifdef AES_LONG
  unsigned long rd_key[4 * (AES_MAXNR + 1)];
#else
  unsigned int rd_key[4 * (AES_MAXNR + 1)];
#endif
  int rounds;
};
typedef struct aes_key_st AES_KEY;
int AES_set_encrypt_key(const unsigned char *k, const int bits, AES_KEY *rk);
int AES_encrypt(const unsigned char *input, unsigned char *output, AES_KEY *rk);
int AES_set_decrypt_key(const unsigned char *k, const int bits, AES_KEY *rk);
int AES_decrypt(const unsigned char *input, unsigned char *output, AES_KEY *rk);