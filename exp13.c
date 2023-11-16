#include <stdio.h>
#include <string.h>

char encryptChar(char plain, char key) {
    if (plain >= 'a' && plain <= 'z') {
        return 'a' + (plain - 'a' + key) % 26;
    } else if (plain >= 'A' && plain <= 'Z') {
        return 'A' + (plain - 'A' + key) % 26;
    } else {
        return plain; // Leave non-alphabetic characters unchanged
    }
}

void encrypt(char* plaintext, char* key, char* ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        ciphertext[i] = encryptChar(plaintext[i], key[i] - 'A');
    }
    ciphertext[len] = '\0';
}

void decrypt(char* ciphertext, char* key, char* decryptedtext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        decryptedtext[i] = encryptChar(ciphertext[i], 26 - (key[i] - 'A'));
    }
    decryptedtext[len] = '\0';
}

int main() {
    char plaintext[] = "sendmoremoney";
    char key[] = "90172315221128";
    char ciphertext[14];
    char decryptedtext[14];

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    char newKey[] = "CASHNOTNEEDED";
    decrypt(ciphertext, newKey, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
