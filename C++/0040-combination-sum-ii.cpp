// HoNooD
// 2024.05.23 11:02

// 40. Combination Sum II
// https://leetcode.com/problems/combination-sum-ii/description/

// https://en.wikipedia.org/wiki/Backtracking

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    if (candidates.empty() || target <= 0) {
      return {};
    }

    vector<vector<int>> res{};
    vector<int> curr{};

    // Sort the numbers to handle duplicates
    std::sort(candidates.begin(), candidates.end());
    backtrack(res, curr, candidates, 0, target);

    return res;
  }

private:
  void backtrack(vector<vector<int>>& res, vector<int>& curr, vector<int> const& candidates, int start, int target) {
    if (target < 0) {
      return;
    }

    if (target == 0) {
      res.emplace_back(curr);
      return;
    }

    for (int i = start; i < candidates.size(); ++i) {
      if (i > start && candidates[i] == candidates[i - 1]) {
        continue;
      }

      curr.emplace_back(candidates[i]);
      backtrack(res, curr, candidates, i + 1, target - candidates[i]);
      curr.pop_back();
    }
  }
};
