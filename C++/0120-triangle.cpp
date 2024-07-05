// HoNooD <honood@gmail.com>
// 2024.07.05 14:55

// 120. Triangle
// https://leetcode.com/problems/triangle/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Top-Down Dynamic Programming solves the problem by iterating from the top to
// the bottom of the triangle while updating a dynamic programming (DP) array
// that keeps track of the minimum path sums for each position as we move
// downward. This approach ensures that we maintain the current state of the
// minimum path sum in a single DP array without the need for additional
// temporary arrays.
//
// Note: intuitive and straightforward
class Solution {
public:
  int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.empty() || triangle[0].empty()) {
      return 0;
    }

    // initialize `dp` with the first row of `triangle`
    vector<int> dp{triangle[0]};
    dp.reserve(triangle[triangle.size() - 1].size());

    // iterate through `triangle` from the second row to the last row
    for (int i = 1; i < triangle.size(); ++i) {
      // update (append) the last element in the current row
      //
      // Note: each row in `triangle` has one more element than the previous
      // row, hence, `dp` for the current row must accommodate one additional
      // element compared to the previous row.
      dp.emplace_back(dp[i - 1] + triangle[i][i]);

      // update the middle elements from right to left to avoid overwriting
      // issues
      for (int j = i - 1; j > 0; --j) {
        dp[j] = std::min(dp[j - 1], dp[j]) + triangle[i][j];
      }

      // update the first element in the current row
      dp[0] += triangle[i][0];
    }

    // the minimum value in `dp` represents the minimum path sum
    return *std::min_element(dp.cbegin(), dp.cend());
  }
};

// Bottom-Up Dynamic Programming:
// 1.	Starting from the second-to-last row, for each number, update it to the
// sum of itself and the minimum of its two adjacent numbers in the row directly
// below.
// 2.	Continue this process upward, and the value at the top of the triangle
// will represent the minimum path sum.
//
// Note: optimal, recommended!
class Solution_2 {
public:
  int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.empty() || triangle[0].empty()) {
      return 0;
    }

    for (int i = triangle.size() - 2; i >= 0; --i) {
      // update each element in the current row
      for (int j = 0; j < triangle[i].size(); ++j) {
        // choose the minimum path sum from the current element to the next row
        triangle[i][j] += std::min(triangle[i + 1][j], triangle[i + 1][j + 1]);
      }
    }

    // the top element now contains the minimum path sum
    return triangle[0][0];
  }
};

// Top-Down Recursive with Memoization approach uses recursion to explore all
// possible paths from the top to the bottom of the triangle. To avoid redundant
// calculations and excessive recursive calls, we use a memoization table to
// store the results of subproblems. This ensures that each subproblem is solved
// only once, and the result is reused when needed.
//
// Note: recursive implementation of the `Solution_2` approach
class Solution_3 {
public:
  int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.empty() || triangle[0].empty()) {
      return 0;
    }

    // memoization table to store minimus path sums for subproblems
    vector<vector<optional<int>>> memo(triangle.size() - 1, vector<optional<int>>(triangle.size() - 1, std::nullopt));
    return impl(triangle, 0, 0, memo);
  }

private:
  int impl(vector<vector<int>> const& triangle, int row, int col, vector<vector<optional<int>>>& memo) {
    // base case: if we reach the bottom row, return the value at (row, col)
    if (row == triangle.size() - 1) {
      return triangle[row][col];
    }

    // check if the result is already computed and stored in the memo table
    if (memo[row][col].has_value()) {
      return memo[row][col].value();
    }

    // recursively compute the minimum path sum for the two possible paths
    int left = impl(triangle, row + 1, col, memo);
    int right = impl(triangle, row + 1, col + 1, memo);

    memo[row][col] = triangle[row][col] + std::min(left, right);
    return memo[row][col].value();
  };
};
