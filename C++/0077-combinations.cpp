// HoNooD
// 2024.05.21 14:30

// 77. Combinations
// https://leetcode.com/problems/combinations/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Backtracking
// https://en.wikipedia.org/wiki/Combination
// https://en.wikipedia.org/wiki/Permutation

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// The basic steps for generating combinations (`C(n, k)`) using the backtracking 
// method are as follows:
// 1. Start with an empty combination;
// 2. Gradually add numbers to the combination until its length reaches `k`;
// 3. After adding a new number, recursively enter the next level to continue 
// trying to add the next number;
// 4. If the current combination length reaches `k`, add this combination to the 
// result set;
// 5. Backtrack one step to try other possible combinations.
class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res{};
    vector<int> curr{};
    backtrack(res, curr, 1, n, k);

    return res;
  }

private:
  void backtrack(vector<vector<int>>& res, vector<int>& curr, int start, int n, int k) {
    if (0 == k) {
      res.emplace_back(curr);
      return;
    }

    for (int i = start; i <= n; ++i) {
      curr.emplace_back(i);
      backtrack(res, curr, i + 1, n, k - 1);
      curr.pop_back();
    }
  }
};

class Solution_2 {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res{};
    vector<int> curr(k, 0);

    int i = 0;
    while (i >= 0) {
      ++curr[i];

      // If the current number exceeds the range [1, n], backtrack to the 
      // previous position.
      if (curr[i] > n) {
        --i;
        continue;
      }

      // If we have filled up all slots in the current combination, add it to
      // the result.
      if (k - 1 == i) {
        res.emplace_back(curr);
        continue;
      }

      // If there are more slots to fill, move to the next slot and set its 
      // value to be the same as the previous slot.
      ++i;
      curr[i] = curr[i - 1];
    }

    return res;
  }
};
