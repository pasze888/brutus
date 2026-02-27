// aead_params.c
// 21-Sep-14  Markku-Juhani O. Saarinen <mjos@iki.fi>

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
