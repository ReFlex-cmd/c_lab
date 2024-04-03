#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include <algorithm>

struct SortStats {
    int comparisons;
    int permutations;
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
    srand(time(NULL));  // Random declaration
    SetConsoleTextAttribute(h, rand() % 8);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix[i * n + j];
        }
        std::cout << std::endl;
    }
}

void bubbleSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2, SortStats& stats) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    stats.comparisons = 0;
    stats.permutations = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            for (int k = 0; k < n - i - 1; ++k) {
                stats.comparisons++;
                if (matrix2[k * n + j] > matrix2[(k + 1) * n + j]) {
                    std::swap(matrix2[k * n + j], matrix2[(k + 1) * n + j]);
                    stats.permutations++;
                }
            }
        }
    }
}

void selectionSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2, SortStats& stats) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    stats.comparisons = 0;
    stats.permutations = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            int min_index = i;
            for (int k = i + 1; k < n; ++k) {
                stats.comparisons++;
                if (matrix2[k * n + j] < matrix2[min_index * n + j]) {
                    min_index = k;
                }
            }
            std::swap(matrix2[i * n + j], matrix2[min_index * n + j]);
            stats.permutations++;
        }
    }
}

void insertionSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2, SortStats& stats) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    stats.comparisons = 0;
    stats.permutations = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n; ++i) {
            int key = matrix2[i * n + j];
            int k = i - 1;
            while (k >= 0 && matrix2[k * n + j] > key) {
                matrix2[(k + 1) * n + j] = matrix2[k * n + j];
                k--;
                stats.comparisons++;
                stats.permutations++;
            }
            matrix2[(k + 1) * n + j] = key;
            stats.permutations++;
        }
    }
}

void shellSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2, SortStats& stats) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    stats.comparisons = 0;
    stats.permutations = 0;
    for (int j = 0; j < n; ++j) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                int temp = matrix2[i * n + j];
                int k;
                for (k = i; k >= gap && matrix2[(k - gap) * n + j] > temp; k -= gap) {
                    matrix2[k * n + j] = matrix2[(k - gap) * n + j];
                    stats.comparisons++;
                    stats.permutations++;
                }
                matrix2[k * n + j] = temp;
                stats.permutations++;
            }
        }
    }
}

int partition(std::vector<int>& matrix, int col, int low, int high, int n, SortStats& stats) {
    int pivot = matrix[high * n + col];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        stats.comparisons++;
        if (matrix[j * n + col] <= pivot) {
            i++;
            std::swap(matrix[i * n + col], matrix[j * n + col]);
            stats.permutations++;
        }
    }
    std::swap(matrix[(i + 1) * n + col], matrix[high * n + col]);
    stats.permutations++;
    return i + 1;
}

void quickSort(std::vector<int>& matrix, int col, int low, int high, int n, SortStats& stats) {
    if (low < high) {
        int pi = partition(matrix, col, low, high, n, stats);
        quickSort(matrix, col, low, pi - 1, n, stats);
        quickSort(matrix, col, pi + 1, high, n, stats);
    }
}

void sortColumns(std::vector<int>& matrix, int n, SortStats& stats) {
    for (int col = 0; col < n; col++) {
        quickSort(matrix, col, 0, n - 1, n, stats);
    }
}

void printMatrix2(const std::vector<int>& matrix2, int n) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL) + 1);  // Random declaration
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

    SortStats bubbleStats, selectionStats, insertionStats, shellStats, quickStats;

    std::cout << "Bubble Sort:" << std::endl;
    bubbleSortColumn(matrix, n, matrix2, bubbleStats);
    printMatrix2(matrix2, n);
    std::cout << "Comparisons: " << bubbleStats.comparisons << ", Permutations: " << bubbleStats.permutations << std::endl;

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Selection Sort:" << std::endl;
    selectionSortColumn(matrix, n, matrix2, selectionStats);
    printMatrix2(matrix2, n);
    std::cout << "Comparisons: " << selectionStats.comparisons << ", Permutations: " << selectionStats.permutations << std::endl;

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Insertion Sort:" << std::endl;
    insertionSortColumn(matrix, n, matrix2, insertionStats);
    printMatrix2(matrix2, n);
    std::cout << "Comparisons: " << insertionStats.comparisons << ", Permutations: " << insertionStats.permutations << std::endl;

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Shell Sort:" << std::endl;
    shellSortColumn(matrix, n, matrix2, shellStats);
    printMatrix2(matrix2, n);
    std::cout << "Comparisons: " << shellStats.comparisons << ", Permutations: " << shellStats.permutations << std::endl;

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    std::cout << "Quicksort:" << std::endl;
    sortColumns(matrix, n, quickStats);
    printMatrix2(matrix, n);
    std::cout << "Comparisons: " << quickStats.comparisons << ", Permutations: " << quickStats.permutations << std::endl;

    return 0;
}
