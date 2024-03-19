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

void sortColumn(std::vector<int>& matrix, int column, int n) {
    std::vector<int> columnData;
    for (int i = 0; i < n; ++i) {
        columnData.push_back(matrix[i * n + column]);
    }
    std::sort(columnData.begin(), columnData.end());
    for (int i = 0; i < n; ++i) {
        matrix[i * n + column] = columnData[i];
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

    // Sorting each column
    for (int j = 0; j < n; ++j) {
        sortColumn(matrix, j, n);
    }

    std::cout << "\nChanged matrix: " << std::endl;
    printMatrix(matrix, n);

    return 0;
}
