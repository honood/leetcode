// HoNooD
// 2024.05.21 23:43

// 39. Combination Sum
// https://leetcode.com/problems/combination-sum/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Backtracking
// A backtracking algorithm tries to construct a solution to a computational 
// problem incrementally, one small piece at a time. Whenever the algorithm 
// needs to decide between multiple alternatives to the next component of the 
// solution, it recursively evaluates every alternative and then chooses the 
// best one.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    if (candidates.empty() || target <= 0) {
      return {};
    }

    vector<vector<int>> res{};
    vector<int> curr{};
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
      curr.emplace_back(candidates[i]);
      backtrack(res, curr, candidates, i, target - candidates[i]);
      curr.pop_back();
    }
  }
};
