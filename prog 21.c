#include <stdio.h>

// Function to perform a circular left shift on a 5-bit array
void circularLeftShift(int *arr, int size) {
    int temp = arr[0];
    for (int i = 0; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = temp;
}

// Function to perform the initial permutation
void initialPermutation(int *input, int *output) {
    int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
    for (int i = 0; i < 8; ++i) {
        output[i] = input[IP[i] - 1];
    }
}

// Function to perform the final permutation
void finalPermutation(int *input, int *output) {
    int FP[] = {4, 1, 3, 5, 7, 2, 8, 6};
    for (int i = 0; i < 8; ++i) {
        output[i] = input[FP[i] - 1];
    }
}

// Function to perform the key generation
void generateKeys(int *key, int *key1, int *key2) {
    int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};

    // Permutation P10
    int tempKey[10];
    for (int i = 0; i < 10; ++i) {
        tempKey[i] = key[P10[i] - 1];
    }

    // Circular Left Shift (LS-1)
    circularLeftShift(tempKey, 5);
    circularLeftShift(tempKey + 5, 5);

    // Permutation P8 to get key1
    for (int i = 0; i < 8; ++i) {
        key1[i] = tempKey[P8[i] - 1];
    }

    // Circular Left Shift (LS-2)
    circularLeftShift(tempKey, 5);
    circularLeftShift(tempKey + 5, 5);

    // Circular Left Shift (LS-2) again to get key2
    circularLeftShift(tempKey, 5);
    circularLeftShift(tempKey + 5, 5);

    // Permutation P8 to get key2
    for (int i = 0; i < 8; ++i) {
        key2[i] = tempKey[P8[i] - 1];
    }
}

// Function to perform the expansion permutation
void expansionPermutation(int *input, int *output) {
    int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};
    for (int i = 0; i < 8; ++i) {
        output[i] = input[EP[i] - 1];
    }
}

// Function to perform the XOR operation on two arrays
void xorOperation(int *arr1, int *arr2, int size) {
    for (int i = 0; i < size; ++i) {
        arr1[i] ^= arr2[i];
    }
}

// Function to perform the S-Box substitution on a 4-bit array
void sBoxSubstitution(int *input, int *output) {
    int S0[4][4] = {{1, 0, 3, 2},
                    {3, 2, 1, 0},
                    {0, 2, 1, 3},
                    {3, 1, 3, 2}};
    int S1[4][4] = {{0, 1, 2, 3},
                    {2, 0, 1, 3},
                    {3, 0, 1, 0},
                    {2, 1, 0, 3}};

    int row = input[0] * 2 + input[3];
    int col = (input[1] << 1) + input[2];

    int sBoxValue = 0;

    if (input[4] == 0) {
        sBoxValue = S0[row][col];
    } else {
        sBoxValue = S1[row][col];
    }

    output[0] = (sBoxValue >> 1) & 1;
    output[1] = sBoxValue & 1;
}

// Function to perform the permutation
void permutation(int *input, int *output, int *permutationOrder, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = input[permutationOrder[i] - 1];
    }
}

// Function to perform the f function
void fFunction(int *right, int *subkey, int *output) {
    int expanded[8];
    expansionPermutation(right, expanded);
    xorOperation(expanded, subkey, 8);

    int substituted[8];
    sBoxSubstitution(expanded, substituted);

    permutation(substituted, output, EP, 4);
}

// Function to perform a round in the Feistel network
void feistelRound(int *left, int *right, int *subkey) {
    int temp[4];
    fFunction(right, subkey, temp);
    xorOperation(left, temp, 4);
    for (int i = 0; i < 4; ++i) {
        left[i] ^= right[i];
    }
    for (int i = 0; i < 4; ++i) {
        right[i] = temp[i];
    }
}

// Function to perform the encryption
void encrypt(int *plaintext, int *key, int *ciphertext) {
    int initialPermutationOrder[] = {2, 6, 3, 1, 4, 8, 5, 7};
    int finalPermutationOrder[] = {4, 1, 3, 5, 7, 2, 8, 6};
    int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};

    int key1[8], key2[8];
    generateKeys(key, key1, key2);

    int temp[8];
    permutation(plaintext, temp, initialPermutationOrder, 8);

    int left[4], right[4];
    for (int i = 0; i < 4; ++i) {
        left[i] = temp[i];
        right[i] = temp[i + 4];
    }

    feistelRound(left, right, key1);
    feistelRound(right, left, key2);
    feistelRound(left, right, key1);

    for (int i = 0; i < 4; ++i) {
        temp[i] = left[i];
        temp[i + 4] = right[i];
    }

    permutation(temp, ciphertext, finalPermutationOrder, 8);
}

// Function to perform the decryption
void decrypt(int *ciphertext, int *key, int *plaintext) {
    int initialPermutationOrder[] = {2, 6, 3, 1, 4, 8, 5, 7};
    int finalPermutationOrder[] = {4, 1, 3, 5, 7, 2, 8, 6};
    int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};

    int key1[8], key2[8];
    generateKeys(key, key1, key2);

    int temp[8];
    permutation(ciphertext, temp, initialPermutationOrder, 8);

    int left[4], right[4];
    for (int i = 0; i < 4; ++i) {
        left[i] = temp[i];
        right[i] = temp[i + 4];
    }

    feistelRound(left, right, key1);
    feistelRound(right, left, key2);
    feistelRound(left, right, key1);

    for (int i = 0; i < 4; ++i) {
        temp[i] = left[i];
        temp[i + 4] = right[i];
    }

    permutation(temp, plaintext, finalPermutationOrder, 8);
}

int main() {
    // Test data
    int plaintext[] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0};
    int key[] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1};
    int ciphertext[16], decryptedText[16];

    // Encryption
    encrypt(plaintext, key, ciphertext);

    // Display encrypted result
    printf("Encrypted Result: ");
    for (int i = 0; i < 16; ++i) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");

    // Decryption
    decrypt(ciphertext, key, decryptedText);

    // Display decrypted result
    printf("Decrypted Result: ");
    for (int i = 0; i < 16; ++i) {
        printf("%d", decryptedText[i]);
    }
    printf("\n");

    return 0;
}

