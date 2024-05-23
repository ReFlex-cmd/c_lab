#ifndef C_LAB_SORT_CURSE_H
#define C_LAB_SORT_CURSE_H

#include <vector>

// Global variables for quicksort comparisons and swaps
extern int quickComparisons;
extern int quickSwaps;

/**
 * @brief Fill a matrix with random values.
 *
 * @param matrix The matrix to fill.
 * @param n The dimension of the matrix (n x n).
 */
void fillMatrix(std::vector<int> &matrix, int n);

/**
 * @brief Sorts each column of the matrix using Bubble Sort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 * @param matrix2 The output matrix to store sorted columns.
 */
void bubbleSortColumn(std::vector<int> &matrix, int n, std::vector<int> &matrix2);

/**
 * @brief Sorts each column of the matrix using Selection Sort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 * @param matrix2 The output matrix to store sorted columns.
 */
void selectionSortColumn(std::vector<int> &matrix, int n, std::vector<int> &matrix2);

/**
 * @brief Sorts each column of the matrix using Insertion Sort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 * @param matrix2 The output matrix to store sorted columns.
 */
void insertionSortColumn(std::vector<int> &matrix, int n, std::vector<int> &matrix2);

/**
 * @brief Sorts each column of the matrix using Shell Sort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 * @param matrix2 The output matrix to store sorted columns.
 */
void shellSortColumn(std::vector<int> &matrix, int n, std::vector<int> &matrix2);

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
int partition(std::vector<int> &matrix, int col, int low, int high, int n);

/**
 * @brief Performs Quicksort on a column of the matrix.
 *
 * @param matrix The input matrix.
 * @param col The column to sort.
 * @param low The starting index for the sort.
 * @param high The ending index for the sort.
 * @param n The dimension of the matrix (n x n).
 */
void quickSort(std::vector<int> &matrix, int col, int low, int high, int n);

/**
 * @brief Sorts each column of the matrix using Quicksort.
 *
 * @param matrix The input matrix.
 * @param n The dimension of the matrix (n x n).
 */
void sortColumns(std::vector<int> &matrix, int n);

#endif //C_LAB_SORT_CURSE_H
