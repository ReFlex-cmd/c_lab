#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include "math.h"
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");

    int x_One = -10;
    int x_Two = 5;
    float x = x_One;
    float step = 1.5;
    float a;
    float result;

    printf("Hello world\n\n");

    printf("                   0,5\n  Формула :_____________________\n           a - (sin(x) + cos(x))\n\n");
    printf("  x --> [-10;5] с шагом 1,5\n\n");


    printf("  Введите число a -->  ");

    scanf("%f", &a);

    printf("\n| №п.п |     x     |        a        |       y       |\n");

    for (int i = 1; i < 12; i++)
    {
        if ((a - (sin(x) + cos(x))) == 0)
        {
            printf("|%30s|", "Всё плохо, знаменатель = 0");
        }
        else
        {
            result = 0.5 / (a - (sin(x) + cos(x)));
            printf("|%6d| %-9.2f | %-15lf | %-13e |\n", i, x, a, result);
        }

        x += step;
    }

    _getch();
}