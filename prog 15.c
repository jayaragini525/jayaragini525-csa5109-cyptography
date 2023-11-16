#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char letter;
    int frequency;
} LetterFrequency;

void calculateFrequency(char* text, LetterFrequency* frequencies) {
    for(int i = 0; i < 26; i++) {
        frequencies[i].letter = 'A' + i;
        frequencies[i].frequency = 0;
    }

    int len = strlen(text);
    for(int i = 0; i < len; i++) {
        if(isalpha(text[i])) {
            char letter = toupper(text[i]);
            frequencies[letter - 'A'].frequency++;
        }
    }
}

void sortByFrequency(LetterFrequency* frequencies) {
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 25 - i; j++) {
            if(frequencies[j].frequency < frequencies[j+1].frequency) {
                LetterFrequency temp = frequencies[j];
                frequencies[j] = frequencies[j+1];
                frequencies[j+1] = temp;
            }
        }
    }
}

int main() {
    char ciphertext[] = "Lsv tvklulha fvbz av dvpaoa";
    LetterFrequency frequencies[26];

    calculateFrequency(ciphertext, frequencies);
    sortByFrequency(frequencies);

    printf("Ciphertext: %s\n", ciphertext);
    printf("Possible plaintexts (in rough order of likelihood):\n");

    for(int i = 0; i < 10; i++) {
        char shift = frequencies[i].letter - 'E';
        for(int j = 0; j < strlen(ciphertext); j++) {
            if(isalpha(ciphertext[j])) {
                char decrypted = ((ciphertext[j] - 'A' - shift + 26) % 26) + 'A';
                if(islower(ciphertext[j])) {
                    decrypted = tolower(decrypted);
                }
                printf("%c", decrypted);
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n");
    }

    return 0;
}
