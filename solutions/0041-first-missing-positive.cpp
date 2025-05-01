// HoNooD <honood@gmail.com>
// 2025.05.01 22:09
//
// 41. First Missing Positive
// https://leetcode.com/problems/first-missing-positive/?envType=study-plan-v2&envId=top-100-liked

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int firstMissingPositive(vector<int>& nums) {
    return first_missing_positive_v1(nums);
  }

private:
  // - Time complexity: O(n)
  //     - Although there's a nested while loop, each number `nums[i]` is
  //       moved (swapped) to its correct position `nums[i]-1` at most once.
  //       Once a number is in its correct place, the inner while loop condition
  //       `nums[nums[i] - 1] != nums[i]` prevents further swaps for that
  //       number. Thus, the total number of swaps is O(n). The initial loop
  //       runs n times. The second loop (finding the missing) also runs n
  //       times. Total time complexity: O(n) + O(n) = O(n).
  // - Space complexity: O(1)
  int first_missing_positive_v1(vector<int>& nums) {
    if (nums.empty()) {
      throw std::invalid_argument("nums must contain at least 1 elements");
    }

    int n = nums.size();

    // Step 1: Place each positive number `k` (where 1 <= k <= n) at its correct
    // index `k-1`.
    for (int i = 0; i < n; ++i) {
      // Keep swapping `nums[i]` until it's in its correct place, or it's out of
      // the range [1, n], or a duplicate is found.
      while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
        // Swap the number `nums[i]` to its target index `nums[i] - 1`.
        std::swap(nums[i], nums[nums[i] - 1]);
      }
    }

    // Step 2: Iterate through the modified array.
    // The first index `i` where `nums[i]` is not equal to `i + 1` indicates
    // that `i + 1` is the first missing positive integer.
    for (int i = 0; i < n; ++i) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }

    // Step 3: If the loop completes, it means all integers from 1 to n are
    // present and correctly placed. The first missing positive is n + 1.
    return n + 1;
  }
};
