#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Global counters for comparisons, swaps, and permutations
struct SortStats {
    int comparisons;
    int swaps;
};

// Функция для печати матрицы
void printMatrix(const vector<vector<int> >& matrix) {
    for (const auto& row : matrix) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

// Функция для сортировки нечетных элементов строки методом пузырька
void bubbleSort(vector<int>& row) {
    SortStats stats = {0, 0};
    int n = row.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            stats.comparisons++;
            if (row[j] % 2 != 0 && row[j + 1] % 2 != 0 && row[j] > row[j + 1]) {
                swap(row[j], row[j + 1]);
                stats.swaps++;
            }
        }
    }
}

// Функция для сортировки нечетных элементов строки методом отбора
void selectionSort(vector<int>& row) {
    SortStats stats = {0, 0};
    int n = row.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            stats.comparisons++;
            if (row[j] % 2 != 0 && row[j] < row[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(row[i], row[minIndex]);
            stats.swaps++;
        }
    }
}

// Функция для сортировки нечетных элементов строки методом вставки
void insertionSort(vector<int>& row) {
    SortStats stats = {0, 0};
    int n = row.size();
    for (int i = 1; i < n; ++i) {
        int key = row[i];
        int j = i - 1;
        while (j >= 0 && row[j] % 2 != 0 && row[j] > key) {
            stats.comparisons++;
            row[j + 1] = row[j];
            j = j - 1;
        }
        row[j + 1] = key;
        stats.swaps++;
    }
}

// Функция для сортировки нечетных элементов строки методом Шелла
void shellSort(vector<int>& row) {
    SortStats stats = {0, 0};
    int n = row.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = row[i];
            int j;
            for (j = i; j >= gap && row[j - gap] % 2 != 0 && row[j - gap] > temp; j -= gap) {
                stats.comparisons++;

                row[j] = row[j - gap];
            }
            row[j] = temp;
            stats.swaps++;
        }
    }
}

// Функция быстрой сортировки для нечетных элементов строки
void quickSort(vector<int>& row, int low, int high) {
    SortStats stats = {0, 0};
    if (low < high) {
        int pivot = row[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; ++j) {
            if (row[j] % 2 != 0 && row[j] < pivot) {
                stats.comparisons++;
                ++i;
                swap(row[i], row[j]);
                stats.swaps++;
            }
        }
        swap(row[i + 1], row[high]);
        int partitionIndex = i + 1;

        quickSort(row, low, partitionIndex - 1);
        quickSort(row, partitionIndex + 1, high);
    }
}

// Функция для генерации случайного числа в диапазоне [min, max]
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}
int main() {
    int rows = 3;
    int cols = 5;

    // Создаем вектор векторов (матрицу)
    vector<vector<int> > matrix(rows, vector<int>(cols));

    // Инициализируем генератор случайных чисел
    srand(time(0));

    // Заполняем матрицу случайными числами
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = random(1, 100); // Генерируем случайное число от 1 до 100
        }
    }

    vector<vector<int> >& matrix_ref = matrix;


    cout << "Unsorted Matrix:" << endl;
    printMatrix(matrix);

    cout << "\nSorted Matrix:" << endl;
    vector<vector<int> > sortedMatrix = matrix;
    std::cout << "Bubble Sort:" << std::endl;
    SortStats bubbleStats = bubbleSortColumn(matrix, n, matrix2);
    SortStats selectionStats = selectionSortColumn(matrix, n, matrix2);
    std::cout << "Bubble Sort Stats:\nComparisons: " << bubbleStats.comparisons << "\nSwaps: " << bubbleStats.swaps << std::endl;
    std::cout << "Selection Sort Stats:\nComparisons: " << selectionStats.comparisons << "\nSwaps: " << selectionStats.swaps << std::endl;

    printMatrix(sortedMatrix);

    return 0;
}
