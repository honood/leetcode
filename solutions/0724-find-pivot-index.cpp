// HoNooD <honood@gmail.com>
// 2025.02.28 00:19

// 724. Find Pivot Index
// https://leetcode.com/problems/find-pivot-index/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int pivotIndex(vector<int>& nums) {
    return pivot_index_v2(nums);
  }

  int pivot_index_v1(vector<int> const& nums) {
    int n = nums.size();
    vector<int> partial_sum(n);
    std::partial_sum(nums.cbegin(), nums.cend(), partial_sum.begin());

    for (int left_sum, right_sum, i = 0; i < n; ++i) {
      if (i == 0) {
        left_sum = 0;
        right_sum = partial_sum.back() - partial_sum[i];
      } else if (i == n - 1) {
        left_sum = partial_sum[i - 1];
        right_sum = 0;
      } else {
        left_sum = partial_sum[i - 1];
        right_sum = partial_sum.back() - partial_sum[i];
      }
      if (left_sum == right_sum) {
        return i;
      }
    }
    return -1;
  }

  int pivot_index_v2(vector<int> const& nums) {
    int total_sum = std::reduce(nums.cbegin(), nums.cend());
    int left_sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      int right_sum = total_sum - left_sum - nums[i];
      if (left_sum == right_sum) {
        return i;
      }

      left_sum += nums[i];
    }
    return -1;
  }
};
