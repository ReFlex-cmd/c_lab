#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

int main() {
    int n, k, l;
    srand(time(NULL));
    printf("Set N --> \n");
    scanf("%d", &n);
    if (n < 2) {
        fprintf(stderr, "N must be > 2");
        return 1;
    }
    printf("Set K --> \n");
    scanf("%d", &k);
    if (k > n) {
        fprintf(stderr, "K must be smaller that N");
        return 1;
    }
    printf("Set L --> \n");
    scanf("%d", &l);
    if (l > n) {
        fprintf(stderr, "L must be smaller that N");
        return 1;
    }
    if (k == l || l == k) {
        fprintf(stderr, "K cannot be equal L");
        return 1;
    }
    int matrix[2 * n];
    for (int i = 0; i < 2 * n; i++) {
        matrix[i] = rand() % 100;
    }
    if (k < 0) {
        fprintf(stderr, "K must be positive");
        return 1;
    }
    if (l < 0) {
        fprintf(stderr, "L must be positive");
        return 1;
    }

}