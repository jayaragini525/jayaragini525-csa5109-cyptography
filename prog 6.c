#include <stdio.h>
#include <string.h>

int main() {
    char ciphertext[] = "BUBUBUB"; // Replace with your ciphertext
    char plaintext[strlen(ciphertext) + 1];

    for (int a = 1; a < 26; a++) {
        for (int b = 0; b < 26; b++) {
            for (int i = 0; i < strlen(ciphertext); i++) {
                if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                    plaintext[i] = 'A' + (ciphertext[i] - 'A' - b + 26) % 26;
                    plaintext[i] = 'A' + (a * (plaintext[i] - 'A') % 26);
                } else {
                    plaintext[i] = ciphertext[i];
                }
            }

            plaintext[strlen(ciphertext)] = '\0';

            // Check if "BU" is present in the plaintext
            if (strstr(plaintext, "BU") != NULL) {
                printf("Possible solution: a=%d, b=%d\n", a, b);
                printf("Decrypted text: %s\n", plaintext);
            }
        }
    }

    return 0;
}
