#include <stdio.h>
#include <ctype.h>
#include <string.h>
int modInverse(int a, int m) {
    a = a % m;
    int x;
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}
char encrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';
        return ((a * (ch - base) + b) % 26) + base;
    }
    return ch;
}
char decrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';
        int aInverse = modInverse(a, 26);
        if (aInverse == -1) {
            printf("The provided key 'a' is not valid for decryption.\n");
            return ch;
        }
        return ((aInverse * (ch - base - b + 26) % 26) + base);
    }
    return ch;
}
int main() {
    int a, b;
    char plaintext[100]; // Fixed-length array
    char ciphertext[100]; // Fixed-length array

    printf("Enter the value of 'a' (must be relatively prime to 26): ");
    scanf("%d", &a);

    if (a % 2 == 0 || a % 13 == 0) {
        printf("'a' must be relatively prime to 26 for decryption to work.\n");
        return 1;
    }

    printf("Enter the value of 'b': ");
    scanf("%d", &b);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);
    
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = encrypt(plaintext[i], a, b);
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext
    printf("Encrypted text: %s\n", ciphertext);
    for (i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = decrypt(ciphertext[i], a, b);
    }
    plaintext[i] = '\0'; // Null-terminate the plaintext  
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
