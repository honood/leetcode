// HoNooD <honood@gmail.com>
// 2025.03.13 00:01

// 1926. Nearest Exit from Entrance in Maze
// https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // Constraints:
  //   - maze.length == m
  //   - maze[i].length == n
  //   - maze[i][j] is either '.' or '+'
  //   - entrance.length == 2
  int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
    return nearest_exit_v1(maze, entrance);
  }

private:
  // BFS for finding the shortest path in unweighted graphs
  //
  // - Time complexity: O(m*n) where m and n are the dimensions of the maze
  // - Space complexity: O(m*n) for the queue and visited array
  int nearest_exit_v1(vector<vector<char>>& maze, vector<int> const& entrance) {
    // clang-format off
    // Four possible directions: up, left, down, right
    vector<pair<int, int>> const directions{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    // clang-format on

    int m = maze.size();
    int n = maze[0].size();
    auto in_bounds = [m, n](int row, int col) {
      return row >= 0 && row < m && col >= 0 && col < n;
    };
    auto on_bounds = [m, n](int row, int col) {
      return row == 0 || row == m - 1 || col == 0 || col == n - 1;
    };

    std::queue<tuple<int, int, int>> queue{{{entrance[0], entrance[1], 0}}};
    maze[entrance[0]][entrance[1]] = '+'; // Mark entrance as visited

    while (!queue.empty()) {
      auto [row, col, steps] = queue.front();
      queue.pop();

      for (auto [drow, dcol] : directions) {
        int new_row = row + drow;
        int new_col = col + dcol;
        if (!in_bounds(new_row, new_col) || maze[new_row][new_col] == '+') {
          continue;
        }

        maze[new_row][new_col] = '+'; // Mark as visited

        if (on_bounds(new_row, new_col)) {
          return steps + 1;
        }

        queue.emplace(new_row, new_col, steps + 1);
      }
    }

    return -1;
  }
};
