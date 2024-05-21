// HoNooD
// 2024.05.21 22:30

// 47. Permutations II
// https://leetcode.com/problems/permutations-ii/description/

// https://en.wikipedia.org/wiki/Backtracking
// https://en.wikipedia.org/wiki/Permutation
// https://en.wikipedia.org/wiki/Combination

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res{};
    vector<int> curr{};
    // Track if an element is used in the current permutation
    vector<bool> used(nums.size(), false);

    // Sort the numbers to handle duplicates
    std::sort(nums.begin(), nums.end());
    backtrack(res, curr, nums, used);

    return res;
  }

private:
  void backtrack(vector<vector<int>>& res, vector<int>& curr, vector<int> const& nums, vector<bool>used) {
    if (curr.size() == nums.size()) {
      res.emplace_back(curr);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (used[i]) {
        continue;
      }

      // Skip duplicate elements
      if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
        continue;
      }

      curr.emplace_back(nums[i]);
      used[i] = true;

      backtrack(res, curr, nums, used);

      curr.pop_back();
      used[i] = false;
    }
  }
};
