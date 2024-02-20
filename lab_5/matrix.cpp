#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

void fillMatrix(int *matrix, int n) {
    int i, j;
    srand(time(NULL));  // Объявление рандома
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i * n + j] = rand() % 100; // Заполнение случайными числами от 0 до 99
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
    int n, k, l;
    printf("Set N --> \n");
    scanf("%d", &n); // Вносим N
    if (n < 2) {
        fprintf(stderr, "N must be > 2");
        return 1;
    }
    printf("Set K --> \n");
    scanf("%d", &k); // Вносим K
    if (k > n) {
        fprintf(stderr, "K must be smaller that N");
        return 1;
    }
    printf("Set L --> \n");
    scanf("%d", &l); // Вносим L
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

    int *matrix = (int *)malloc(n * n * sizeof(int));

    fillMatrix(matrix, n);
    printMatrix(matrix, n);

    free(matrix);

    return 0;

}