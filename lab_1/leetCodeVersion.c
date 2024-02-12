#include <stdio.h>
#include "math.h"

int main() {
    float x_final = 12.0;
    float y, a;
    int counter = 0;
    printf("Set a: ");
    scanf("%f", &a);
    for (double x = -13.0; x < x_final; x += 2.5) {
        counter ++;
        if ((3 / x) + a * cos(x) == 0 || x == 0) {
            printf("%d %f %f %f\n", counter, NAN, NAN, NAN);
        } else {
            y = 0.9 / (3 / x) + a * cos(x);
            printf("%d %.1f %.2f %.2f\n", counter, x, a, y);
        }
    }
}