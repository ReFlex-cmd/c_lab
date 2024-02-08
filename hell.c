#define _CRT_SECURE_NO_WARNINGS // для возможности использования scanf в Visual Studio
#include <stdio.h>
#include <stdlib.h> // для перехода на русский язык
int main()
{
  float y;
  system("chcp 1251"); // переходим в консоли на русский язык
  system("cls");       // очищаем окно консоли
  printf("Введите y: "); // выводим сообщение
  scanf("%f", &y);     // вводим значения переменной y
  printf("Значение переменной y=%f", y); // выводим значение переменной y
  getchar(); getchar();
  return 0;
}