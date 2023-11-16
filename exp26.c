#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate modular exponentiation
unsigned long long modExp(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to encrypt a single character using RSA
unsigned long long encryptCharacter(char plaintext, unsigned long long e, unsigned long long n) {
    if (plaintext >= 'A' && plaintext <= 'Z') {
        unsigned long long num = plaintext - 'A';
        return modExp(num, e, n);
    }
    return plaintext;  // If not an uppercase letter, return unchanged
}

int main() {
    // Bob's public key (n, e)
    unsigned long long n = 123456789;  // Replace with a large modulus
    unsigned long long e = 65537;      // Replace with a large public exponent

    // Message from Alice
    char message[] = "HELLO";

    // Encrypt each character individually
    printf("Encrypted message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        unsigned long long ciphertext = encryptCharacter(message[i], e, n);
        printf("%llu ", ciphertext);
    }

    return 0;
}
