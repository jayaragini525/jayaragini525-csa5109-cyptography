#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void handleErrors(void)
{
    fprintf(stderr, "Error occurred.\n");
    exit(EXIT_FAILURE);
}

void ecb_encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext)
{
    AES_KEY ecb_key;
    if (AES_set_encrypt_key(key, 128, &ecb_key) < 0)
        handleErrors();

    AES_encrypt(plaintext, ciphertext, &ecb_key);
}

void ecb_decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *plaintext)
{
    AES_KEY ecb_key;
    if (AES_set_decrypt_key(key, 128, &ecb_key) < 0)
        handleErrors();

    AES_decrypt(ciphertext, plaintext, &ecb_key);
}

void cbc_encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext)
{
    AES_KEY cbc_key;
    if (AES_set_encrypt_key(key, 128, &cbc_key) < 0)
        handleErrors();

    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &cbc_key, iv, AES_ENCRYPT);
}

void cbc_decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext)
{
    AES_KEY cbc_key;
    if (AES_set_decrypt_key(key, 128, &cbc_key) < 0)
        handleErrors();

    AES_cbc_encrypt(ciphertext, plaintext, ciphertext_len, &cbc_key, iv, AES_DECRYPT);
}

int main()
{
    const unsigned char key[16] = "0123456789abcdef";
    const unsigned char iv[16] = "1234567890abcdef";
    const char *plaintext = "This is a block.";
    int plaintext_len = strlen(plaintext);

    unsigned char ciphertext_ecb[16];
    unsigned char decryptedtext_ecb[16];

    unsigned char ciphertext_cbc[32];
    unsigned char decryptedtext_cbc[32];

    // ECB mode
    ecb_encrypt((unsigned char *)plaintext, plaintext_len, key, ciphertext_ecb);
    ecb_decrypt(ciphertext_ecb, 16, key, decryptedtext_ecb);

    printf("ECB Mode:\n");
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++)
        printf("%02x", ciphertext_ecb[i]);
    printf("\n");
    printf("Decryptedtext: %s\n\n", decryptedtext_ecb);

    // CBC mode
    cbc_encrypt((unsigned char *)plaintext, plaintext_len, key, iv, ciphertext_cbc);
    cbc_decrypt(ciphertext_cbc, 32, key, iv, decryptedtext_cbc);

    printf("CBC Mode:\n");
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < 32; i++)
        printf("%02x", ciphertext_cbc[i]);
    printf("\n");
    printf("Decryptedtext: %s\n", decryptedtext_cbc);

    return 0;
}

