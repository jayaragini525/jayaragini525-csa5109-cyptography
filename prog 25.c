#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to check if a number is prime
int isPrime(int n) {
    if (n <= 1)
        return 0;  // Not prime
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;  // Not prime
    }
    return 1;  // Prime
}

// Function to find the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the modular multiplicative inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;  // Inverse does not exist
}

// Function to generate a new RSA key pair
void generateKeyPair(int *n, int *e, int *d) {
    // Choose two large prime numbers
    int p, q;
    do {
        p = rand() % 100 + 50;  // Adjust the range for larger primes
    } while (!isPrime(p));

    do {
        q = rand() % 100 + 50;  // Adjust the range for larger primes
    } while (!isPrime(q));

    // Calculate modulus n
    *n = p * q;

    // Calculate totient (Euler's totient function)
    int totient = (p - 1) * (q - 1);

    // Choose public exponent e (commonly 65537)
    *e = 65537;

    // Calculate private exponent d
    *d = modInverse(*e, totient);
}

int main() {
    // User's original key pair
    int originalN, originalE, originalD;

    // Simulate Bob's private key leak
    printf("Original key pair:\n");
    generateKeyPair(&originalN, &originalE, &originalD);
    printf("Public key (n, e): (%d, %d)\n", originalN, originalE);
    printf("Private key (n, d): (%d, %d)\n\n", originalN, originalD);

    // Generate a new key pair after the private key leak
    int newN, newE, newD;
    printf("New key pair after private key leak:\n");
    generateKeyPair(&newN, &newE, &newD);
    printf("Public key (n, e): (%d, %d)\n", newN, newE);
    printf("Private key (n, d): (%d, %d)\n", newN, newD);

    return 0;
}
