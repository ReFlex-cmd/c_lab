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

void bubbleSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            for (int k = 0; k < n - i - 1; ++k) {
                if (matrix2[k * n + j] > matrix2[(k + 1) * n + j]) {
                    std::swap(matrix2[k * n + j], matrix2[(k + 1) * n + j]);
                }
            }
        }
    }
}

void selectionSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            int min_index = i;
            for (int k = i + 1; k < n; ++k) {
                if (matrix2[k * n + j] < matrix2[min_index * n + j]) {
                    min_index = k;
                }
            }
            std::swap(matrix2[i * n + j], matrix2[min_index * n + j]);
        }
    }
}

void insertionSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n; ++i) {
            int key = matrix2[i * n + j];
            int k = i - 1;
            while (k >= 0 && matrix2[k * n + j] > key) {
                matrix2[(k + 1) * n + j] = matrix2[k * n + j];
                --k;
            }
            matrix2[(k + 1) * n + j] = key;
        }
    }
}

void shellSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                int temp = matrix2[i * n + j];
                int k;
                for (k = i; k >= gap && matrix2[(k - gap) * n + j] > temp; k -= gap) {
                    matrix2[k * n + j] = matrix2[(k - gap) * n + j];
                }
                matrix2[k * n + j] = temp;
            }
        }
    }
}

void quickSortColumn(std::vector<int>& matrix, int column, int n) {
    std::vector<int> columnData;
    for (int i = 0; i < n; ++i) {
        columnData.push_back(matrix[i * n + column]);
    }
    std::sort(columnData.begin(), columnData.end());
    for (int i = 0; i < n; ++i) {
        matrix[i * n + column] = columnData[i];
    }
}

void printMatrix2(const std::vector<int>& matrix2, int n) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL)+1);  // Объявление рандома
    SetConsoleTextAttribute(h, rand() % 8);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix2[i * n + j];
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

    std::cout << "Bubble Sort:" << std::endl;
    bubbleSortColumn(matrix, n, matrix2);
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Selection Sort:" << std::endl;
    selectionSortColumn(matrix, n, matrix2);
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Insertion Sort:" << std::endl;
    insertionSortColumn(matrix, n, matrix2);
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Shell Sort:" << std::endl;
    shellSortColumn(matrix, n, matrix2);
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Quick Sort:" << std::endl;
    for (int j = 0; j < n; ++j) {
        quickSortColumn(matrix, j, n);
    }
    printMatrix2(matrix2, n);

    return 0;
}
