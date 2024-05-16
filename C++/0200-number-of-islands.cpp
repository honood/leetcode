// HoNooD
// 2024.05.15 16:58

// 200. Number of Islands
// https://leetcode.com/problems/number-of-islands/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) {
      return 0;
    }

    int res = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] == '1') {
          ++res;
          dfs(grid, i, j);
        }
      }
    }

    return res;
  }

private:
  void dfs(vector<vector<char>>& grid, int row, int col) {
    if (grid.empty()) {
      return;
    }

    int rows = grid.size();
    int cols = grid[0].size();
    if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] != '1') {
      return;
    }

    // Mark the current land as visited
    grid[row][col] = 'v'; // `v` looks like "check mark".

    // Continue depth-first search in all four directions
    dfs(grid, row - 1, col); // top
    dfs(grid, row, col + 1); // right
    dfs(grid, row + 1, col); // bottom
    dfs(grid, row, col - 1); // left
  }
};

class Solution_2 {
public:
  int numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) {
      return 0;
    }

    int res = 0;
    vector<pair<int, int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] == '1') {
          ++res;
          bfs(grid, i, j, directions);
        }
      }
    }

    return res;
  }

private:
  void bfs(vector<vector<char>>& grid, int row, int col, vector<pair<int, int>>& directions) {
    if (grid.empty()) {
      return;
    }

    int rows = grid.size();
    int cols = grid[0].size();
    const int visitedLand = '0';

    // Mark the current land as visited
    grid[row][col] = visitedLand;

    queue<pair<int, int>> q{};
    q.push({row, col});
    while (!q.empty()) {
      pair<int, int> loc = q.front();
      q.pop();

      // Continue breadth-first search in all four directions
      for (auto const& dir : directions) {
        int r = loc.first + dir.first;
        int c = loc.second + dir.second;
        if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == '1') {
          q.push({r, c});
          grid[r][c] = visitedLand;
        }
      }
    }
  }
};
