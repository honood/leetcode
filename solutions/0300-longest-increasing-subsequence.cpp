// HoNooD <honood@gmail.com>
// 2024.07.04 23:18

// 300. Longest Increasing Subsequence
// https://leetcode.com/problems/longest-increasing-subsequence/description/?envType=study-plan-v2&envId=top-interview-150

// Longest increasing subsequence
// https://en.wikipedia.org/wiki/Longest_increasing_subsequence

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int lengthOfLIS(vector<int>& nums) {
    return length_of_lis_v1(nums);
  }

private:
  // - Time complexity: O(n^2)
  // - Space complexity: O(n)
  int length_of_lis_v1(vector<int> const& nums) {
    if (nums.empty()) return 0;

    int n = nums.size();

    // dp[i] represents the length of the longest increasing subsequence ending
    // at index i (nums[i] must be included)
    //
    // Base case: Each element itself forms an LIS of length 1.
    vector<int> dp(n, 1);

    int max_len = 1;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          // If we can extend the subsequence ending at j, update dp[i] if it
          // leads to a longer subsequence.
          dp[i] = std::max(dp[i], dp[j] + 1);
        }
      }
      max_len = std::max(max_len, dp[i]);
    }
    return max_len;
  }

  // Solution using Dynamic Programming with Binary Search (Patience Sorting analogy).
  // https://en.wikipedia.org/wiki/Patience_sorting
  //
  // - Time complexity: O(n * log(n))
  // - Space complexity: O(n)
  int length_of_lis_v2(vector<int> const& nums) {
    // 'tails' is an array storing the smallest tail of all increasing
    // subsequences with length i+1 at index i.
    // Example: tails[0] = smallest tail of LIS of length 1
    //          tails[1] = smallest tail of LIS of length 2
    //          ...
    // This array is always maintained in sorted order.
    vector<int> tails{};

    for (int num : nums) {
      // Binary search to find the first element in 'tails' that is >= num.
      // 'lower_bound' returns an iterator to the first element not less than
      // 'num'.
      auto it = std::lower_bound(tails.begin(), tails.end(), num);
      if (it == tails.end()) {
        // If 'num' is greater than all elements in 'tails', it means we can
        // extend the longest increasing subsequence found so far. Append 'num'
        // to 'tails', effectively increasing the length of the LIS by 1. The
        // size of 'tails' directly corresponds to the current LIS length.
        tails.emplace_back(num);
      } else {
        // If we found an element *it (which is tails[i] for some i) such that
        // *it >= num. It means 'num' can potentially replace 'tails[i]' to form
        // an increasing subsequence of length i+1 that ends with a smaller
        // number ('num') than the previous 'tails[i]'. Replacing 'tails[i]'
        // with 'num' optimizes for the future: a smaller tail allows for more
        // possibilities to extend the subsequence later. Crucially, this
        // replacement *does not* change the length of 'tails'. Therefore, it
        // reflects that we haven't found a *longer* LIS yet, but we've
        // potentially found a "better" (smaller tail) LIS of the same length
        // (i+1).
        *it = num;
      }
    }

    // The final size of the 'tails' array gives the length of the Longest
    // Increasing Subsequence.
    //
    // Why does tails.size() work?
    // - The size only increases when we append (case: it == tails.end()), which
    //   happens exactly when we find a number that can extend the *current*
    //   longest subsequence.
    // - The replacement step (case: else) doesn't change the size, correctly
    //   reflecting that we haven't increased the maximum length found so far.
    //
    // Important Note: The 'tails' array itself at the end does *not*
    // necessarily represent an actual LIS sequence from 'nums'.
    //
    // For instance, if `nums = [0, 8, 4, 12, 2]`:
    // 1. Process 0: tails = [0]
    // 2. Process 8: tails = [0, 8]
    // 3. Process 4: 4 replaces 8. tails = [0, 4] (Length still 2)
    // 4. Process 12: tails = [0, 4, 12]
    // 5. Process 2: 2 replaces 4. tails = [0, 2, 12] (Length still 3)
    // The final `tails` is `[0, 2, 12]`. The length 3 is correct (LIS is [0, 8,
    // 12] or [0, 4, 12]). However, `[0, 2, 12]` is not a valid subsequence of
    // the original `nums` because `12` appears *before* `2` in the input
    // `nums`.
    //
    // The replacement step prioritizes maintaining the "smallest tail for each
    // length" property, which might create a 'tails' sequence whose elements
    // don't respect the original order in 'nums'. However, its *length*
    // accurately tracks the LIS length.
    return tails.size();
  }
};
