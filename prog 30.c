#include <stdio.h>
#include <stdint.h>

// Block size constants
#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16

// Constants for block sizes
const uint8_t const_Rb_64 = 0x1B;  // Constant for 64-bit block size
const uint8_t const_Rb_128 = 0x87; // Constant for 128-bit block size

// Function to perform left shift on a block
void leftShiftOneBit(uint8_t *block, size_t block_size) {
    uint8_t carry = 0;

    for (size_t i = 0; i < block_size; i++) {
        uint8_t next_carry = (block[i] & 0x80) ? 1 : 0;
        block[i] = (block[i] << 1) | carry;
        carry = next_carry;
    }
}

// Function to generate subkeys for CMAC
void generateSubkeys(const uint8_t *const_Rb, uint8_t *subkey1, uint8_t *subkey2, size_t block_size) {
    // Initialize a block with all zeros
    uint8_t zeros[BLOCK_SIZE_128] = {0};

    // Apply the block cipher to the block of zeros
    // (In practice, a real block cipher would be used)
    // Here, we simulate it by performing a left shift
    leftShiftOneBit(zeros, block_size);

    // Conditionally XOR with a constant
    if ((zeros[0] & 0x80) != 0) {
        for (size_t i = 0; i < block_size; i++) {
            zeros[i] ^= const_Rb[i];
        }
    }

    // Copy the result to subkey1
    for (size_t i = 0; i < block_size; i++) {
        subkey1[i] = zeros[i];
    }

    // Perform left shift on subkey1
    leftShiftOneBit(subkey1, block_size);

    // Conditionally XOR with a constant
    if ((subkey1[0] & 0x80) != 0) {
        for (size_t i = 0; i < block_size; i++) {
            subkey1[i] ^= const_Rb[i];
        }
    }

    // Copy the result to subkey2
    for (size_t i = 0; i < block_size; i++) {
        subkey2[i] = subkey1[i];
    }

    // Perform an additional left shift if needed (for 128-bit block size)
    if (block_size == BLOCK_SIZE_128) {
        leftShiftOneBit(subkey2, block_size);

        // Conditionally XOR with a constant
        if ((subkey2[0] & 0x80) != 0) {
            for (size_t i = 0; i < block_size; i++) {
                subkey2[i] ^= const_Rb[i];
            }
        }
    }
}

int main() {
    // Subkeys for 64-bit block size
    uint8_t subkey1_64[BLOCK_SIZE_64];
    uint8_t subkey2_64[BLOCK_SIZE_64];

    // Subkeys for 128-bit block size
    uint8_t subkey1_128[BLOCK_SIZE_128];
    uint8_t subkey2_128[BLOCK_SIZE_128];

    // Generate subkeys for 64-bit block size
    generateSubkeys(&const_Rb_64, subkey1_64, subkey2_64, BLOCK_SIZE_64);

    // Generate subkeys for 128-bit block size
    generateSubkeys(&const_Rb_128, subkey1_128, subkey2_128, BLOCK_SIZE_128);

    // Print the generated subkeys
    printf("Subkey 1 (64-bit): ");
    for (size_t i = 0; i < BLOCK_SIZE_64; i++) {
        printf("%02x ", subkey1_64[i]);
    }
    printf("\n");

    printf("Subkey 2 (64-bit): ");
    for (size_t i = 0; i < BLOCK_SIZE_64; i++) {
        printf("%02x ", subkey2_64[i]);
    }
    printf("\n");

    printf("Subkey 1 (128-bit): ");
    for (size_t i = 0; i < BLOCK_SIZE_128; i++) {
        printf("%02x ", subkey1_128[i]);
    }
    printf("\n");

    printf("Subkey 2 (128-bit): ");
    for (size_t i = 0; i < BLOCK_SIZE_128; i++) {
        printf("%02x ", subkey2_128[i]);
    }
    printf("\n");

    return 0;
}
