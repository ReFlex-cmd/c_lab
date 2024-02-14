#include <stdio.h>
#include <wchar.h>

int main() {
    // Declare a wide character array
    wchar_t word[1000];

    // Read the word from input
    wprintf(L"Enter a word: ");
    fgetws(word, 1000, stdin);

    // Iterate over each character and print them
    wprintf(L"The characters are: ");
    for (int i = 0; word[i] != L'\0'; ++i) {
        wprintf(L"%lc\n", word[i]);
    }

    return 0;
}
