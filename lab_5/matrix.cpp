#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

HANDLE hStdout;

void fillMatrix(int *matrix, int n) {
    int i, j;
    srand(time(NULL));  // Объявление рандома
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i * n + j] = rand() % 100; // Заполнение случайными числами от 0 до 99
        }
    }
}

void numberSwap(int *matrix, int n, int k, int l) { // Войд для построчного переноса цифр с индексом K и L
    int i;
    for (i = 0; i < n; i++) {
        int tempK, tempL;
        tempK = matrix[i * n + k];
        tempL = matrix[i * n + l];
        matrix[i * n + l] = tempK;
        matrix[i * n + k] = tempL;
    }
}

void printMatrix(int *matrix, int n) {
    srand(time(NULL));  // Объявление рандома
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, rand() % 8);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%-3d", matrix[i * n + j]);
        }
        printf("\n");
    }
}

void printSwappedMatrix(int *matrix, int n) {
    srand(time(NULL) + 1);  // Объявление рандома
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, rand() % 9);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%-3d", matrix[i * n + j]);
        }
        printf("\n");
    }
}

int main() {
    int n, k, l;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    GetConsoleScreenBufferInfo(hStdOut, &start_attribute);

    printf("Set N --> \n");
    scanf("%d", &n); // Вносим N

    printf("Set K --> \n");
    scanf("%d", &k); // Вносим K

    printf("Set L --> \n");
    scanf("%d", &l); // Вносим L
    if (n < 2) {
        fprintf(stderr, "N must be > 2");
        return 1;
    }
    if (k > n) {
        fprintf(stderr, "K must be smaller that N");
        return 1;
    }
    if (l > n) {
        fprintf(stderr, "L must be smaller that N");
        return 1;
    }
    if (k == l || l == k) {
        fprintf(stderr, "L cannot be equal K");
        return 1;
    }
    if (k < 0) {
        fprintf(stderr, "K must be positive");
        return 1;
    }
    if (l < 0) {
        fprintf(stderr, "L must be positive");
        return 1;
    }

    // Выше представленны проверки для входных данных

    int *matrix = (int *)malloc(n * n * sizeof(int)); // Выделяем память под массив

    printf("Original matrix: \n");

    fillMatrix(matrix, n);
    printMatrix(matrix, n);

    SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);  // Восстанавливаем цвет консоли

    printf("\nChanged matrix: \n");

    numberSwap(matrix, n, k, l);
    printSwappedMatrix(matrix, n);

    free(matrix); // Очищаем память

    SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);  // Восстанавливаем цвет консоли

    return 0;
}