#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>


int isVowel(wchar_t c) {
    return (c == L'а' || c == L'е' || c == L'ё' || c == L'и' || c == L'о' ||
            c == L'у' || c == L'ы' || c == L'э' || c == L'ю' || c == L'я' ||
            c == L'А' || c == L'Е' || c == L'Ё' || c == L'И' || c == L'О' ||
            c == L'У' || c == L'Ы' || c == L'Э' || c == L'Ю' || c == L'Я');
}

void moveVowelsToFront(wchar_t *word) {
    wchar_t temp[100];
    int vIndex = 0, cIndex = 0;

    // Copy vowels to temp array
    for(int i = 0; word[i] != L'\0'; i++) {
        if (isVowel(word[i])) {
            temp[vIndex++] = word[i];
        }
    }

    // Copy consonants to temp array
    for(int i = 0; word[i] != L'\0'; i++) {
        if (!isVowel(word[i])) {
            temp[vIndex + cIndex++] = word[i];
        }
    }

    temp[vIndex + cIndex] = L'\0'; // Ensure null termination
    wcscpy(word, temp); // Copy temp back to word
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    wchar_t parasha[] = L"C:\\Users\\ReFlex\\Documents\\GitHub\\c_lab\\lab_3\\parasha.txt";
    FILE *file = _wfopen(parasha, L"r");
    if (file == NULL) {
        fwprintf(stderr, L"Не удалось открыть файл %ls\n", parasha);
        return 1;
    }
    wchar_t word[100];
    while(fwscanf(file, L"%ls", word) != EOF) {
        moveVowelsToFront(word);
        wprintf(L"%ls ", word);
    }
    fclose(file);
    return 0;
}
