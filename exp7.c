#include <stdio.h>
#include <string.h>

// Function to generate the cipher sequence from a keyword
void generateCipherSequence(char keyword[], char cipherSequence[]) {
    int i, j = 0;
    int used[26] = {0};

    // Copy the keyword to the cipher sequence
    strcpy(cipherSequence, keyword);

    // Mark letters in the keyword as used
    for(i = 0; i < strlen(keyword); i++) {
        used[keyword[i] - 'A'] = 1;
    }

    // Add remaining unused letters to the cipher sequence
    for(i = 0; i < 26; i++) {
        if(used[i] == 0) {
            cipherSequence[strlen(keyword) + j] = 'A' + i;
            j++;
        }
    }

    cipherSequence[26] = '\0';
}

// Function to encrypt plaintext using the generated cipher sequence
void encrypt(char plaintext[], char cipherSequence[], char ciphertext[]) {
    int i;

    for(i = 0; i < strlen(plaintext); i++) {
        if(plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = cipherSequence[plaintext[i] - 'A'];
        } else if(plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = cipherSequence[plaintext[i] - 'a'] + ('a' - 'A');
        } else {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipherSequence[27];
    char plaintext[] = "hello world";
    char ciphertext[100];

    generateCipherSequence(keyword, cipherSequence);
    encrypt(plaintext, cipherSequence, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
