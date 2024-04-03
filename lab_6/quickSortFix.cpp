#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include <algorithm>

void fillMatrix(std::vector<int>& matrix, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i * n + j] = rand() % 100;
        }
    }
}

void printMatrix(const std::vector<int>& matrix, int n) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));  // Объявление рандома
    SetConsoleTextAttribute(h, rand() % 8);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix[i * n + j];
        }
        std::cout << std::endl;
    }
}

int partition(std::vector<int>& matrix, int col, int low, int high, int n) {
    int pivot = matrix[high * n + col];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (matrix[j * n + col] <= pivot) {
            i++;
            std::swap(matrix[i * n + col], matrix[j * n + col]);
        }
    }
    std::swap(matrix[(i + 1) * n + col], matrix[high * n + col]);
    return i + 1;
}

void quickSort(std::vector<int>& matrix, int col, int low, int high, int n) {
    if (low < high) {
        int pi = partition(matrix, col, low, high, n);
        quickSort(matrix, col, low, pi - 1, n);
        quickSort(matrix, col, pi + 1, high, n);
    }
}

void sortColumns(std::vector<int>& matrix, int n) {
    for (int col = 0; col < n; col++) {
        quickSort(matrix, col, 0, n - 1, n);
    }
}

void printMatrix2(const std::vector<int>& matrix, int n) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL)+1);  // Объявление рандома
    SetConsoleTextAttribute(h, rand() % 8);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix[i * n + j];
        }
        std::cout << std::endl;
    }
}

int main() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    GetConsoleScreenBufferInfo(h, &start_attribute);

    int n;

    std::cout << "Set N --> " << std::endl;
    std::cin >> n;

    if (n < 2) {
        std::cerr << "N must be > 2" << std::endl;
        return 1;
    }

    std::vector<int> matrix(n * n);
    std::vector<int> matrix2(n * n);

    std::cout << "Original matrix: " << std::endl;
    fillMatrix(matrix, n);
    printMatrix(matrix, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Quicksort:" << std::endl;
    sortColumns(matrix, n);
    printMatrix2(matrix, n);

    return 0;
}
