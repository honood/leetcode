// HoNooD <honood@gmail.com>
// 2025.03.25 17:30
// 2024.05.23 19:36

// 216. Combination Sum III
// https://leetcode.com/problems/combination-sum-iii/description/?envType=study-plan-v2&envId=leetcode-75

// https://en.wikipedia.org/wiki/Backtracking
// https://en.wikipedia.org/wiki/Combination
// https://en.wikipedia.org/wiki/Permutation

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> combinationSum3(int k, int n) {
    return combination_sum3_v2(k, n);
  }

private:
  // - Time complexity: O(C(9, k) * k)
  // - Space complexity: O(k)
  vector<vector<int>> combination_sum3_v1(int k, int n) {
    vector<vector<int>> result{};
    vector<int> current{};
    current.reserve(k);

    std::function<void(int, int)> backtrack
      = [&backtrack, &result, &current, k](int target, int start) {
          if (current.size() == k) {
            if (target == 0) {
              result.emplace_back(current); // O(k)
            }
            return;
          }

          // 1. Checking `current.size() > k` is redundant as the recursive
          // structure ensures size never exceeds k
          // 2. Checking `target < 0` is not mandatory but improves performance
          // by pruning paths that cannot lead to valid solutions
          if (target < 0 /* || current.size() > k */) {
            return;
          }

          for (int i = start; i <= 9; ++i) {
            current.push_back(i);
            backtrack(target - i, i + 1);
            current.pop_back(); // Backtrack
          }
        };

    backtrack(n, 1);

    return result;
  }

  // - Time complexity: O(C(9, k) * k)
  // - Space complexity: O(k)
  vector<vector<int>> combination_sum3_v2(int k, int n) {
    vector<vector<int>> result{};
    vector<int> current{};
    current.reserve(k);

    std::function<void(int, int)> backtrack
      = [&backtrack, &result, &current, k](int target, int start) {
          if (current.size() == k) {
            if (target == 0) {
              result.emplace_back(current); // O(k)
            }
            return;
          }

          // Early pruning: if remaining target is negative
          if (target < 0) {
            return;
          }

          // Early pruning: if can't form a valid combination anymore
          int remaining = k - current.size();
          if (remaining > 9 - start + 1) {
            return;
          }

          // Early pruning: if the sum of smallest remaining numbers exceeds
          // target
          int min_sum = 0;
          for (int i = 0; i < remaining; ++i) {
            min_sum += start + i;
          }
          // int min_sum = (start + (start + remaining - 1)) * remaining / 2;
          if (min_sum > target) {
            return;
          }

          // Early pruning: if the sum of largest remaining numbers is less than
          // target
          int max_sum = 0;
          for (int i = 0; i < remaining; ++i) {
            max_sum += 9 - i;
          }
          // int max_sum = (9 + (9 - remaining + 1)) * remaining / 2;
          if (max_sum < target) {
            return;
          }

          for (int i = start; i <= 9; ++i) {
            current.push_back(i);
            backtrack(target - i, i + 1);
            current.pop_back(); // Backtrack
          }
        };

    backtrack(n, 1);

    return result;
  }

  // - Time complexity: O(2^9)
  // - Space complexity: O(k)
  vector<vector<int>> combination_sum3_v3(int k, int n) {
    vector<vector<int>> result{};
    vector<int> current{};
    current.reserve(k);

    // Generate all possible combinations using bit manipulation
    for (int mask = 0; mask < (1 << 9); ++mask) {
      // Skip if not exactly k bits set
      if (__builtin_popcount(mask) != k) { // use `std::popcount` if available
        continue;
      }

      int sum = 0;
      // Check each bit int the mask
      for (int i = 0; i < 9; ++i) {
        if (mask & (1 << i)) {
          current.push_back(i + 1);
          sum += i + 1;
        }
      }

      if (sum == n) {
        result.emplace_back(std::move(current));
      }
    }

    return result;
  }
};
