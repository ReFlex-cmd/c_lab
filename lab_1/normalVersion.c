#include <stdio.h>
#include <windows.h>
#include "math.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    float x_final = 12.0;
    float y, a;
    int counter = 0;

    printf("Задайте a:\n");
    scanf("%f", &a);

    printf("%-12s %-6s %-7s %-6s\n", "№", "x", "a", "y");

    for (double x = -13.0; x < x_final; x += 2.5) {
        counter++;

        if ((3 / x) + a * cos(x) == 0 || x == 0) {
            printf("%-7d %-7s %-7s %-7s\n", counter, "NAN", "NAN", "NAN");
        } else {
            y = 0.9 / (3 / x) + a * cos(x);
            printf("%-7d %-7.1f %-7.2f %-7.2f\n", counter, x, a, y);
        }
    }

    return 0;
}
