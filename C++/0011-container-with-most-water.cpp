// HoNooD <honood@gmail.com>
// 2025.02.24 18:30

// 11. Container With Most Water
// https://leetcode.com/problems/container-with-most-water/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/container-with-most-water/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int maxArea(vector<int>& height) {
    return max_area_v1(height);
  }

private:
  int max_area_v1(vector<int> const& height) {
    int max_area = 0;
    for (int left = 0, right = height.size() - 1; left < right;) {
      int current_area = std::min(height[left], height[right]) * (right - left);
      max_area = std::max(max_area, current_area);

      if (height[left] < height[right]) {
        ++left;
      } else {
        --right;
      }
    }
    return max_area;
  }
};
