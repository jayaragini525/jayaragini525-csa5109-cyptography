#include <stdio.h>
#include <string.h>
void decryptCaesarCipher(char message[], int key) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = (message[i] - 'a' - key + 26) % 26 + 'a';
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = (message[i] - 'A' - key + 26) % 26 + 'A';
        }
    }
}

int main() {
    char message[100];
    int key;

    printf("Enter the encrypted message: ");
    fgets(message, sizeof(message), stdin);
    
    printf("Enter the decryption key (0-25): ");
    scanf("%d", &key);

    if (key < 0 || key > 25) {
        printf("Invalid key. Key should be in the range 0-25.\n");
        return 1;
    }

    decryptCaesarCipher(message, key);

    printf("Decrypted message: %s\n", message);

    return 0;
}
