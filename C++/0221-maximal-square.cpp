// HoNooD <honood@gmail.com>
// 2024.07.11 08:30

// 221. Maximal Square
// https://leetcode.com/problems/maximal-square/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Dynamic Programming (DP)
class Solution {
public:
  int maximalSquare(vector<vector<char>> const& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return 0;
    }

    int m = matrix.size();
    int n = matrix[0].size();

    // create a 2D DP array initialized to 0
    //
    // Note: `dp[i][j]` represents the side length of the largest square whose
    // bottom-right corner is at cell `(i, j)`
    vector<vector<int>> dp(m, vector<int>(n, 0));

    int max_side = 0;

    // fill the DP array
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == '1') {
          if (i == 0 || j == 0) { // handle boundary conditions separately
            dp[i][j] = 1;
          } else {
            // Understanding the DP Transition Formula
            //
            // The idea is to determine the side length of the largest square
            // that ends at position `(i, j)` if `matrix[i][j]` is `1`. The
            // largest square that ends at `(i, j)` is influenced by the squares
            // that end at the positions directly above it, directly to the left
            // of it, and diagonally above-left to it.
            dp[i][j] = std::min({
                         dp[i - 1][j],    // square ending directly above
                         dp[i][j - 1],    // square ending directly to the left
                         dp[i - 1][j - 1] // square ending diagonally above-left
                       }) + 1;
          }

          max_side = std::max(max_side, dp[i][j]);
        }
      }
    }

    return max_side * max_side;
  }

  int maximal_square_with_space_opt(vector<vector<char>> const& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return 0;
    }

    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> dp(n + 1, 0);
    int max_side = 0;
    // store the value of `dp[j-1]` from the previous row
    int prev = 0;

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        // current `dp[j]` before updating
        int temp = dp[j];

        if (matrix[i - 1][j - 1] == '1') {
          dp[j] = std::min({
                    prev,      // square ending diagonally above-left
                    dp[j - 1], // square ending directly to the left
                    dp[j]      // square ending directly above
                  }) + 1;
          max_side = std::max(max_side, dp[j]);
        } else {
          dp[j] = 0;
        }

        prev = temp;
      }
    }

    return max_side * max_side;
  }
};

// The Histogram-Based Approach transforms each row of the matrix into a
// histogram and then calculates the largest square area that can be formed in
// that histogram. This approach is typically used to find the largest rectangle
// area but can be adapted to find the largest square area.
//
// 1. Building the Histogram:
//   - For each row in the matrix, construct a histogram where the height of
//     each bar represents the number of consecutive '1's up to that row.
//   - Essentially, treat each row as the base and calculate the heights of
//     histogram bars from the current row upwards.
// 2. Calculating Maximum Rectangle Area:
//   - Use a stack to efficiently calculate the largest rectangle area in the
//     histogram.
//   - While calculating the rectangle area, ensure the rectangle can also form
//     a square by comparing the height and width.
//
// Note: Compare the following matrix and histogram (or use a professional
// graphing tool to visualize them), and you might understand how the
// Histogram-Based Approach works:
// ┌───┬───┬───┬───┬───┐
// │ 1 │ 0 │ 1 │ 0 │ 0 │
// ├───┼───┼───┼───┼───┤
// │ 1 │ 0 │ 1 │ 1 │ 1 │
// ├───┼───┼───┼───┼───┤
// │ 1 │ 1 │ 1 │ 1 │ 1 │
// ├───┼───┼───┼───┼───┤
// │ 1 │ 0 │ 0 │ 1 │ 0 │
// └───┴───┴───┴───┴───┘
//          6
//       5  ██
//       ██ ██
//       ██ ██    3
// 2     ██ ██ 2  ██
// ██ 1  ██ ██ ██ ██
// ██ ██ ██ ██ ██ ██
class Solution_2 {
public:
  int maximalSquare(vector<vector<char>> const& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return 0;
    }

    int m = matrix.size();
    int n = matrix[0].size();

    // create a height array initialized to 0
    vector<int> heights(n, 0);
    int max_area = 0;

    // fill the height array and calculate max area
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == '1') {
          heights[j] += 1;
        } else {
          heights[j] = 0;
        }
      }

      max_area = std::max(max_area, maximal_square_in_histogram(heights));
    }

    return max_area;
  }

private:
  // Reference:
  //   84. Largest Rectangle in Histogram
  //     - https://leetcode.com/problems/largest-rectangle-in-histogram/description/
  //     - See: 0084-largest-rectangle-in-histogram.cpp
  int maximal_square_in_histogram(vector<int> const& heights) {
    // Define a stack to store indices of the histogram bars
    //
    // This will be a monotonic increasing stack, meaning the heights of the
    // bars at the indices in the stack will be in non-decreasing order.
    //
    // Note: A monotonic stack is a stack where the elements are ordered in a
    // specific non-decreasing (or non-increasing) manner. This structure helps
    // efficiently solve problems involving ranges and boundaries in an array.
    stack<int> stack{};
    int max_area = 0;

    int n = heights.size();
    for (int i = 0; i <= n; ++i) {
      // Assigns `0` to `curr_height` when the loop index `i` reaches `n` (the
      // end of the `heights` array). This acts as a sentinel value to ensure
      // that any remaining elements in the `stack` are processed correctly. It
      // flushes out the `stack` at the end of the iteration, ensuring all
      // potential rectangles formed by the histogram bars are considered.
      //
      // This approach removes the need for adding and removing an extra `0`
      // to/from the `heights` array.
      int curr_height = i == n ? 0 : heights[i];
      while (!stack.empty() && curr_height < heights[stack.top()]) {
        int height = heights[stack.top()];
        stack.pop();

        int width = stack.empty() ? i : i - stack.top() - 1;
        // ensure the area can form a square
        int side = std::min(height, width);
        max_area = std::max(max_area, side * side);
      }

      stack.emplace(i);
    }

    return max_area;
  }
};
