#include <stdio.h>
#include <string.h>

// Function to find the position of a character in the Playfair matrix
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    int i, j;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decrypt a Playfair cipher message
void decryptPlayfair(char matrix[5][5], char message[]) {
    int i, row1, col1, row2, col2;

    for(i = 0; i < strlen(message); i += 2) {
        if(message[i] == ' ') {
            printf(" ");
            i--;
            continue;
        }

        findPosition(matrix, message[i], &row1, &col1);
        findPosition(matrix, message[i+1], &row2, &col2);

        if(row1 == row2) {
            printf("%c%c", matrix[row1][(col1 + 4) % 5], matrix[row2][(col2 + 4) % 5]);
        } else if(col1 == col2) {
            printf("%c%c", matrix[(row1 + 4) % 5][col1], matrix[(row2 + 4) % 5][col2]);
        } else {
            printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
        }
    }
}

int main() {
    char matrix[5][5] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'E', 'B', 'E'},
        {'Z', 'W', 'E', 'H', 'E'},
        {'W', 'R', 'Y', 'T', 'U'},
        {'H', 'E', 'Y', 'F', 'S'}
    };

    char message[] = "UREBE ZWEHE WRYTU HEYFS";
    decryptPlayfair(matrix, message);

    return 0;
}
