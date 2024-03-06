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

void findMax(int *matrix, int n, int k) {
    int max = matrix[0]; // Предполагаем, что первый элемент матрицы - максимальный
    int maxRow = 0; // Предполагаем, что максимальное значение находится в первой строке

    // Находим максимальный элемент и его номер строки
    for (int i = 0; i < n; i++) {
        if (matrix[i * n + k - 1] > max) {
            max = matrix[i * n + k - 1]; // Если текущий элемент больше максимального, обновляем максимальное значение
            maxRow = i; // Обновляем номер строки с максимальным значением
        }
    }

    // Выводим информацию о максимальном элементе
    printf("The maximum value in the %d-th column: %d, is located in the %d-th row\n", k, max, maxRow + 1);

    // Переставляем максимальный элемент на место k-ой строки и k-ого столбца
    int temp = matrix[k - 1 + maxRow * n]; // Сохраняем текущий элемент в k-ой строке и k-ом столбце во временной переменной
    matrix[k - 1 + maxRow * n] = matrix[(k - 1) * n + k - 1]; // Переставляем максимальный элемент в k-ую строку и k-ый столбец
    matrix[(k - 1) * n + k - 1] = temp; // Помещаем сохраненное значение в ячейку, откуда был взят максимальный элемент
}


void printMatrix(int *matrix, int n) {
    srand(time(NULL));  // Объявление рандома
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, rand() % 8); // Применяем рандом к цвету текста
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%-3d", matrix[i * n + j]);
        }
        printf("\n");
    }
}

int main() {
    int n, k;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    GetConsoleScreenBufferInfo(hStdOut, &start_attribute); // Вот эти три строчки
    // нужны что бы запомнить стартовый цвет терминала

    printf("Set N --> \n");
    scanf("%d", &n); // Вносим N

    printf("Set K --> \n");
    scanf("%d", &k); // Вносим K

    if (n < 2) {
        fprintf(stderr, "N must be > 2");
        return 1;
    }
    if (k > n) {
        fprintf(stderr, "K must be smaller that N");
        return 1;
    }

    if (k < 0) {
        fprintf(stderr, "K must be positive");
        return 1;
    }

    // Выше представленны проверки для входных данных

    int *matrix = (int *)malloc(n * n * sizeof(int)); // Выделяем память под массив

    printf("Original matrix: \n");

    fillMatrix(matrix, n);
    printMatrix(matrix, n);

    SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);  // Восстанавливаем цвет консоли

    printf("\nChanged matrix: \n");

    findMax(matrix, n, k);
    printMatrix(matrix, n);

    free(matrix); // Очищаем память

    SetConsoleTextAttribute(hStdOut, start_attribute.wAttributes);  // Восстанавливаем цвет консоли

    return 0;
}