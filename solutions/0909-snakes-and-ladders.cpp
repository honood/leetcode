// HoNooD <honood@gmail.com>
// 2024.06.26 11:27

// 909. Snakes and Ladders
// https://leetcode.com/problems/snakes-and-ladders/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int snakesAndLadders(vector<vector<int>>& board) {
    if (board.empty() || board[0].empty()) {
      return -1;
    }

    int n = board.size();
    if (board[0].size() != n) {
      return -1;
    }

    // flatten the board into a 1D array
    vector<int> moves(n * n + 1, -1);
    bool left_to_right = true;
    int idx = 1;
    for (int i = n - 1; i >= 0; --i) {
      if (left_to_right) {
        for (int j = 0; j < n; ++j) {
          moves[idx++] = board[i][j];
        }
      } else {
        for (int j = n - 1; j >= 0; --j) {
          moves[idx++] = board[i][j];
        }
      }

      left_to_right = !left_to_right;
    }

    // BFS to find the shortest path to the end
    queue<pair<int, int>> q{};
    q.emplace(1, 0); // start at 1 with 0 moves
    vector<bool> visited(n * n + 1, false);
    visited[1] = true;
    while (!q.empty()) {
      auto [curr, moves_count] = q.front();
      q.pop();

      if (curr == n * n) {
        return moves_count;
      }

      // try all posible moves
      for (int i = 1; i <= 6; ++i) {
        int next = curr + i;
        if (next > n * n) {
          continue;
        }

        // move to ladder/snake end
        if (moves[next] != -1) {
          next = moves[next];
        }

        if (!visited[next]) {
          visited[next] = true;
          q.emplace(next, moves_count + 1);
        }
      } // for
    } // while

    return -1;
  }
};
