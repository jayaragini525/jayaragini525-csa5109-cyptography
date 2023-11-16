#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to remove spaces from a string
void removeSpaces(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

// Function to generate the Playfair matrix from the keyword
void generatePlayfairMatrix(char matrix[5][5], char keyword[]) {
    int len = strlen(keyword);
    int used[26] = {0};
    int row = 0, col = 0;

    // Fill the matrix with the unique letters from the keyword
    for (int i = 0; i < len; i++) {
        char letter = toupper(keyword[i]);
        if (!used[letter - 'A']) {
            matrix[row][col] = letter;
            used[letter - 'A'] = 1;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    // Fill the matrix with the remaining letters
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (letter != 'J' && !used[letter - 'A']) {
            matrix[row][col] = letter;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to find the position of a letter in the matrix
void findPosition(char matrix[5][5], char letter, int *row, int *col) {
    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (matrix[*row][*col] == letter)
                return;
        }
    }
}

// Function to encrypt a pair of letters using the Playfair matrix
void encryptPair(char matrix[5][5], char letter1, char letter2) {
    int row1, col1, row2, col2;
    findPosition(matrix, letter1, &row1, &col1);
    findPosition(matrix, letter2, &row2, &col2);

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

    printf("%c%c", matrix[row1][col1], matrix[row2][col2]);
}

int main() {
    char keyword[100];
    char plaintext[100];
    char matrix[5][5];

    printf("Enter the keyword (uppercase letters only): ");
    scanf("%s", keyword);
    removeSpaces(keyword);

    printf("Enter the plaintext (uppercase letters only): ");
    scanf("%s", plaintext);

    removeSpaces(plaintext);

    generatePlayfairMatrix(matrix, keyword);

    printf("Encrypted Text: ");
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        if (i + 1 < len)
            encryptPair(matrix, plaintext[i], plaintext[i + 1]);
        else
            printf("%c", plaintext[i]);
    }

    printf("\n");

    return 0;
}

