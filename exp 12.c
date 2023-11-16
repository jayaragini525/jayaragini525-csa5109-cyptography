#include <stdio.h>

#define MOD 26

void encrypt(int key[3][3], int plaintext[3], int ciphertext[3]) {
    for(int i = 0; i < 3; i++) {
        ciphertext[i] = 0;
        for(int j = 0; j < 3; j++) {
            ciphertext[i] += key[i][j] * plaintext[j];
        }
        ciphertext[i] %= MOD;
    }
}

int main() {
    int key[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    int plaintext[3] = {8, 5, 11};
    int ciphertext[3];

    encrypt(key, plaintext, ciphertext);

    printf("Ciphertext: ");
    for(int i = 0; i < 3; i++) {
        printf("%c", 'A' + ciphertext[i]);
    }
    printf("\n");

    return 0;
}
