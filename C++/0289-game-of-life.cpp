// HoNooD <honood@gmail.com>
// 2024.06.26 08:30

// 289. Game of Life
// https://leetcode.com/problems/game-of-life/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// To solve this problem in-place, we need to keep track of transitions without
// altering the current state before we are done processing the entire board. We
// use two additional states to help with this:
// - `-1`: A cell that was alive but is now dead.
// - `2`: A cell that was dead but is now alive.
class Solution {
public:
  void gameOfLife(vector<vector<int>>& board) {
    if (board.empty() || board[0].empty()) {
      return;
    }

    int m = board.size();
    int n = board[0].size();

    int const directions[8][2] = {
      {-1, -1}, {-1, 0}, {-1, 1},
      {0, -1},           {0, 1},
      {1, -1},  {1, 0},  {1, 1}
    };

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int live_neighbors = 0;
        // check all 8 neighbors
        for (auto const& [di, dj] : directions) {
          int ni = i + di;
          int nj = j + dj;
          if (ni >= 0 && ni < m && nj >= 0 && nj < n && (board[ni][nj] == 1 || board[ni][nj] == -1)) {
            ++live_neighbors;
          }
        }

        // apply the rules of the game
        if (board[i][j] == 0) {
          if (live_neighbors == 3) {
            board[i][j] = 2;
          }
        } else if (board[i][j] == 1) {
          if (live_neighbors < 2 || live_neighbors > 3) {
            board[i][j] = -1;
          }
        }
      }
    }

    // update the board to the next state
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == -1) {
          board[i][j] = 0;
        } else if (board[i][j] == 2) {
          board[i][j] = 1;
        }
      }
    }
  }
};
