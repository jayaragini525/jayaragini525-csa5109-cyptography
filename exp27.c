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

int main() {
    // Public parameters (shared between participants)
    unsigned long long q = 23;  // A prime number
    unsigned long long a = 5;   // A primitive root modulo q

    // Participants' secret numbers
    unsigned long long privateA = 6;  // Alice's secret number
    unsigned long long privateB = 15; // Bob's secret number

    // Calculate public values
    unsigned long long publicA = modExp(a, privateA, q); // Alice's public value
    unsigned long long publicB = modExp(a, privateB, q); // Bob's public value

    // Exchange public values

    // Calculate shared secret
    unsigned long long secretA = modExp(publicB, privateA, q); // Alice's shared secret
    unsigned long long secretB = modExp(publicA, privateB, q); // Bob's shared secret

    // Display results
    printf("Public parameters (q, a): (%llu, %llu)\n", q, a);
    printf("Public values (A, B): (%llu, %llu)\n", publicA, publicB);
    printf("Shared secrets: %llu (Alice) and %llu (Bob)\n", secretA, secretB);

    return 0;
}
