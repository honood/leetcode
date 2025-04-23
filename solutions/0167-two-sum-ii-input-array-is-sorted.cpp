// HoNooD <honood@gmail.com>
// 2025.04.23 22:32
//
// 167. Two Sum II - Input Array Is Sorted
// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    return two_sum_v1(nums, target);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  vector<int> two_sum_v1(vector<int> const& nums, int target) {
    int n = nums.size();
    if (n < 2) {
      return {};
    }

    int left = 0;
    int right = n - 1;
    while (left < right) {
      int sum = nums[left] + nums[right];
      if (sum == target) {
        return {left + 1, right + 1};
      } else if (sum < target) {
        ++left;
      } else {
        --right;
      }
    }

    return {};
  }

  // - Time complexity: O(n * log(n))
  // - Space complexity: O(1)
  vector<int> two_sum_v2(vector<int> const& nums, int target) {
    int n = nums.size();
    if (n < 2) {
      return {};
    }

    for (int i = 0; i < n - 1; ++i) {
      int complement = target - nums[i];
      // Search for complement starting from index i + 1
      auto it = std::lower_bound(nums.begin() + i + 1, nums.end(), complement);
      if (it != nums.end() && *it == complement) {
        return {i + 1, static_cast<int>(std::distance(nums.begin(), it)) + 1};
      }
    }

    return {};
  }

  // - Time complexity: O(n * log(n))
  // - Space complexity: O(1)
  vector<int> two_sum_v2_2(vector<int> const& nums, int target) {
    int n = nums.size();
    if (n < 2) {
      return {};
    }

    for (int i = 0; i < n - 1; ++i) {
      int complement = target - nums[i];

      // Perform binary search for 'complement' in the range [i + 1, n - 1]
      int left = i + 1;
      int right = n - 1;
      while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == complement) {
          return {i + 1, mid + 1};
        } else if (nums[mid] < complement) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      }
    }

    return {};
  }
};
