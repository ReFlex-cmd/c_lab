#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

// Функция для генерации случайного числа в диапазоне [min, max]
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Функция для вывода массива на экран
void printArray(const vector<int>& arr) {
    for (int num : arr) {
         cout << setw(5) << num; // Измените эту строку, установив желаемую ширину поля
    }
    cout << endl;
}

// Функция для пузырьковой сортировки
void bubbleSort(vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swaps++;
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Функция для сортировки методом отбора
void selectionSort(vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swaps++;
        swap(arr[i], arr[minIndex]);
    }
}

// Функция для сортировки вставками
void insertionSort(vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            swaps++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        swaps++;
    }
}

// Функция для сортировки Шелла
void shellSort(vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                comparisons++;
                swaps++;
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
            swaps++;
        }
    }
}

// Функция для быстрой сортировки (Quick Sort)
void quickSort(vector<int>& arr, int low, int high, int& comparisons, int& swaps) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; ++j) {
            comparisons++;
            if (arr[j] < pivot) {
                i++;
                swaps++;
                swap(arr[i], arr[j]);
            }
        }
        swaps++;
        swap(arr[i + 1], arr[high]);
        int partitionIndex = i + 1;

        quickSort(arr, low, partitionIndex - 1, comparisons, swaps);
        quickSort(arr, partitionIndex + 1, high, comparisons, swaps);
    }
}

int main() {
    system("chcp 65001");
    srand(time(nullptr));

    const int M = 5; // Количество строк
    const int N = 5; // Количество элементов в строке

    vector<vector<int>> matrix(M, vector<int>(N));

    // Заполнение матрицы случайными числами
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = random(1, 100);
        }
    }

    cout << "Неупорядоченная матрица:" << endl;
    for (int i = 0; i < M; ++i) {
        printArray(matrix[i]);
    }
    vector<vector<int>> sortedMatrix(M); // Создание новой матрицы для хранения отсортированных строк

    // Сортировка каждой строки матрицы и сохранение результатов
    for (int i = 0; i < M; ++i) {
        vector<int> temp = matrix[i];
        int comparisons = 0, swaps = 0;

        // Вы можете выбрать любую сортировку, здесь я использую пузырьковую сортировку
        bubbleSort(temp, comparisons, swaps);
        
        // Сохранение отсортированной строки в новую матрицу
        sortedMatrix[i] = temp;
    }


    // Сортировка каждой строки матрицы
    for (int i = 0; i < M; ++i) {
        vector<int> temp = matrix[i];
        int comparisons = 0, swaps = 0;

        cout << "\nСортировка строки " << i + 1 << ":" << endl;

        // Пузырьковая сортировка

        vector<int> bubbleSorted = temp;
        bubbleSort(bubbleSorted, comparisons, swaps);
        printArray(bubbleSorted);
        cout << "Пузырьковая сортировка: ";
        cout << "Сравнений: " << comparisons << ", Перестановок: " << swaps << endl;

        // Сортировка методом отбора
        vector<int> selectionSorted = temp;
        comparisons = 0, swaps = 0;
        selectionSort(selectionSorted, comparisons, swaps);
        cout << "Сортировка методом отбора: ";
        cout << "Сравнений: " << comparisons << ", Перестановок: " << swaps << endl;

        // Сортировка вставками
        vector<int> insertionSorted = temp;
        comparisons = 0, swaps = 0;
        insertionSort(insertionSorted, comparisons, swaps);
        cout << "Сортировка вставками: ";
        cout << "Сравнений: " << comparisons << ", Перестановок: " << swaps << endl;

        // Сортировка Шелла
        vector<int> shellSorted = temp;
        comparisons = 0, swaps = 0;
        shellSort(shellSorted, comparisons, swaps);
        cout << "Сортировка Шелла: ";
        cout << "Сравнений: " << comparisons << ", Перестановок: " << swaps << endl;

        // Быстрая сортировка
        vector<int> quickSorted = temp;
        comparisons = 0, swaps = 0;
        quickSort(quickSorted, 0, N - 1, comparisons, swaps);
        cout << "Быстрая сортировка: ";
        cout << "Сравнений: " << comparisons << ", Перестановок: " << swaps << endl;
    }
    cout << "\nИтоговая отсортированная матрица:" << endl;
    for (int i = 0; i < M; ++i) {
        printArray(sortedMatrix[i]);
    }

    

    return 0;
}