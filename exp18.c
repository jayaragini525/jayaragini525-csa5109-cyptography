#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt_3des_cbc(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int length) {
    DES_cblock des_key1, des_key2, des_key3;
    DES_key_schedule ks1, ks2, ks3;

    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key + 16, 8);

    DES_set_key_unchecked(&des_key1, &ks1);
    DES_set_key_unchecked(&des_key2, &ks2);
    DES_set_key_unchecked(&des_key3, &ks3);

    DES_ede3_cbc_encrypt(plaintext, ciphertext, length, &ks1, &ks2, &ks3, (DES_cblock *)iv, DES_ENCRYPT);
}

int main() {
    unsigned char plaintext[] = "Hello, World!";
    unsigned char key[] = "MySecretKey";
    unsigned char iv[] = "Initialization";

    int plaintext_length = strlen((char *)plaintext);
    int ciphertext_length = ((plaintext_length + 7) / 8) * 8;
    unsigned char *ciphertext = (unsigned char *)malloc(ciphertext_length);

    encrypt_3des_cbc(plaintext, key, iv, ciphertext, plaintext_length);

    printf("Ciphertext: ");
    for (int i = 0; i < ciphertext_length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    free(ciphertext);

    return 0;
}
