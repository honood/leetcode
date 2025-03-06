// HoNooD <honood@gmail.com>
// 2024.06.10 20:40

// 56. Merge Intervals
// https://leetcode.com/problems/merge-intervals/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    int n = intervals.size();
    if (n == 0) { return {}; }
    if (n == 1) { return intervals; }

    std::sort(intervals.begin(), intervals.end());

    vector<vector<int>> res{};
    assert(intervals[0].size() == 2);
    int left = intervals[0][0];
    int right = intervals[0][1];
    for (int i = 1; i < n; ++i) {
      auto const& interval = intervals[i];
      assert(interval.size() == 2);
      if (interval[1] <= right) {
        continue;
      }

      if (interval[0] > right) {
        res.emplace_back(vector<int>{left, right});

        left = interval[0];
        right = interval[1];
      } else {
        right = interval[1];
      }
    }

    res.emplace_back(vector<int>{left, right});

    return res;
  }
};

// Great!
// Simpler and more readable!
class Solution_2 {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    int n = intervals.size();
    if (n == 0) { return {}; }
    if (n == 1) { return intervals; }

    std::sort(intervals.begin(), intervals.end());

    vector<vector<int>> res{intervals[0]};
    for (int i = 1; i < n; ++i) {
      auto const& interval = intervals[i];
      if (res.back()[1] >= interval[0]) {
        res.back()[1] = std::max(res.back()[1], interval[1]);
      } else {
        res.emplace_back(interval);
      }
    }

    return res;
  }
};
