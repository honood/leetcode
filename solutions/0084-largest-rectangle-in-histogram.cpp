// HoNooD <honood@gmail.com>
// 2024.07.12 00:06

// 84. Largest Rectangle in Histogram
// https://leetcode.com/problems/largest-rectangle-in-histogram/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int largestRectangleArea(vector<int> const& heights) {
    return largest_rectangle_area_v3(heights);
  }

private:
  // Brute Force
  //
  // time complexity: O(n^2)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int largest_rectangle_area_v1(vector<int> const& heights) {
    if (heights.empty()) {
      return 0;
    }

    int max_area = 0;

    int n = heights.size();
    for (int i = 0; i < n; ++i) {
      int height = heights[i];

      int left_smaller = i - 1;
      while (left_smaller >= 0 && heights[left_smaller] >= height) {
        --left_smaller;
      }
      int left_bound = left_smaller + 1;

      int right_smaller = i + 1;
      while (right_smaller < n && heights[right_smaller] >= height) {
        ++right_smaller;
      }
      int right_bound = right_smaller - 1;

      int width = right_bound - left_bound + 1;
      max_area = std::max(max_area, width * height);
    }

    return max_area;
  }

  // Solves the problem using a monotonic stack
  //
  // time complexity: O(n), as each bar is pushed and popped from the stack at
  // most once.
  int largest_rectangle_area_v2(vector<int> const& heights) {
    if (heights.empty()) {
      return 0;
    }

    stack<int> stack{};

    int n = heights.size();
    // Initialize `right_smaller` with `n` to indicate no smaller element to the
    // right by default.
    //
    // Initialize `left_smaller` with `-1` to indicate no smaller element to the
    // left by default.
    //
    // These default values simplify area calculation, as using different values
    // would require additional logic. For example, if `right_smaller` is
    // initialized to `INT_MAX`, and `left_smaller` to `INT_MIN`, extra checks
    // would be needed:
    //
    // int width = (right_smaller[i] == INT_MAX ? n : right_smaller[i])
    //             - (left_smaller[i] == INT_MIN ? -1 : left_smaller[i]) - 1;
    vector<int> right_smaller(n, n);
    vector<int> left_smaller(n, -1);

    for (int i = 0; i < n; ++i) {
      while (!stack.empty() && heights[stack.top()] > heights[i]) {
        right_smaller[stack.top()] = i;
        stack.pop();
      }

      stack.emplace(i);
    }

    // clear the stack for reuse
    while (!stack.empty()) {
      stack.pop();
    }

    for (int i = 0; i < n; ++i) {
      while (!stack.empty() && heights[stack.top()] > heights[i]) {
        stack.pop();
      }
      if (!stack.empty()) {
        left_smaller[i] = stack.top();
      }

      stack.emplace(i);
    }

    int max_area = 0;
    for (int i = 0; i < n; ++i) {
      int height = heights[i];
      // Note:
      //   right_smaller[i] - left_smaller[i] - 1
      // = (right_smaller[i] - 1) - (left_smaller[i] + 1) + 1
      // = right_bound - left_bound + 1
      int width = right_smaller[i] - left_smaller[i] - 1;
      max_area = std::max(max_area, width * height);
    }

    return max_area;
  }

  // Solves the problem using a monotonic stack
  //
  // time complexity: O(n), as each bar is pushed and popped from the stack at
  // most once.
  //
  // Reference:
  //   221. Maximal Square
  //     - https://leetcode.com/problems/maximal-square/description/?envType=study-plan-v2&envId=top-interview-150
  //     - See: 0221-maximal-square.cpp
  int largest_rectangle_area_v3(vector<int> const& heights) {
    if (heights.empty()) {
      return 0;
    }

    stack<int> stack{};
    int max_area = 0;

    int n = heights.size();
    for (int i = 0; i <= n; ++i) {
      // use a height of `0` for the end of the array to process remaining bars
      // in the `stack`
      int curr_height = i == n ? 0 : heights[i];
      while (!stack.empty() && curr_height < heights[stack.top()]) {
        // Note: The right smaller of the top element is `i`, and the left
        // smaller of the top element is the element below it in the stack.
        int height = heights[stack.top()];
        stack.pop();

        // Note:
        // 1. When `stack` is empty, the right smaller is `i` and the left
        //    smaller can be interpreted as:
        //    - Not existing:
        //      int width = (i - 1) - 0 + 1 = i
        //    - Or as `-1`:
        //      int width = i - (-1) - 1 = (i - 1) - (-1 + 1) + 1 = i
        // 2. i - stack.top() - 1 = (i - 1) - (stack.top() + 1) + 1
        int width = stack.empty() ? i : i - stack.top() - 1;
        max_area = std::max(max_area, width * height);
      }

      stack.emplace(i);
    }

    return max_area;
  }
};

// Brute Force
//
// time complexity: O(n^2)
//
// Note: result in Time Limit Exceeded (TLE)
class Solution_2 {
public:
  int largestRectangleArea(vector<int> const& heights) {
    if (heights.empty()) {
      return 0;
    }

    int max_area = 0;

    int n = heights.size();
    for (int left_bound = 0; left_bound < n; ++left_bound) {
      int min_height = heights[left_bound];
      for (int right_bound = left_bound; right_bound < n; ++right_bound) {
        min_height = std::min(min_height, heights[right_bound]);
        int width = right_bound - left_bound + 1;
        max_area = std::max(max_area, width * min_height);
      }
    }

    return max_area;
  }
};

// Divide and Conquer
// https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm
//
// time complexity:
//   - worst case: O(n^2)
//   - average case: O(n*log(n))
//
// Note: result in Time Limit Exceeded (TLE)
class Solution_3 {
public:
  int largestRectangleArea(vector<int> const& heights) {
    if (heights.empty()) {
      return 0;
    }

    return divide_and_conquer(heights, 0, heights.size() -1);
  }

private:
  int divide_and_conquer(vector<int> const& heights, int left, int right) {
    if (left > right) {
      return 0;
    }

    int min_height_index = left;
    for (int i = left; i <= right; ++i) {
      if (heights[i] < heights[min_height_index]) {
        min_height_index = i;
      }
    }

    int left_area = divide_and_conquer(heights, left, min_height_index - 1);
    int right_area = divide_and_conquer(heights, min_height_index + 1, right);
    int cross_area = (right - left + 1) * heights[min_height_index];

    return std::max({left_area, right_area, cross_area});
  }
};
