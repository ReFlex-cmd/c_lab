#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

int isVowel(wchar_t c) {
    return (c == L'а' || c == L'е' || c == L'ё' || c == L'и' || c == L'о' ||
            c == L'у' || c == L'ы' || c == L'э' || c == L'ю' || c == L'я' ||
            c == L'А' || c == L'Е' || c == L'Ё' || c == L'И' || c == L'О' ||
            c == L'У' || c == L'Ы' || c == L'Э' || c == L'Ю' || c == L'Я');
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    wchar_t parasha[] = L"C:\\Users\\Komar\\c_lab\\lab_3\\parasha.txt";
    FILE *file = _wfopen(parasha, L"r");
    if (file == NULL) {
        fwprintf(stderr, L"Не удалось открыть файл %ls\n", parasha);
        return 1;
    }
    wchar_t word[1000];
    while(fwscanf(file, L"%ls", word) != EOF) {
        wchar_t vowels[1000] = L"";
        wchar_t consonants[1000] = L"";
        for(int i = 0; i < wcslen(word); i+=2) {
            if (isVowel(word[i])) {
                wcscat(vowels, &word[i]);
            } else {
                wcscat(consonants, &word[i]);
            }
        }
        wchar_t res[1000] = L"";
        wcscpy(res, vowels);
        wcscat(res, consonants);
        wprintf(L"%ls ", res);
    }
    fclose(file);
    return 0;
}