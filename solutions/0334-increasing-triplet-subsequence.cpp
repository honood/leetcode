// HoNooD <honood@gmail.com>
// 2025.02.21 09:25

// 334. Increasing Triplet Subsequence
// https://leetcode.com/problems/increasing-triplet-subsequence/description/?envType=study-plan-v2&envId=leetcode-75

// Follow up: Could you implement a solution that runs in O(n) time complexity
// and O(1) space complexity?

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  bool increasingTriplet(vector<int>& nums) {
    return increasing_triplet_v2(nums);
  }

private:
  // Time complexity: O(n^3)
  bool increasing_triplet_v1(vector<int>& nums) {
    size_t n = nums.size();
    if (n < 3) {
      return false;
    }

    for (size_t i = 0; i < n; ++i) {
      for (size_t j = i + 1; j < n; ++j) {
        for (size_t k = j + 1; k < n; ++k) {
          if (nums[i] < nums[j] && nums[j] < nums[k]) {
            return true;
          }
        }
      }
    }

    return false;
  }

  bool increasing_triplet_v2(vector<int>& nums) {
    size_t n = nums.size();
    if (n < 3) {
      return false;
    }

    int min_so_far = nums[0];
    int second = std::numeric_limits<int>::max();
    for (size_t i = 1; i < n; ++i) {
      // Note: Usig `nums[i] < min_so_far` is incorrect, as it could cause
      // `second` to equal `min_so_far`.
      if (nums[i] <= min_so_far) {
        min_so_far = nums[i];
      } else {
        if (nums[i] > second) {
          return true;
        }

        if (nums[i] < second) {
          second = nums[i];
        }
      }
    }

    return false;
  }
};
