// HoNooD <honood@gmail.com>
// 2024.06.22 01:05

// $ /opt/homebrew/opt/llvm/bin/clang++ -std=c++20 matrix_traversal.cpp -o matrix_traversal
// $ ./matrix_traversal
//
// $ /opt/homebrew/opt/gcc/bin/g++-14 -std=c++20 matrix_traversal.cpp -o matrix_traversal
// $ ./matrix_traversal

#include <functional>
#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

void bfsRecursiveHelper(queue<pair<int, int>>& q,
                        vector<vector<int>> const& matrix,
                        vector<vector<bool>>& visited,
                        int const directions[4][2],
                        function<void(int const&)> callback) {
  if (q.empty()) {
    return;
  }

  // Note: `q.pop()` invalidates references, so do NOT use:
  // 1. auto const& [x, y] = q.front();
  // 2. auto& [x, y] = q.front();
  auto [x, y] = q.front();
  q.pop();
  callback(matrix[x][y]);

  for (int i = 0; i < 4; ++i) {
    int nx = x + directions[i][0];
    int ny = y + directions[i][1];
    if (nx >= 0 && nx < matrix.size() && ny >= 0 && ny < matrix[0].size() && !visited[nx][ny]) {
      q.emplace(nx, ny);
      visited[nx][ny] = true;
    }
  }

  bfsRecursiveHelper(q, matrix, visited, directions, callback);
}

void bfsRecursive(vector<vector<int>> const& matrix,
                  int startX,
                  int startY,
                  function<void(int const&)> callback) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));

  queue<pair<int, int>> q{};
  q.emplace(startX, startY);
  visited[startX][startY] = true;

  int const directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  bfsRecursiveHelper(q, matrix, visited, directions, callback);
}

void bfsIterative(vector<vector<int>> const& matrix,
                  int startX,
                  int startY,
                  function<void(int const&)> callback) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));

  queue<pair<int, int>> q{};
  q.emplace(startX, startY);
  visited[startX][startY] = true;

  int const directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  while (!q.empty()) {
    // Note: `q.pop()` invalidates references, so do NOT use:
    // 1. auto const& [x, y] = q.front();
    // 2. auto& [x, y] = q.front();
    auto [x, y] = q.front();
    q.pop();
    callback(matrix[x][y]);

    for (int i = 0; i < 4; ++i) {
      int nx = x + directions[i][0];
      int ny = y + directions[i][1];
      if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny]) {
        q.emplace(nx, ny);
        visited[nx][ny] = true;
      }
    }
  }
}

void dfsRecursiveHelper(vector<vector<int>> const& matrix,
                        vector<vector<bool>>& visited,
                        int x,
                        int y,
                        int const directions[4][2],
                        function<void(int const&)> callback) {
  visited[x][y] = true;
  callback(matrix[x][y]);

  for (int i = 0; i < 4; ++i) {
    int nx = x + directions[i][0];
    int ny = y + directions[i][1];
    if (nx >= 0 && nx < matrix.size() && ny >= 0 && ny < matrix[0].size() && !visited[nx][ny]) {
      dfsRecursiveHelper(matrix, visited, nx, ny, directions, callback);
    }
  }
}

void dfsRecursive(vector<vector<int>> const& matrix,
                  int startX,
                  int startY,
                  function<void(int const&)> callback) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));

  int const directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  dfsRecursiveHelper(matrix, visited, startX, startY, directions, callback);
}

void dfsIterative(vector<vector<int>> const& matrix,
                  int startX,
                  int startY,
                  function<void(int const&)> callback) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));

  stack<pair<int, int>> s{};
  s.emplace(startX, startY);
  visited[startX][startY] = true;

  int const directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  while (!s.empty()) {
    // Note: `s.pop()` invalidates references, so do NOT use:
    // 1. auto const& [x, y] = s.top();
    // 2. auto& [x, y] = s.top();
    auto [x, y] = s.top();
    s.pop();
    callback(matrix[x][y]);

    for (int i = 0; i < 4; ++i) {
      int nx = x + directions[i][0];
      int ny = y + directions[i][1];
      if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny]) {
        s.emplace(nx, ny);
        visited[nx][ny] = true;
      }
    }
  }
}

void printMatrix(vector<vector<int>> const& matrix) {
  if (matrix.empty() || matrix[0].empty()) {
    cout << "matrix is empty, nothing to print." << endl;
    return;
  }

  for (auto const& row : matrix) {
    for (auto const& elem : row) {
      cout << setw(3) << elem << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  vector<vector<int>> matrix(6, vector<int>(6));
  int value = 1;
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      matrix[i][j] = value++;
    }
  }

  cout << "Matrix:" << endl;
  printMatrix(matrix);

  auto printCallback = [](const int& val) {
    cout << val << " ";
  };

  cout << "BFS Recursive: ";
  bfsRecursive(matrix, 0, 0, printCallback);
  cout << endl;

  cout << "BFS Iterative: ";
  bfsIterative(matrix, 0, 0, printCallback);
  cout << endl;

  cout << "DFS Recursive: ";
  dfsRecursive(matrix, 0, 0, printCallback);
  cout << endl;

  cout << "DFS Iterative: ";
  dfsIterative(matrix, 0, 0, printCallback);
  cout << endl;

  return 0;
}

// Matrix:
//   1   2   3   4   5   6
//   7   8   9  10  11  12
//  13  14  15  16  17  18
//  19  20  21  22  23  24
//  25  26  27  28  29  30
//  31  32  33  34  35  36
//
// BFS Recursive: 1 7 2 13 8 3 19 14 9 4 25 20 15 10 5 31 26 21 16 11 6 32 27 22 17 12 33 28 23 18 34 29 24 35 30 36
// BFS Iterative: 1 7 2 13 8 3 19 14 9 4 25 20 15 10 5 31 26 21 16 11 6 32 27 22 17 12 33 28 23 18 34 29 24 35 30 36
// DFS Recursive: 1 7 13 19 25 31 32 26 20 14 8 2 3 9 15 21 27 33 34 28 22 16 10 4 5 11 17 23 29 35 36 30 24 18 12 6
// DFS Iterative: 1 2 3 4 5 6 12 18 24 30 36 35 34 33 32 31 25 19 20 21 22 16 15 14 13 26 27 28 29 23 17 11 10 9 8 7
