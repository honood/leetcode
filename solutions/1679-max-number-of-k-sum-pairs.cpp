// HoNooD <honood@gmail.com>
// 2025.02.24 19:44

// 1679. Max Number of K-Sum Pairs
// https://leetcode.com/problems/max-number-of-k-sum-pairs/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Constraints:
//   1 <= nums[i] <= 10^9
#define    ALL_ELEMENTS_POSITIVE    1

class Solution {
public:
  int maxOperations(vector<int>& nums, int k) {
    return max_operations_v2(nums, k);
  }

private:
  // - Time complexity: O(n*log(n))
  // - Space complexity: O(1)
  int max_operations_v1(vector<int>& nums, int k) {
    std::sort(nums.begin(), nums.end());

    int result = 0;
    for (int i = 0, j = nums.size() - 1; i < j;) {
      int current_sum = nums[i] + nums[j];
      if (current_sum == k) {
        ++result;
        ++i;
        --j;
      } else if (current_sum < k) {
        ++i;
      } else {
        --j;
      }
    }
    return result;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int max_operations_v2(vector<int>& nums, int k) {
    unordered_map<int, int> freq{};
    int result = 0;
    for (int num : nums) {
#if ALL_ELEMENTS_POSITIVE
      if (num > k) {
        continue;
      }
#endif

      int temp = k - num;
      if (freq[temp] > 0) {
        ++result;
        --freq[temp];
      } else {
        ++freq[num];
      }
    }
    return result;
  }
};
