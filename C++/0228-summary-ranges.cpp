// HoNooD <honood@gmail.com>
// 2024.06.10 19:31

// 228. Summary Ranges
// https://leetcode.com/problems/summary-ranges/?envType=study-plan-v2&envId=top-interview-150

// See also:
// 128. Longest Consecutive Sequence
// https://leetcode.com/problems/longest-consecutive-sequence/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<string> summaryRanges(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) {
      return {};
    }

    vector<string> res{};
    int left = 0;
    for (int i = 1; i <= n; ++i) {
      if (i <= n - 1 && nums[i] == nums[i - 1] + 1) {
        continue;
      }

      if (left == i - 1) {
        res.emplace_back(std::to_string(nums[left]));
      } else {
        res.emplace_back(std::to_string(nums[left]) + "->" + std::to_string(nums[i - 1]));
      }

      left = i;
    }

    return res;
  }
};
