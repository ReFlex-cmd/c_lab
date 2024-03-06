#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <ctime>
#include <Windows.h>

void fillMatrix(std::vector<int>& matrix, int n) {
    srand(time(NULL));  // Объявление рандома
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i * n + j] = rand() % 100; // generates a random number between 0 and 99
        }
    }
}

void printMatrix(const std::vector<int>& matrix, int n) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));  // Объявление рандома
    SetConsoleTextAttribute(h, rand() % 8); // Применяем рандом к цвету текста

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix[i * n + j];
        }
        std::cout << std::endl;
    }
}

int main() {
    int n;

    std::cout << "Set N --> " << std::endl;
    std::cin >> n;

    if (n < 2) {
        std::cerr << "N must be > 2" << std::endl;
        return 1;
    }

    std::vector<int> matrix(n * n);

    std::cout << "Original matrix: " << std::endl;
    fillMatrix(matrix, n);
    printMatrix(matrix, n);

    std::cout << "\nChanged matrix: " << std::endl;

    return 0;
}
