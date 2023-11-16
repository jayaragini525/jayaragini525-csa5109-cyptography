#include <stdio.h>
#include <string.h>

void decrypt(char* ciphertext, int shift, char* decryptedtext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            decryptedtext[i] = ((ciphertext[i] - 'a' - shift + 26) % 26) + 'a';
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            decryptedtext[i] = ((ciphertext[i] - 'A' - shift + 26) % 26) + 'A';
        } else {
            decryptedtext[i] = ciphertext[i]; // Leave non-alphabetic characters unchanged
        }
    }
    decryptedtext[len] = '\0';
}

int main() {
    char ciphertext[] = "Lsv tvklulha fvbz av dvpaoa";
    char decryptedtext[100];
    int shift;

    printf("Ciphertext: %s\n", ciphertext);
    printf("Possible plaintexts:\n");

    for (shift = 0; shift < 26; shift++) {
        decrypt(ciphertext, shift, decryptedtext);
        printf("Shift %d: %s\n", shift, decryptedtext);
    }

    return 0;

