#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>


int isVowel(wchar_t c) {
    return (c == L'а' || c == L'е' || c == L'ё' || c == L'и' || c == L'о' ||
            c == L'у' || c == L'ы' || c == L'э' || c == L'ю' || c == L'я' ||
            c == L'А' || c == L'Е' || c == L'Ё' || c == L'И' || c == L'О' ||
            c == L'У' || c == L'Ы' || c == L'Э' || c == L'Ю' || c == L'Я');
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
    while(fgetws(word, 100, file) != NULL) {
        wchar_t vowels[100] = L"";
        wchar_t consonants[100] = L"";
        int vIndex = 0, cIndex = 0;
        for(int i = 0; word[i] != L'\0'; i++) {
            if (isVowel(word[i])) {
                vowels[vIndex++] = word[i];
            } else {
                consonants[cIndex++] = word[i];
            }
        }
        vowels[vIndex] = L'\0';
        consonants[cIndex] = L'\0';
        wprintf(L"%ls%ls\n", vowels, consonants);
    }
    fclose(file);
    return 0;
}
