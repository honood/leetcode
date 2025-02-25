// HoNooD <honood@gmail.com>
// 2025.02.25 23:15

// 485. Max Consecutive Ones
// https://leetcode.com/problems/max-consecutive-ones/description/

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int findMaxConsecutiveOnes(vector<int>& nums) {
    return find_max_consecutive_ones_v3(nums);
  }

private:
  int find_max_consecutive_ones_v1(vector<int> const& nums) {
    if (nums.empty()) {
      return 0;
    }

    int n = nums.size();
    auto it = std::find(nums.cbegin(), nums.cend(), 0);
    if (it == nums.cend()) {
      return n;
    }

    int max_count = std::distance(nums.cbegin(), it);
    int prev = max_count;
    for (int i = prev + 1; i <= n; ++i) {
      if (i == n || nums[i] == 0) {
        max_count = std::max(max_count, i - prev - 1);
        prev = i;
      }
    }
    return max_count;
  }

  int find_max_consecutive_ones_v2(vector<int> const& nums) {
    int max_count = 0;
    for (int count = 0; int num : nums) {
      if (num == 1) {
        ++count;
        max_count = std::max(max_count, count);
      } else {
        count = 0;
      }
    }
    return max_count;
  }

  int find_max_consecutive_ones_v3(vector<int> const& nums) {
    int max_count = 0;
    for (int left = 0, right = 0; right < nums.size(); ++right) {
      if (nums[right] == 1) {
        max_count = std::max(max_count, right - left + 1);
      } else {
        left = right + 1;
      }
    }
    return max_count;
  }
};
