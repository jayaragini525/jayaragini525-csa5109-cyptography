#include <stdio.h>

// Define the key matrix
int keyMatrix[2][2] = {
    {9, 4},
    {5, 7}
};

// Function to convert a character to its numerical value
int charToNum(char ch) {
    return (int)(ch - 'a');
}

// Function to convert a numerical value to its character representation
char numToChar(int num) {
    return (char)(num + 'a');
}

// Function to perform matrix multiplication
void multiplyMatrix(int matrix[2][2], int block[2]) {
    int result[2] = {0, 0};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i] += matrix[i][j] * block[j];
        }
    }

    for (int i = 0; i < 2; i++) {
        block[i] = result[i] % 26;
    }
}

// Function to encrypt the message
void encryptMessage(char message[]) {
    int block[2];
    int ciphertext[2];

    for (int i = 0; message[i]; i++) {
        block[i % 2] = charToNum(message[i]);
        if (i % 2 == 1) {
            multiplyMatrix(keyMatrix, block);
            for (int j = 0; j < 2; j++) {
                ciphertext[j] = numToChar(block[j]);
                printf("%c", ciphertext[j]);
            }
        }
    }
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";

    printf("Original Message: %s\n", message);
    printf("Encrypted Message: ");
    encryptMessage(message);

    return 0;
}
