// HoNooD
// 2024.05.23 19:36

// 216. Combination Sum III
// https://leetcode.com/problems/combination-sum-iii/description/

// https://en.wikipedia.org/wiki/Backtracking
// https://en.wikipedia.org/wiki/Combination
// https://en.wikipedia.org/wiki/Permutation

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> res{};
    vector<int> combination{};
    backtrack(res, combination, 1, n, k);

    return res;
  }

private:
  void backtrack(vector<vector<int>>& res, vector<int>& combination, int start, int sum, int const& k) {
    if (sum == 0 && combination.size() == k) {
      res.emplace_back(combination);
      return;
    }

    for (int i = start; i <= 9; ++i) {
      if (i > sum || combination.size() >= k) {
        break;
      }

      combination.emplace_back(i);
      backtrack(res, combination, i + 1, sum - i, k);
      combination.pop_back();
    }
  }
};
