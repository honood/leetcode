// HoNooD <honood@gmail.com>
// 2024.06.20 08:30

// 11. Container With Most Water
// https://leetcode.com/problems/container-with-most-water/?envType=study-plan-v2&envId=top-interview-150
//
// You are given an integer array height of length `n`. There are `n` vertical
// lines drawn such that the two endpoints of the ith line are `(i, 0)` and
// `(i, height[i])`.
//
// Find two lines that together with the x-axis form a container, such that the
// container contains the most water.
//
// Return the maximum amount of water a container can store.
//
// Notice that you may not slant the container.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxArea(vector<int>& height) {
    int n = height.size();
    if (n <= 1) {
      return 0;
    }

    int maxArea = std::numeric_limits<int>::min();
    int left = 0;
    int right = n - 1;
    while (left < right) {
      int area = std::min(height[left], height[right]) * (right - left);
      maxArea = std::max(maxArea, area);

      // To maximize the area, one pointer must be moved:
      // 1. Regardless of whether `left` or `right` is moved, `(right - left)`
      //    will always decrease by `1`. Hence, from the perspective of the
      //    change in `(right - left)`, moving either has the same effect.
      // 2. Suppose `height[left] < height[right]`.
      //    - If `right` is moved, `min(height[left], height[right - 1])` might
      //      be smaller or remain the same as before.
      //    - If `left` is moved, `min(height[left + 1], height[right])` might
      //      be larger, smaller, or the same as before.
      //    Thus, to maximize the area, move `left`.
      if (height[left] < height[right]) {
        ++left;
      } else {
        --right;
      }
    }

    return maxArea;
  }
};

// Brute Force
// Do not use, will TLE (Time Limit Exceeded).
class Solution_2 {
public:
  int maxArea(vector<int>& height) {
    int n = height.size();
    if (n <= 1) {
      return 0;
    }

    int maxArea = std::numeric_limits<int>::min();
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int area = std::min(height[i], height[j]) * (j - i);
        maxArea = std::max(maxArea, area);
      }
    }

    return maxArea;
  }
};
