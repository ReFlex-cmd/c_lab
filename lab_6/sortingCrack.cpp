#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

vector<vector<int>> createMatrix(int n) {
    vector<vector<int>> arr(n, vector<int>(n));

    // Seed the random number generator
    srand(time(nullptr));

    // Fill the array with random numbers
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            arr[i][j] = random(1, 99); // Generating random numbers between 1 and 100
        }
    }
    return arr;
}

// Function to print the 2D array
void printArray(const vector<vector<int>>& arr) {
    for (const auto& row : arr) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the dimension of the square array: ";
    cin >> n;

    if (n <= 1) {
        cout << "Invalid dimension!" << endl;
        return 1;
    }

    vector<vector<int>> randomMatrix = createMatrix(n);

    cout << "Random " << n << "x" << n << " Matrix:" << endl;
    printArray(randomMatrix);

    return 0;
}
