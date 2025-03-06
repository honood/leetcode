// HoNooD <honood@gmail.com>
// 2024.06.11 08:00

// 57. Insert Interval
// https://leetcode.com/problems/insert-interval/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Using a new array yields better performance, because modifying the original
// array generally involves linear scans and operations (such as `erase` and
// `insert`), which can lead to higher overhead due to multiple element shifts.
//
// Additionally, `std::move` parts of elements from the original array can
// further enhance performance.
class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    if (intervals.empty()) {
      return {newInterval};
    }

    vector<vector<int>> res{};
    int i = 0;
    int n = intervals.size();

    // Add intervals before the new interval
    while (i < n && newInterval[0] > intervals[i][1]) {
      res.emplace_back(std::move(intervals[i]));
      ++i;
    }

    // Merge overlapping intervals with the new interval
    while (i < n && newInterval[1] >= intervals[i][0]) {
      newInterval[0] = std::min(newInterval[0], intervals[i][0]);
      newInterval[1] = std::max(newInterval[1], intervals[i][1]);
      ++i;
    }
    res.emplace_back(std::move(newInterval));

    // Add remaining intervals after the new interval
    while (i < n) {
      res.emplace_back(std::move(intervals[i]));
      ++i;
    }

    return res;
  }
};

// Modify the original array directly
//
// Considerably slower when compared to the `Solution`.
class Solution_2 {
public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    if (intervals.empty()) {
      return {newInterval};
    }

    int i = 0;
    // Skip intervals that end before the new interval starts
    while (i < intervals.size() && newInterval[0] > intervals[i][1]) {
      ++i;
    }

    // Merge overlapping intervals with the new interval
    while (i < intervals.size() && newInterval[1] >= intervals[i][0]) {
      newInterval[0] = std::min(newInterval[0], intervals[i][0]);
      newInterval[1] = std::max(newInterval[1], intervals[i][1]);
      intervals.erase(std::next(intervals.cbegin(), i));
    }

    // Insert the merged new interval
    intervals.emplace(std::next(intervals.cbegin(), i), std::move(newInterval));

    return intervals;
  }
};
