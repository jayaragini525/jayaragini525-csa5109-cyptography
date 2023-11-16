#include <stdio.h>
#include <string.h>

// Function to preprocess the plaintext and remove spaces and handle 'I' and 'J' as one letter
void preprocessText(char plaintext[], char preprocessedText[]) {
    int len = strlen(plaintext);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (plaintext[i] == ' ') {
            continue;
        } else if (plaintext[i] == 'I' || plaintext[i] == 'J') {
            preprocessedText[j++] = 'I';
        } else {
            preprocessedText[j++] = plaintext[i];
        }
    }

    preprocessedText[j] = '\0';
}

// Function to find the position of a character in the Playfair matrix
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a message using the Playfair cipher
void encryptPlayfair(char matrix[5][5], char plaintext[]) {
    char preprocessedText[100];
    preprocessText(plaintext, preprocessedText);

    int len = strlen(preprocessedText);

    for (int i = 0; i < len; i += 2) {
        char ch1 = preprocessedText[i];
        char ch2 = preprocessedText[i + 1];

        int row1, col1, row2, col2;
        findPosition(matrix, ch1, &row1, &col1);
        findPosition(matrix, ch2, &row2, &col2);

        if (row1 == row2) {
            col1 = (col1 + 1) % 5;
            col2 = (col2 + 1) % 5;
        } else if (col1 == col2) {
            row1 = (row1 + 1) % 5;
            row2 = (row2 + 1) % 5;
        } else {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        printf("%c%c ", matrix[row1][col1], matrix[row2][col2]);
    }
}

int main() {
    char matrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    encryptPlayfair(matrix, plaintext);
    
    return 0;
}
