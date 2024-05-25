#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <algorithm>
#include "sort_curse.h"

int quickComparisons = 0;
int quickSwaps = 0;

/**
 * @brief Fill a matrix with random values.
 *
 * @param matrix The matrix to fill.
 * @param n The dimension of the matrix (n x n).
 */
void fillMatrix(std::vector<int> &matrix, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i * n + j] = rand() % 100;
        }
    }
}

/**
 * @brief Sorts each column of the matrix using Bubble Sort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 * @param matrix2 The output matrix to store sorted columns.
 */
void bubbleSortColumn(std::vector<int> &matrix, int n, std::vector<int> &matrix2) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    int swaps = 0;
    int comps = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            for (int k = 0; k < n - i - 1; ++k) {
                comps++;
                if (matrix2[k * n + j] > matrix2[(k + 1) * n + j]) {
                    swaps++;
                    std::swap(matrix2[k * n + j], matrix2[(k + 1) * n + j]);
                }
            }
        }
    }
    std::cout << "Comparisons: " << comps << std::endl;
    std::cout << "Swaps: " << swaps << std::endl;
}

/**
 * @brief Sorts each column of the matrix using Selection Sort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 * @param matrix2 The output matrix to store sorted columns.
 */
void selectionSortColumn(std::vector<int> &matrix, int n, std::vector<int> &matrix2) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    int swaps = 0;
    int comps = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            int min_index = i;
            for (int k = i + 1; k < n; ++k) {
                comps++;
                if (matrix2[k * n + j] < matrix2[min_index * n + j]) {
                    min_index = k;
                }
            }
            swaps++;
            std::swap(matrix2[i * n + j], matrix2[min_index * n + j]);
        }
    }
    std::cout << "Comparisons: " << comps << std::endl;
    std::cout << "Swaps: " << swaps << std::endl;
}

/**
 * @brief Sorts each column of the matrix using Insertion Sort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 * @param matrix2 The output matrix to store sorted columns.
 */
void insertionSortColumn(std::vector<int> &matrix, int n, std::vector<int> &matrix2) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    int swaps = 0;
    int comps = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n; ++i) {
            int key = matrix2[i * n + j];
            int k = i - 1;
            while (k >= 0 && matrix2[k * n + j] > key) {
                comps++;
                swaps++;
                matrix2[(k + 1) * n + j] = matrix2[k * n + j];
                --k;
            }
            matrix2[(k + 1) * n + j] = key;
            swaps++;
        }
    }
    std::cout << "Comparisons: " << comps << std::endl;
    std::cout << "Swaps: " << swaps << std::endl;
}

/**
 * @brief Sorts each column of the matrix using Shell Sort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 * @param matrix2 The output matrix to store sorted columns.
 */
void shellSortColumn(std::vector<int> &matrix, int n, std::vector<int> &matrix2) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    int swaps = 0;
    int comps = 0;
    for (int j = 0; j < n; ++j) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                int temp = matrix2[i * n + j];
                int k;
                for (k = i; k >= gap && matrix2[(k - gap) * n + j] > temp; k -= gap) {
                    comps++;
                    swaps++;
                    matrix2[k * n + j] = matrix2[(k - gap) * n + j];
                }
                matrix2[k * n + j] = temp;
                swaps++;
            }
        }
    }
    std::cout << "Comparisons: " << comps << std::endl;
    std::cout << "Swaps: " << swaps << std::endl;
}

/**
 * @brief Partitions a column of the matrix for Quicksort.
 *
 * @param matrix The input matrix.
 * @param col The column to partition.
 * @param low The starting index of the partition.
 * @param high The ending index of the partition.
 * @param n The dimension of the matrix (n x n).
 * @return int The partition index.
 */
int partition(std::vector<int> &matrix, int col, int low, int high, int n) {
    int pivot = matrix[high * n + col];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        quickComparisons++;
        if (matrix[j * n + col] <= pivot) {
            i++;
            quickSwaps++;
            std::swap(matrix[i * n + col], matrix[j * n + col]);
        }
    }
    quickSwaps++;
    std::swap(matrix[(i + 1) * n + col], matrix[high * n + col]);
    return i + 1;
}

/**
 * @brief Performs Quicksort on a column of the matrix.
 *
 * @param matrix The input matrix.
 * @param col The column to sort.
 * @param low The starting index for the sort.
 * @param high The ending index for the sort.
 * @param n The dimension of the matrix (n x n).
 */
void quickSort(std::vector<int> &matrix, int col, int low, int high, int n) {
    if (low < high) {
        int pi = partition(matrix, col, low, high, n);
        quickSort(matrix, col, low, pi - 1, n);
        quickSort(matrix, col, pi + 1, high, n);
    }
}

/**
 * @brief Sorts each column of the matrix using Quicksort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 */
void sortColumns(std::vector<int> &matrix, int n) {
    for (int col = 0; col < n; col++) {
        quickSort(matrix, col, 0, n - 1, n);
    }
}

/**
 * @brief The main function to test different sorting algorithms on matrix columns.
 *
 * @return int Returns 0 on success.
 */
int main() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    GetConsoleScreenBufferInfo(h, &start_attribute);

    int n = 1500;

    for (int i = 1; i <= 7; i++) {
        n *= i;
        std::cout << n << std::endl;
        std::vector<int> matrix(n * n);
        std::vector<int> matrix2(n * n);

        fillMatrix(matrix, n);

        std::cout << "Bubble Sort:" << std::endl;
        bubbleSortColumn(matrix, n, matrix2);

        std::cout << "Selection Sort:" << std::endl;
        selectionSortColumn(matrix, n, matrix2);

        std::cout << "Insertion Sort:" << std::endl;
        insertionSortColumn(matrix, n, matrix2);

        std::cout << "Shell Sort:" << std::endl;
        shellSortColumn(matrix, n, matrix2);

        std::cout << "Quicksort:" << std::endl;
        sortColumns(matrix, n);

        std::cout << "Comparisons: " << quickComparisons << std::endl;
        std::cout << "Swaps: " << quickSwaps << std::endl;
    }

    return 0;
}
