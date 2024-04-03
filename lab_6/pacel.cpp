#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix[i * n + j];
        }
        std::cout << std::endl;
    }
}

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void arrangeOddElements(std::vector<int>& matrix, int n) {
    for (int i = 0; i < n; i++) {
        std::vector<int> oddElements;
        for (int j = 0; j < n; j++) {
            if (matrix[i * n + j] % 2 != 0) {
                oddElements.push_back(matrix[i * n + j]);
            }
        }
        std::sort(oddElements.begin(), oddElements.end());
        int oddIndex = 0;
        for (int j = 0; j < n; j++) {
            if (matrix[i * n + j] % 2 != 0) {
                matrix[i * n + j] = oddElements[oddIndex++];
            }
        }
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

    // Sorting algorithms
    // bubbleSort(matrix);
    // selectionSort(matrix);
    // insertionSort(matrix);
    // shellSort(matrix);
    quickSort(matrix, 0, n * n - 1);

    std::cout << "\nSorted matrix: " << std::endl;
    printMatrix(matrix, n);

    // Arrange odd elements
    arrangeOddElements(matrix, n);

    std::cout << "\nMatrix with odd elements arranged in ascending order: " << std::endl;
    printMatrix(matrix, n);

    return 0;
}
