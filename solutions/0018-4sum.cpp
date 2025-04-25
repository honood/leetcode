// HoNooD <honood@gmail.com>
// 2025.04.25 10:47
//
// 18. 4Sum
// https://leetcode.com/problems/4sum/

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // clang-format off
  //
  // Constraints:
  // 1. -10^9 <= nums[i] <= 10^9
  // 2. -10^9 <= target <= 10^9
  //
  // Note:
  // 1. std::numeric_limits<int>::max()       =   INT_MAX =              2'147'483'647
  // 2. std::numeric_limits<int>::min()       =   INT_MIN =             -2'147'483'648
  // 3. std::numeric_limits<long long>::max() = LLONG_MAX =  9'223'372'036'854'775'807
  // 4. std::numeric_limits<long long>::min() = LLONG_MIN = -9'223'372'036'854'775'808
  // 5. INT_MIN   ≮ (-10^9) * 4 <= nums[i] + nums[j] + nums[k] + nums[l] <= (10^9) * 4 ≮ INT_MAX
  // 6. LLONG_MIN < (-10^9) * 4 <= nums[i] + nums[j] + nums[k] + nums[l] <= (10^9) * 4 < LLONG_MAX
  //
  // clang-format on
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    return four_sum_v3(nums, target);
  }

private:
  // - Time complexity: O(n^3)
  // - Space complexity: O(n)
  vector<vector<int>> four_sum_v1(vector<int>& nums, int target) {
    // clang-format off
    int n = nums.size();
    if (n < 4) {
      return {};
    }

    std::sort(nums.begin(), nums.end());

    vector<vector<int>> result{};

    using ll = long long;
    for (int i = 0; i < n - 3; ++i) {
      if (ll min_sum = static_cast<ll>(nums[i]) + nums[i + 1] + nums[i + 2] + nums[i + 3]; min_sum > target) break;
      if (i > 0 && nums[i] == nums[i - 1]) continue;
      if (ll max_sum = static_cast<ll>(nums[i]) + nums[n - 3] + nums[n - 2] + nums[n - 1]; max_sum < target) continue;

      for (int j = i + 1; j < n - 2; ++j) {
        if (ll min_sum = static_cast<ll>(nums[i]) + nums[j] + nums[j + 1] + nums[j + 2]; min_sum > target) break;
        if (j > i + 1 && nums[j] == nums[j - 1]) continue;
        if (ll max_sum = static_cast<ll>(nums[i]) + nums[j] + nums[n - 2] + nums[n - 1]; max_sum < target) continue;

        int left = j + 1;
        int right = n - 1;
        while (left < right) {
          ll sum = static_cast<ll>(nums[i]) + nums[j] + nums[left] + nums[right];
          if (sum == target) {
            result.push_back({nums[i], nums[j], nums[left], nums[right]});

            ++left;
            --right;

            while (left < right && nums[left] == nums[left - 1]) ++left;
            while (left < right && nums[right] == nums[right + 1]) --right;
          } else if (sum < target) {
            ++left;
          } else {
            --right;
          }
        } // while
      } // for: j
    } // for: i

    return result;
    // clang-format on
  }

  // - Time complexity: O(n^3)
  // - Space complexity: O(n^2)
  vector<vector<int>> four_sum_v2(vector<int>& nums, int target) {
    // clang-format off
    int n = nums.size();
    if (n < 4) {
      return {};
    }

    std::sort(nums.begin(), nums.end());

    unordered_map<long long, vector<std::pair<int, int>>> pair_sums{};

    // for (int k = 0; k < n - 1; ++k) {
    //   // CRITICAL NOTE: Do NOT skip based on `nums[k] == nums[k-1]` here.
    //   //
    //   // Example demonstrating the issue if skipped:
    //   //   nums = [1, 0, -1, 0, -2, 2], target = 0
    //   //   Sorted: [-2, -1, 0, 0, 1, 2] (Indices: 0, 1, 2, 3, 4, 5)
    //   //   Expected result: [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]
    //   //   Actual result:  [[-2, -1, 1, 2]]
    //   //
    //   // if (k > 0 && nums[k] == nums[k - 1]) continue; // <<< MUST remain commented out or removed.
    //
    //   for (int l = k + 1; l < n; ++l) {
    //     if (l > k + 1 && nums[l] == nums[l - 1]) continue;
    //
    //     long long sum = static_cast<long long>(nums[k]) + nums[l];
    //     pair_sums[sum].emplace_back(k, l);
    //   }
    // }

    // -OR-
    for (int l = n - 1; l > 0; --l) {
      if (l < n - 1 && nums[l] == nums[l + 1]) continue;

      for (int k = l - 1; k >= 0; --k) {
        if (k < l - 1 && nums[k] == nums[k + 1]) continue;

        long long sum = static_cast<long long>(nums[k]) + nums[l];
        pair_sums[sum].emplace_back(k, l);
      }
    }

    vector<vector<int>> result{};

    for (int i = 0; i < n - 3; ++i) {
      // Skip duplicate values for the first element (nums[i]).
      //
      // Since the array is sorted, if nums[i] == nums[i-1], any valid
      // quadruplet starting with nums[i] (e.g., [value_i, value_j, value_k,
      // value_l]) would represent the same *combination of values* as a
      // quadruplet that could have been formed starting with nums[i-1]. This
      // prevents adding value-duplicate quadruplets to the result set.
      if (i > 0 && nums[i] == nums[i - 1]) continue;

      for (int j = i + 1; j < n - 2; ++j) {
        // Given a fixed nums[i], skip adjacent duplicates for the second
        // element nums[j].
        //
        // If nums[j] == nums[j-1], any quadruplet found using nums[j] would
        // have the same *value combination* as one found using nums[j-1].
        if (j > i + 1 && nums[j] == nums[j - 1]) continue;

        long long complement = static_cast<long long>(target) - nums[i] - nums[j];
        if (pair_sums.contains(complement)) {
          for (auto [k, l] : pair_sums[complement]) {
            // Consider: nums[i] + nums[j] + nums[k] + nums[l] == target,
            // where nums[k1] == nums[k2] == nums[k3] (k1 < k2 < k3 are indices)
            //
            // Case 1: Index order: i < k1 < k2 < k3 < j < l
            //
            //         ─┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─
            //          i           k1    k2    k3          j           l
            // Note: Invalid. The condition j < k fails for k1, k2, and k3.
            //
            // Case 2: Index order: i < k1 < j = k2 < k3 < l
            //
            //         ─┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─
            //          i           k1   j(k2)  k3                      l
            // Note: Potentially problematic if preprocessing skipped pairs.
            //       If pair (k3, l) were skipped during map population due to
            //       k2/k3 having duplicate values, solutions requiring j < k3
            //       might be missed.
            //
            // Case 3: Index order: i < j < k1 < k2 < k3 < l
            //
            //         ─┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─
            //          i           j           k1    k2    k3          l
            // Note: Safe even if preprocessing skipped pairs (k2, l), (k3, l).
            //       The condition j < k1 holds, allowing the quadruplet to be
            //       found using the pair (k1, l).
            //
            //
            // Consider: nums[i] + nums[j] + nums[k] + nums[l] == target,
            // where nums[l1] == nums[l2] == nums[l3] (l1 < l2 < l3 are indices).
            //
            // Case 4: Index order: i < j < k < l1 < l2 < l3
            //
            //         ─┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─
            //          i           j           k           l1    l2    l3
            // Note: Safe even if preprocessing skipped pairs (k, l2), (k, l3).
            //       As long as the pair (k, l1) (using the first occurrence l1)
            //       is stored in the map, the condition j < k ensures the
            //       quadruplet can be found.
            if (j < k) {
              if (!result.empty()
                  && result.back() == vector<int>{nums[i], nums[j], nums[k], nums[l]}) {
                continue;
              }

              result.push_back({nums[i], nums[j], nums[k], nums[l]});
            }
          }
        }
      }
    }

    return result;
    // clang-format on
  }

  // - Time complexity: O(n^(k-1))
  // - Space complexity: O(k)
  vector<vector<int>> four_sum_v3(vector<int>& nums, int target) {
    int n = nums.size();
    if (n < 4) {
      return {};
    }

    std::sort(nums.begin(), nums.end());

    return k_sum(nums, target, 4, 0);
  }

  vector<vector<int>> k_sum(vector<int>& sorted_nums, long long target, int k,
                            int start) {
    int n = sorted_nums.size();
    if (n == 0 || k < 2 || n - start < k) {
      return {};
    }

    vector<vector<int>> result{};

    // Base case: k = 2 (2Sum problem)
    if (k == 2) {
      int left = start;
      int right = n - 1;
      while (left < right) {
        long long sum = sorted_nums[left] + sorted_nums[right];
        if (sum == target) {
          result.push_back({sorted_nums[left], sorted_nums[right]});

          ++left;
          --right;

          while (left < right && sorted_nums[left] == sorted_nums[left - 1]) {
            ++left;
          }
          while (left < right && sorted_nums[right] == sorted_nums[right + 1]) {
            --right;
          }
        } else if (sum < target) {
          ++left;
        } else {
          --right;
        }
      }
    } // if (k == 2)

    // Recursive step: k > 2
    for (int i = start; i <= n - k; ++i) {
      long long min_sum = sorted_nums[i];
      for (int j = 1; j < k; ++j) {
        min_sum += sorted_nums[i + j];
      }
      if (min_sum > target) {
        break;
      }

      if (i > start && sorted_nums[i] == sorted_nums[i - 1]) {
        continue;
      }

      long long max_sum = sorted_nums[i];
      for (int j = 1; j < k; ++j) {
        max_sum += sorted_nums[n - j];
      }
      if (max_sum < target) {
        continue;
      }

      auto subsets = k_sum(sorted_nums, target - sorted_nums[i], k - 1, i + 1);
      for (auto& subset : subsets) {
        subset.insert(subset.cbegin(), sorted_nums[i]);
        result.push_back(std::move(subset));
      }
    } // for: i

    return result;
  }
};
