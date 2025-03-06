// HoNooD
// 2024.05.21 18:01

// 46. Permutations
// https://leetcode.com/problems/permutations/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Backtracking
// https://en.wikipedia.org/wiki/Permutation
// https://en.wikipedia.org/wiki/Combination

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res{};
    vector<int> curr{};
    // Track if an element is used in the current permutation
    vector<bool> used(nums.size(), false);
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

      curr.emplace_back(nums[i]);
      used[i] = true;

      backtrack(res, curr, nums, used);

      curr.pop_back();
      used[i] = false;
    }
  }
};
