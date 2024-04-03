#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include <algorithm>

using namespace std;

struct SortStatsColumn {
    int comparisons;
    int swaps;
};

void fillMatrix(std::vector<std::vector<int>>& matrix, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void printMatrix(std::vector<std::vector<int>>& matrix, int n) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));
    SetConsoleTextAttribute(h, rand() % 8);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

SortStatsColumn bubbleSortColumn(std::vector<std::vector<int>>& matrix, int n, std::vector<std::vector<int>>& matrix2) {
    SortStatsColumn stats = {0, 0};
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            for (int k = 0; k < n - i - 1; ++k) {
                stats.comparisons++;
                if (matrix2[k][j] > matrix2[k + 1][j]) {
                    stats.swaps++;
                    std::swap(matrix2[k][j], matrix2[k + 1][j]);
                }
            }
        }
    }
    return stats;
}

SortStatsColumn selectionSortColumn(std::vector<std::vector<int>>& matrix, int n, std::vector<std::vector<int>>& matrix2) {
    SortStatsColumn stats = {0, 0};
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            int min_index = i;
            for (int k = i + 1; k < n; ++k) {
                stats.comparisons++;
                if (matrix[k][j] < matrix[min_index][j]) {
                    min_index = k;
                }
            }
            std::swap(matrix[i][j], matrix[min_index][j]);
            stats.swaps++;
        }
    }
    return stats;
}

SortStatsColumn insertionSortColumn(std::vector<std::vector<int>>& matrix, int n, std::vector<std::vector<int>>& matrix2) {
    SortStatsColumn stats = {0, 0};
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n; ++i) {
            int key = matrix[i][j];
            int k = i - 1;
            while (k >= 0 && matrix[k][j] > key) {
                stats.comparisons++;
                stats.swaps++;
                matrix[k + 1][j] = matrix[k][j];
                --k;
            }
            matrix[k + 1][j] = key;
            stats.swaps++;
        }
    }
    return stats;
}

SortStatsColumn shellSortColumn(std::vector<std::vector<int>>& matrix, int n, std::vector<std::vector<int>>& matrix2) {
    SortStatsColumn stats = {0, 0};
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                int key = matrix[i][j];
                int k = i;
                while (k >= gap && matrix[k - gap][j] > key) {
                    stats.comparisons++;
                    stats.swaps++;
                    matrix[k][j] = matrix[k - gap][j];
                    k -= gap;
                }
                matrix[k][j] = key;
                stats.swaps++;
            }
        }
    }
    return stats;
}

void printMatrix2(std::vector<std::vector<int>>& matrix2, int n) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL)+1);
    SetConsoleTextAttribute(h, rand() % 8);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix2[i][j];
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

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    std::vector<std::vector<int>> matrix2(n, std::vector<int>(n));

    std::cout << "Original matrix: " << std::endl;
    fillMatrix(matrix, n);
    printMatrix(matrix, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Bubble Sort:" << std::endl;
    bubbleSortColumn(matrix, n, matrix2);
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    SortStatsColumn bubbleStats = bubbleSortColumn(matrix, n, matrix2);
    std::cout << "Bubble Sort Stats:\nComparisons: " << bubbleStats.comparisons << "\nSwaps: " << bubbleStats.swaps << std::endl;

    std::cout << "Selection Sort:" << std::endl;
    selectionSortColumn(matrix, n, matrix2);
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    SortStatsColumn selectionStats = selectionSortColumn(matrix, n, matrix2);
    std::cout << "Selection Sort Stats:\nComparisons: " << selectionStats.comparisons << "\nSwaps: " << selectionStats.swaps << std::endl;

    std::cout << "Insertion Sort:" << std::endl;
    insertionSortColumn(matrix, n, matrix2);
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    SortStatsColumn insertionStats = insertionSortColumn(matrix, n, matrix2);
    std::cout << "Insertion Sort Stats:\nComparisons: " << insertionStats.comparisons << "\nSwaps: " << insertionStats.swaps << std::endl;

    std::cout << "Shell Sort:" << std::endl;
    shellSortColumn(matrix, n, matrix2);
    printMatrix2(matrix2, n);

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    SortStatsColumn shellStats = shellSortColumn(matrix, n, matrix2);
    std::cout << "Shell Sort Stats:\nComparisons: " << shellStats.comparisons << "\nSwaps: " << shellStats.swaps << std::endl;

    return 0;
}