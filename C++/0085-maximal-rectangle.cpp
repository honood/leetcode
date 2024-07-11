// HoNooD <honood@gmail.com>
// 2024.07.12 14:00

// 85. Maximal Rectangle
// https://leetcode.com/problems/maximal-rectangle/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// This problem can be transformed into a series of largest rectangle in
// histogram problems, notably akin to LeetCode 84, "Largest Rectangle in
// Histogram". Each row of the matrix can be viewed as a new base where we
// accumulate height information from the rows above to compute the maximum
// rectangle area.
//
// Reference:
//   84. Largest Rectangle in Histogram
//     - https://leetcode.com/problems/largest-rectangle-in-histogram/description/
//     - See: 0084-largest-rectangle-in-histogram.cpp
//   221. Maximal Square
//     - https://leetcode.com/problems/maximal-square/description/?envType=study-plan-v2&envId=top-interview-150
//     - See: 0221-maximal-square.cpp
//
// Example:
// Consider the matrix:
// ┌───┬───┬───┬───┬───┐
// │ 1 │ 0 │ 1 │ 0 │ 0 │
// ├───┼───┼───┼───┼───┤
// │ 1 │ 0 │ 1 │ 1 │ 1 │
// ├───┼───┼───┼───┼───┤
// │ 1 │ 1 │ 1 │ 1 │ 1 │
// ├───┼───┼───┼───┼───┤
// │ 1 │ 0 │ 0 │ 1 │ 0 │
// └───┴───┴───┴───┴───┘
// 1.	First Row:
//   - Heights: [1, 0, 1, 0, 0]
//   - Largest Rectangle in Histogram: 1
// 2. Second Row:
//   - Heights: [2, 0, 2, 1, 1]
//   - Largest Rectangle in Histogram: 3
// 3. Third Row:
//   - Heights: [3, 1, 3, 2, 2]
//   - Largest Rectangle in Histogram: 6
// 4. Fourth Row:
//   - Heights: [4, 0, 0, 3, 0]
//   - Largest Rectangle in Histogram: 4
// The overall maximum rectangle area is 6.
class Solution {
public:
  int maximalRectangle(vector<vector<char>> const& matrix) {
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

      max_area = std::max(max_area, maximal_rectangle_in_histogram(heights));
    }

    return max_area;
  }

private:
  int maximal_rectangle_in_histogram(vector<int> const& heights) {
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
        max_area = std::max(max_area, width * height);
      }

      stack.emplace(i);
    }

    return max_area;
  }
};
