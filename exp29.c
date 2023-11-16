#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Block size (in bytes)
#define BLOCK_SIZE 8

// Function to perform a basic block cipher operation (XOR in this case)
void blockCipher(uint8_t *input, const uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        input[i] ^= key[i];
    }
}

// Function to calculate the CBC-MAC for a one-block message
void cbcMac(const uint8_t *key, const uint8_t *message, uint8_t *mac) {
    // Initialization vector (IV) for CBC-MAC
    uint8_t iv[BLOCK_SIZE] = {0};

    // Encrypt the one-block message
    blockCipher(mac, key);

    // Finalize the CBC-MAC by XORing the result with the last block
    for (int i = 0; i < BLOCK_SIZE; i++) {
        mac[i] ^= message[i];
    }
}

int main() {
    // Secret key for CBC-MAC
    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

    // One-block message
    uint8_t message[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    // Calculate CBC-MAC for the one-block message
    uint8_t mac[BLOCK_SIZE];
    cbcMac(key, message, mac);

    // Concatenate the one-block message with (X XOR T)
    uint8_t twoBlockMessage[2 * BLOCK_SIZE];
    memcpy(twoBlockMessage, message, BLOCK_SIZE);
    blockCipher(twoBlockMessage + BLOCK_SIZE, mac);

    // Calculate CBC-MAC for the two-block message
    uint8_t macTwoBlock[BLOCK_SIZE];
    cbcMac(key, twoBlockMessage, macTwoBlock);

    // Check if the MACs are the same
    if (memcmp(mac, macTwoBlock, BLOCK_SIZE) == 0) {
        printf("The MACs are the same for one-block and two-block messages.\n");
    } else {
        printf("The MACs are different.\n");
    }

    return 0;
}
