#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encryptPolyalphabetic(char message[], const char key[]) {
    int key_len = strlen(key);
    int i;
    for ( i = 0; i < strlen(message); i++) {
        if (isalpha(message[i])) {
            char shift = tolower(key[i % key_len]) - 'a';

            if (islower(message[i])) {
                message[i] = ((message[i] - 'a' + shift) % 26) + 'a';
            } else if (isupper(message[i])) {
                message[i] = ((message[i] - 'A' + shift) % 26) + 'A';
            }
        }
    }
}

int main() {
    char message[100];
    char key[100];

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    if (strlen(message) == 0) {
        printf("Invalid message.\n");
        return 1;
    }

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    if (strlen(key) == 0) {
        printf("Invalid key.\n");
        return 1;
    }
    int key_len = strlen(key);
    int index = 0;
    int i;
    for ( i = 0; i < key_len; i++) {
        if (isalpha(key[i])) {
            key[index] = toupper(key[i]);
            index++;
        }
    }
    key[index] = '\0';

    encryptPolyalphabetic(message, key);

    printf("Encrypted message: %s\n", message);

    return 0;
}
