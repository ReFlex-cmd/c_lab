#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Structure to represent a cell in the grid
struct Cell {
    int x, y; // Cell coordinates
    double f, g, h; // Values for the A* algorithm
    bool obstacle; // Flag for obstacles
    pair<int, int> parent; // Parent cell

    Cell(int x_, int y_) : x(x_), y(y_), f(0), g(0), h(0), obstacle(false) {}
};

// Function to calculate the distance between two cells
double heuristic(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

// Function to find the shortest path using A* algorithm
vector<pair<int, int>> findPath(vector<vector<Cell>>& grid, pair<int, int> start, pair<int, int> end) {
    vector<pair<int, int>> path;
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<>> pq;

    pq.emplace(0, start);
    grid[start.first][start.second].f = 0;

    while (!pq.empty()) {
        pair<int, int> current = pq.top().second;
        pq.pop();

        if (current == end) {
            // Building the path from end to start
            while (current != start) {
                path.push_back(current);
                current = grid[current.first][current.second].parent;
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            break;
        }

        // Possible neighboring cells including diagonals
        vector<pair<int, int>> neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (auto& neighbor : neighbors) {
            int x = current.first + neighbor.first;
            int y = current.second + neighbor.second;

            // Check if the neighbor is within the grid bounds
            if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
                continue;

            // Check if the neighbor is an obstacle
            if (grid[x][y].obstacle)
                continue;

            // If diagonal movement, check if both horizontal and vertical neighbors are not obstacles
            if (abs(neighbor.first) == 1 && abs(neighbor.second) == 1) {
                if (grid[current.first + neighbor.first][current.second].obstacle || grid[current.first][current.second + neighbor.second].obstacle)
                    continue;
            }

            double gNew = grid[current.first][current.second].g + ((abs(neighbor.first) == 1 && abs(neighbor.second) == 1) ? 1.4 : 1.0); // Diagonal movement costs 1.4, others cost 1
            double hNew = heuristic(x, y, end.first, end.second);
            double fNew = gNew + hNew;

            // Check if the neighbor is already open with a lower f value
            if (grid[x][y].f == 0 || grid[x][y].f > fNew) {
                pq.push({fNew, {x, y}});
                grid[x][y].f = fNew;
                grid[x][y].g = gNew;
                grid[x][y].h = hNew;
                grid[x][y].parent = current;
            }
        }
    }

    return path;
}

// Function to calculate the cost of the path
double calculatePathCost(const vector<pair<int, int>>& path) {
    double cost = 0;
    for (int i = 1; i < path.size(); ++i) {
        int dx = path[i].first - path[i - 1].first;
        int dy = path[i].second - path[i - 1].second;
        cost += (abs(dx) == 1 && abs(dy) == 1) ? 1.4 : 1.0; // Diagonal movement costs 1.4, others cost 1
    }
    return cost;
}

// Function to validate input coordinates
bool isValidCoordinate(int x, int y, int gridSize) {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize;
}

int main() {
    int a_x, a_y, b_x, b_y, n;


    // Input coordinates for A and B
    cout << "Set A_x --> ";
    cin >> a_x;

    cout << "Set A_y --> ";
    cin >> a_y;

    cout << "Set B_x --> ";
    cin >> b_x;

    cout << "Set B_y --> ";
    cin >> b_y;

    cout << "Set grid size >10 --> ";
    cin >> n;

    if (n < 10) {
        cout << "Error: Grid size must be greater than 10." << endl;
        return 1; // Exit with error code
    }

    int gridSize = n; // Size of the grid

    // Check if input coordinates are valid
    if (!isValidCoordinate(a_x, a_y, gridSize) || !isValidCoordinate(b_x, b_y, gridSize)) {
        cout << "Error: Invalid coordinates for A or B." << endl;
        return 1; // Exit with error code
    }

    // Creating the grid
    vector<vector<Cell>> grid(gridSize, vector<Cell>(gridSize, Cell(0, 0)));

    // Setting obstacle cells
    grid[2][2].obstacle = true;
    grid[3][3].obstacle = true;
    grid[4][4].obstacle = true;
    grid[5][5].obstacle = true;

    // Check if A or B is set on an obstacle
    if (grid[a_x][a_y].obstacle || grid[b_x][b_y].obstacle) {
        cout << "Error: A or B is set on an obstacle." << endl;
        return 1; // Exit with error code
    }

    pair<int, int> start = {a_x, a_y};
    pair<int, int> end = {b_x, b_y};

    // Finding the shortest path
    vector<pair<int, int>> path = findPath(grid, start, end);

    // Output the grid with path
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (make_pair(i, j) == start)
                cout << "A ";
            else if (make_pair(i, j) == end)
                cout << "B ";
            else if (grid[i][j].obstacle)
                cout << "X ";
            else if (find(path.begin(), path.end(), make_pair(i, j)) != path.end())
                cout << "* ";
            else
                cout << ". ";
        }
        cout << endl;
    }

    // Output the shortest path
    cout << "Shortest Path: ";
    for (auto& p : path) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl;

    // Calculate and output the cost of the path
    cout << "Path Cost: " << calculatePathCost(path) << endl;

    return 0;
}
