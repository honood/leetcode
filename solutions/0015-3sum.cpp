// HoNooD <honood@gmail.com>
// 2025.04.23 11:47
//
// 15. 3Sum
// https://leetcode.com/problems/3sum/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/3sum/?envType=study-plan-v2&envId=top-100-liked

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // clang-format off
  //
  // Constraints: -10^5 <= nums[i] <= 10^5
  //
  // Note:
  // 1. std::numeric_limits<int>::max() = INT_MAX =  2'147'483'647
  // 2. std::numeric_limits<int>::min() = INT_MIN = -2'147'483'648
  // 3. INT_MIN < (-10^5) * 3 <= nums[i] + nums[j] + nums[k] <= (10^5) * 3 < INT_MAX
  //
  // clang-format on
  vector<vector<int>> threeSum(vector<int>& nums) {
    return three_sum_v2(nums);
  }

private:
  // Time Limit Exceeded!
  //
  // - Time complexity: O(n^3)
  // - Space complexity: O(n)
  vector<vector<int>> three_sum_v1(vector<int> const& nums) {
    int n = nums.size();
    if (n < 3) {
      return {};
    }

    std::set<vector<int>> result_set{};
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        for (int k = j + 1; k < n; ++k) {
          if (nums[i] + nums[j] + nums[k] == 0) {
            vector<int> triplet{nums[i], nums[j], nums[k]};
            std::sort(triplet.begin(), triplet.end());
            result_set.insert(std::move(triplet));
          }
        }
      }
    }
    return vector<vector<int>>{result_set.begin(), result_set.end()};
  }

  // - Time complexity: O(n^2)
  // - Space complexity: O(log(n)) or O(n), depending on the specific sorting
  //   algorithm implementation used.
  vector<vector<int>> three_sum_v2(vector<int>& nums) {
    int n = nums.size();
    if (n < 3) {
      return {};
    }

    std::sort(nums.begin(), nums.end());

    vector<vector<int>> result{};

    // Iterate through the array, fixing the first element
    for (int i = 0; i < n - 2; ++i) {
      if (int min_sum = nums[i] + nums[i + 1] + nums[i + 2]; min_sum > 0) {
        break;
      }

      // Skip duplicate first elements to avoid duplicate triplets
      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }

      if (int max_sum = nums[i] + nums[n - 2] + nums[n - 1]; max_sum < 0) {
        continue;
      }

      int left = i + 1;
      int right = n - 1;
      int target = -nums[i];

      while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
          result.push_back({nums[i], nums[left], nums[right]});

          // Skip duplicate second elements
          while (left < right && nums[left] == nums[left + 1]) {
            ++left;
          }
          // Skip duplicate third elements
          while (left < right && nums[right - 1] == nums[right]) {
            --right;
          }

          // Move pointers inward
          ++left;
          --right;
        } else if (sum < target) {
          // Sum is too small, need a larger number
          ++left;
        } else {
          // Sum is too larger, need a smaller number
          --right;
        }
      } // while
    } // for

    return result;
  }

  // - Time complexity: O(n^2)
  // - Space complexity: O(n)
  vector<vector<int>> three_sum_v3(vector<int>& nums) {
    int n = nums.size();
    if (n < 3) {
      return {};
    }

    std::sort(nums.begin(), nums.end());

    std::set<vector<int>> result_set{};

    for (int i = 0; i < n - 2; ++i) {
      if (nums[i] > 0) {
        break;
      }

      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }

      std::unordered_set<int> seen{};
      for (int j = i + 1; j < n; ++j) {
        int complement = -nums[i] - nums[j];
        if (seen.contains(complement)) {
          vector<int> triplet{nums[i], complement, nums[j]};
          // No need to sort triplet here as nums[i] <= complement <= nums[j]
          // due to overall sort and lookup order
          result_set.insert(std::move(triplet));
        }
        seen.insert(nums[j]);
      }
    }

    return vector<vector<int>>{result_set.begin(), result_set.end()};
  }
};
