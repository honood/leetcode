// HoNooD <honood@gmail.com>
// 2024.06.25 09:30

// 54. Spiral Matrix
// https://leetcode.com/problems/spiral-matrix/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Great!
class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return {};
    }

    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> res{};
    int top = 0;
    int bottom = m - 1;
    int left = 0;
    int right = n - 1;
    while (top <= bottom && left <= right) {
      // traverse from left to right on the current top row
      for (int col = left; col <= right; ++col) {
        res.emplace_back(matrix[top][col]);
      }
      // move top boundary down
      ++top;

      // traverse from top to bottom on the current right column
      for (int row = top; row <= bottom; ++row) {
        res.emplace_back(matrix[row][right]);
      }
      // move right boundary left
      --right;

      if (top <= bottom) {
        // traverse from right to left on the current bottom row
        for (int col = right; col >= left; --col) {
          res.emplace_back(matrix[bottom][col]);
        }
        // move bottom boundary up
        --bottom;
      }

      if (left <= right) {
        // traverse from bottom to top on the current left column
        for (int row = bottom; row >= top; --row) {
          res.emplace_back(matrix[row][left]);
        }
        // move left boundary right
        ++left;
      }
    }

    return res;
  }
};

// Not Recommended due to several drawbacks:
// 1. High Space Complexity: Uses an extra `visited` matrix, leading to O(m * n)
// space complexity. This can be significant for large matrices.
// 2. Inefficient Boundary Checks: Each movement requires checking bounds and
// visited status, resulting in repetitive and unnecessary checks.
// 3. Redundant Direction Handling: Repeats similar logic for each direction
// (right, down, left, up), making the code verbose and harder to maintain.
// 4. Complex Direction Management: Manages four direction changes with repeated
// boundary conditions, which is error-prone and less elegant than a unified
// approach.
class Solution_2 {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return {};
    }

    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> res{};
    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));

    enum : int { right, down, left, up };
    int direction = right;
    int i = 0;
    int j = 0;
    while (res.size() < m * n) {
      res.emplace_back(matrix[i][j]);
      visited[i][j] = true;

      switch (direction) {
        case right: {
          ++j;
          if (j == n || visited[i][j]) {
            --j;
            ++i;
            direction = down;
          }
          break;
        }
        case down: {
          ++i;
          if (i == m || visited[i][j]) {
            --i;
            --j;
            direction = left;
          }
          break;
        }
        case left: {
          --j;
          if (j == -1 || visited[i][j]) {
            ++j;
            --i;
            direction = up;
          }
          break;
        }
        case up: {
          --i;
          if (i == -1 || visited[i][j]) {
            ++i;
            ++j;
            direction = right;
          }
          break;
        }
        default:
          assert(false);
          break;
      }
    }

    return res;
  }
};
