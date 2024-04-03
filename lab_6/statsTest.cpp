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
    // TODO implement quick sort
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

void printSortStats(const std::string& sortName, const SortStats& stats) {
    std::cout << sortName << " Stats: " << std::endl;
    std::cout << "Comparisons: " << stats.comparisons << std::endl;
    std::cout << "Swaps: " << stats.swaps << std::endl;
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
    // TODO implement quick sort
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    SortStats bubbleStats = bubbleSortColumn(matrix, n, matrix2);
    SortStats selectionStats = selectionSortColumn(matrix, n, matrix2);
    SortStats insertionStats = insertionSortColumn(matrix, n, matrix2);
    SortStats shellStats = shellSortColumn(matrix, n, matrix2);

    std::cout << "Bubble Sort Stats: " << std::endl;
    std::cout << "Comparisons: " << bubbleStats.comparisons << std::endl;
    std::cout << "Swaps: " << bubbleStats.swaps << std::endl;

    std::cout << "Selection Sort Stats: " << std::endl;
    std::cout << "Comparisons: " << selectionStats.comparisons << std::endl;
    std::cout << "Swaps: " << selectionStats.swaps << std::endl;

    std::cout << "Insertion Sort Stats: " << std::endl;
    std::cout << "Comparisons: " << insertionStats.comparisons << std::endl;
    std::cout << "Swaps: " << insertionStats.swaps << std::endl;

    std::cout << "Shell Sort Stats: " << std::endl;
    std::cout << "Comparisons: " << shellStats.comparisons << std::endl;
    std::cout << "Swaps: " << shellStats.swaps << std::endl;

    // Вывод сравнительной таблицы
    std::cout << "Sort Method\tComparisons\tSwaps" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    printSortStats("Bubble Sort", bubbleStats);
    printSortStats("Selection Sort", selectionStats);
    printSortStats("Insertion Sort", insertionStats);
    printSortStats("Shell Sort", shellStats);

    return 0;
}
