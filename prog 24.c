#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to perform modular exponentiation
int modExp(int base, int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int main() {
    // Public key (n, e)
    int n = 77;  // Replace with your actual n value
    int e = 7;   // Replace with your actual e value

    // Plaintext block
    int plaintext = 10;  // Replace with your actual plaintext value

    // Encrypt the plaintext using RSA
    int ciphertext = modExp(plaintext, e, n);

    // Print the ciphertext
    printf("Ciphertext: %d\n", ciphertext);

    // Assume someone tells us that the plaintext block has a common factor with n
    int commonFactor = 11;  // Replace with the common factor

    // Check if the common factor is a non-trivial factor of n
    if (commonFactor > 1 && commonFactor < n && gcd(commonFactor, n) > 1) {
        printf("Potential vulnerability detected! Common factor with n found: %d\n", commonFactor);
    } else {
        printf("No potential vulnerability detected.\n");
    }

    return 0;
}
