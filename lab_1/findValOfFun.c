#include <stdio.h>
#include <windows.h>
#include "math.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    double x_final = 12.0;
    double y;
    double a;
    int counter = 0;
    double matrix[10][4];
    printf("Установите a: \n");
    scanf("%lf", &a);
    printf("n    x    a    y\n");
    for (double x = -13.0; x < x_final; x += 2.5) {
        counter += 1;
        double divider = (3 / x) + a * cos(x);
        if (divider == 0 || x == 0) {
            matrix[counter - 1][0] = counter;
            matrix[counter - 1][1] = NAN;
            matrix[counter - 1][2] = NAN;
            matrix[counter - 1][3] = NAN;
        } else {
            y = 0.9 / divider;
            matrix[counter - 1][0] = counter;
            matrix[counter - 1][1] = x;
            matrix[counter - 1][2] = a;
            matrix[counter - 1][3] = y;
        }
    }
    for (int i = 0; i < 10; i++) {
        if ((int)matrix[i][0] < 10) {
            printf(" %d %.1f %.2f %.2f\n", (int) matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
        } else printf("%d %.1f %.2f %.2f\n", (int) matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
    }
    return 0;
} 