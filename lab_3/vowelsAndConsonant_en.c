#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

int isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y');
}

int main() {
    char parasha[] = "C:\\Users\\Komar\\c_lab\\lab_3\\parasha_2.txt";
    FILE *file = fopen(parasha, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", parasha);
        return 1;
    }
    char word[1000];
    while(fscanf(file, "%s", word) != EOF) {
        char vowels[1000] = "";
        char consonants[1000] = "";
        for(int i = 0; i < strlen(word); i++) {
            if (isVowel(word[i])) {
                strncat(vowels, &word[i], 1);
            } else {
                strncat(consonants, &word[i], 1);
            }
        }
        char res[1000] = "";
        strcpy(res, vowels);
        strcat(res, consonants);
        printf("%s ", res);
    }
    fclose(file);
    return 0;
}
