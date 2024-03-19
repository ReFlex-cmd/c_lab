#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include <algorithm>

struct SortStats {
    int comparisons;
    int swaps;
};

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
    srand(time(NULL));
    SetConsoleTextAttribute(h, rand() % 8);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix[i * n + j];
        }
        std::cout << std::endl;
    }
}

SortStats bubbleSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2) {
    SortStats stats = {0, 0};
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            for (int k = 0; k < n - i - 1; ++k) {
                stats.comparisons++;
                if (matrix2[k * n + j] > matrix2[(k + 1) * n + j]) {
                    stats.swaps++;
                    std::swap(matrix2[k * n + j], matrix2[(k + 1) * n + j]);
                }
            }
        }
    }
    return stats;
}

SortStats selectionSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2) {
    SortStats stats = {0, 0};
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            int min_index = i;
            for (int k = i + 1; k < n; ++k) {
                stats.comparisons++;
                if (matrix2[k * n + j] < matrix2[min_index * n + j]) {
                    min_index = k;
                }
            }
            if (min_index != i) {
                stats.swaps++;
                std::swap(matrix2[i * n + j], matrix2[min_index * n + j]);
            }
        }
    }
    return stats;
}

SortStats insertionSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2) {
    SortStats stats = {0, 0};
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n; ++i) {
            int key = matrix2[i * n + j];
            int k = i - 1;
            while (k >= 0 && matrix2[k * n + j] > key) {
                stats.comparisons++;
                matrix2[(k + 1) * n + j] = matrix2[k * n + j];
                stats.swaps++;
                --k;
            }
            matrix2[(k + 1) * n + j] = key;
        }
    }
    return stats;
}

SortStats shellSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2) {
    SortStats stats = {0, 0};
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                int temp = matrix2[i * n + j];
                int k;
                for (k = i; k >= gap && matrix2[(k - gap) * n + j] > temp; k -= gap) {
                    matrix2[k * n + j] = matrix2[(k - gap) * n + j];
                    stats.comparisons++;
                }
                matrix2[k * n + j] = temp;
                stats.swaps++;
            }
        }
    }
    return stats;
}

SortStats quickSortColumn(std::vector<int>& matrix, int column, int n) {
    SortStats stats = {0, 0};
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
    SortStats bubbleStats = bubbleSortColumn(matrix, n, matrix2);
    SortStats selectionStats = selectionSortColumn(matrix, n, matrix2);
    std::cout << "Bubble Sort Stats:\nComparisons: " << bubbleStats.comparisons << "\nSwaps: " << bubbleStats.swaps << std::endl;
    std::cout << "Selection Sort Stats:\nComparisons: " << selectionStats.comparisons << "\nSwaps: " << selectionStats.swaps << std::endl;
    // Остальная часть кода
    return 0;
}
