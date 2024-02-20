#include <stdio.h>
#include <stdlib.h>

void fillMatrix(int *matrix, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i * n + j] = i * n + j + 1; // Для примера заполняем матрицу числами от 1 до n^2
        }
    }
}

void printMatrix(int *matrix, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i * n + j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 3; // Размерность матрицы
    int *matrix = (int *)malloc(n * n * sizeof(int)); // Выделение памяти под одномерный массив

    fillMatrix(matrix, n); // Заполнение матрицы данными
    printMatrix(matrix, n); // Вывод матрицы

    free(matrix); // Освобождение выделенной памяти

    return 0;
}
