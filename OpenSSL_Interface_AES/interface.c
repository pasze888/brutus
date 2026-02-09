#include "aes.h"
#include "crypto_aes.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
int AES_set_encrypt_key(const unsigned char *k, const int bits, AES_KEY *rk) {
  uint8_t *tmp = aes_init(bits % 8);
  aes_key_expansion((uint8_t *)k, tmp);
  if (bits == 256) {
    memcpy(rk->rd_key, tmp, 240);
  } else if (bits == 192) {
    memcpy(rk->rd_key, tmp, 208);
  } else {
    memcpy(rk->rd_key, tmp, 176);
  }
  free(tmp);
  return 0;
}
int AES_encrypt(const unsigned char *input, unsigned char *output,
                AES_KEY *rk) {
  aes_cipher((uint8_t *)input, (uint8_t *)output, (uint8_t *)rk->rd_key);
  return 0;
}

int AES_set_decrypt_key(const unsigned char *k, const int bits, AES_KEY *rk) {
  uint8_t *tmp = aes_init(bits % 8);
  aes_key_expansion((uint8_t *)k, tmp);
  if (bits == 256) {
    memcpy(rk->rd_key, tmp, 240);
  } else if (bits == 192) {
    memcpy(rk->rd_key, tmp, 208);
  } else {
    memcpy(rk->rd_key, tmp, 176);
  }
  free(tmp);
  return 0;
};
int AES_decrypt(const unsigned char *input, unsigned char *output,
                AES_KEY *rk) {
  aes_cipher((uint8_t *)input, (uint8_t *)output, (uint8_t *)rk->rd_key);
  return 0;
}