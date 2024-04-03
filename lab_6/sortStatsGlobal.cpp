#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include <algorithm>

// Function to fill the matrix with random numbers
void fillMatrix(std::vector<int>& matrix, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i * n + j] = rand() % 100;
        }
    }
}

// Function to print the matrix
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

// Function to perform bubble sort on a column of the matrix
void bubbleSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2, int& comparisons, int& permutations) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            for (int k = 0; k < n - i - 1; ++k) {
                comparisons++;
                if (matrix2[k * n + j] > matrix2[(k + 1) * n + j]) {
                    permutations++;
                    std::swap(matrix2[k * n + j], matrix2[(k + 1) * n + j]);
                }
            }
        }
    }
}

// Function to perform selection sort on a column of the matrix
void selectionSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2, int& comparisons, int& permutations) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            int min_index = i;
            for (int k = i + 1; k < n; ++k) {
                comparisons++;
                if (matrix2[k * n + j] < matrix2[min_index * n + j]) {
                    min_index = k;
                }
            }
            if (min_index != i) {
                permutations++;
                std::swap(matrix2[i * n + j], matrix2[min_index * n + j]);
            }
        }
    }
}

// Function to perform insertion sort on a column of the matrix
void insertionSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2, int& comparisons, int& permutations) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n; ++i) {
            int key = matrix2[i * n + j];
            int k = i - 1;
            while (k >= 0 && matrix2[k * n + j] > key) {
                comparisons++;
                matrix2[(k + 1) * n + j] = matrix2[k * n + j];
                k--;
            }
            matrix2[(k + 1) * n + j] = key;
            if (k != i - 1) {
                permutations++;
            }
        }
    }
}

// Function to perform shell sort on a column of the matrix
void shellSortColumn(std::vector<int>& matrix, int n, std::vector<int>& matrix2, int& comparisons, int& permutations) {
    std::copy(matrix.begin(), matrix.end(), matrix2.begin());
    for (int j = 0; j < n; ++j) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                int temp = matrix2[i * n + j];
                int k;
                for (k = i; k >= gap && matrix2[(k - gap) * n + j] > temp; k -= gap) {
                    comparisons++;
                    matrix2[k * n + j] = matrix2[(k - gap) * n + j];
                }
                matrix2[k * n + j] = temp;
                if (k != i) {
                    permutations++;
                }
            }
        }
    }
}

// Function to partition the matrix for quick sort
int partition(std::vector<int>& matrix, int col, int low, int high, int n, int& comparisons, int& permutations) {
    int pivot = matrix[high * n + col];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (matrix[j * n + col] <= pivot) {
            i++;
            permutations++;
            std::swap(matrix[i * n + col], matrix[j * n + col]);
        }
    }
    permutations++;
    std::swap(matrix[(i + 1) * n + col], matrix[high * n + col]);
    return i + 1;
}

// Function to perform quick sort on a column of the matrix
void quickSort(std::vector<int>& matrix, int col, int low, int high, int n, int& comparisons, int& permutations) {
    if (low < high) {
        int pi = partition(matrix, col, low, high, n, comparisons, permutations);
        quickSort(matrix, col, low, pi - 1, n, comparisons, permutations);
        quickSort(matrix, col, pi + 1, high, n, comparisons, permutations);
    }
}

// Function to sort all columns of the matrix using quick sort
void sortColumns(std::vector<int>& matrix, int n, int& comparisons, int& permutations) {
    for (int col = 0; col < n; col++) {
        quickSort(matrix, col, 0, n - 1, n, comparisons, permutations);
    }
}

// Function to print the matrix after sorting
void printMatrix2(const std::vector<int>& matrix2, int n) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL)+1);
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

    int comparisons = 0;
    int permutations = 0;

    std::cout << "Bubble Sort:" << std::endl;
    bubbleSortColumn(matrix, n, matrix2, comparisons, permutations);
    printMatrix2(matrix2, n);
    std::cout << "Comparisons: " << comparisons << ", Permutations: " << permutations << std::endl;

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    comparisons = 0;
    permutations = 0;

    std::cout << "Selection Sort:" << std::endl;
    selectionSortColumn(matrix, n, matrix2, comparisons, permutations);
    printMatrix2(matrix2, n);
    std::cout << "Comparisons: " << comparisons << ", Permutations: " << permutations << std::endl;

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    comparisons = 0;
    permutations = 0;

    std::cout << "Insertion Sort:" << std::endl;
    insertionSortColumn(matrix, n, matrix2, comparisons, permutations);
    printMatrix2(matrix2, n);
    std::cout << "Comparisons: " << comparisons << ", Permutations: " << permutations << std::endl;

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    comparisons = 0;
    permutations = 0;

    std::cout << "Shell Sort:" << std::endl;
    shellSortColumn(matrix, n, matrix2, comparisons, permutations);
    printMatrix2(matrix2, n);
    std::cout << "Comparisons: " << comparisons << ", Permutations: " << permutations << std::endl;

    SetConsoleTextAttribute(h, start_attribute.wAttributes);

    comparisons = 0;
    permutations = 0;

    std::cout << "Quicksort:" << std::endl;
    sortColumns(matrix, n, comparisons, permutations);
    printMatrix2(matrix, n);
    std::cout << "Comparisons: " << comparisons << ", Permutations: " << permutations << std::endl;

    return 0;
}
