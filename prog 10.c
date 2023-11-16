#include <stdio.h>

unsigned long long calculatePossibleKeys() {
    unsigned long long possibleKeys = 1;

    for(int i = 0; i < 5; i++) {
        possibleKeys *= (25 - i);
    }

    return possibleKeys;
}

int main() {
    unsigned long long keys = calculatePossibleKeys();
    printf("Number of possible keys (without considering equivalent keys): %llu\n", keys);

    return 0;
}
