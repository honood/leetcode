// HoNooD <honood@gmail.com>
// 2025.04.21 08:30
//
// 435. Non-overlapping Intervals
// https://leetcode.com/problems/non-overlapping-intervals/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// This problem is equivalent to finding the maximum set of mutually
// non-overlapping intervals. If the size of this maximum set is `k`, then the
// minimum number of intervals to remove is `n - k`, where n is the total number
// of intervals.

class Solution {
public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    return erase_overlap_intervals_v1(intervals);
  }

private:
  // - Time complexity: O(n * log(n))
  // - Space complexity: O(log(n)) or O(n), depending on the specific sorting
  //   algorithm implementation used.
  int erase_overlap_intervals_v1(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n <= 1) {
      return 0;
    }

    // Sort intervals by end time in ascending order
    //
    // If end times are equal, sorting by start time is not strictly necessary
    // for correctness but can be a good practice for consistency.
    std::sort(intervals.begin(), intervals.end(),
              [](vector<int> const& lhs, vector<int> const& rhs) {
                return lhs[1] < rhs[1];
              });

    // Keep the first interval (which finishes earliest)
    int kept_count = 1;
    // Track the end time of the last kept interval
    int last_end_time = intervals[0][1];

    for (int i = 1; i < n; ++i) {
      // If the current interval's start time is greater than or equal to the
      // end time of the last kept interval, they don't overlap.
      if (intervals[i][0] >= last_end_time) {
        // Keep this interval
        ++kept_count;
        // Update the end time of the last kept interval
        last_end_time = intervals[i][1];
      }
      // Else (intervals[i][0] < last_end_time):
      // The current interval overlaps with the last kept interval.
      // Since we sorted by end times, the interval ending at 'last_end_time'
      // finishes earlier or at the same time as the current interval
      // 'intervals[i]'.
      // The greedy choice is to keep the one that finishes earlier, which we
      // already did by keeping the previous one.
      // So, we effectively "remove" the current interval by skipping it.
    }

    // The minimum number of intervals to remove is the total number minus the
    // maximum number of non-overlapping intervals we kept.
    return n - kept_count;
  }

  // - Time complexity: O(n * log(n))
  // - Space complexity: O(log(n)) or O(n), depending on the specific sorting
  //   algorithm implementation used.
  int erase_overlap_intervals_v2(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n <= 1) {
      return 0;
    }

    // clang-format off
    //
    // Sort intervals primarily by start time, secondarily by end time (ascending).
    //
    // Sorting by start time is fundamental to this greedy approach.
    // The secondary sort by end time is CRUCIAL for correctness when intervals
    // share the same start time, especially involving degenerate intervals (e.g., [S, S]).
    // It dictates the processing order, which affects comparisons against `last_end_time`
    // and the `last_end_time = min(...)` update logic.
    //
    // Example: Input {{0, 1}, {1, 2}, {1, 1}}
    // - Correct order (with secondary sort): [[0, 1], [1, 1], [1, 2]]
    //   - Processing this order yields `removed_count = 0`. (Correct)
    // - Incorrect order (e.g., only primary sort): [[0, 1], [1, 2], [1, 1]]
    //   - Processing this order can incorrectly increment `removed_count` when
    //     comparing [1, 1] against the `last_end_time` set by [1, 2], leading to
    //     `removed_count = 1`. (Incorrect)
    // Thus, the secondary sort ensures correct handling of these critical edge cases.
    //
    // clang-format on
    std::sort(intervals.begin(), intervals.end(),
              [](vector<int> const& lhs, vector<int> const& rhs) {
                if (lhs[0] != rhs[0]) {
                  return lhs[0] < rhs[0];
                }
                return lhs[1] < rhs[1];
              });

    int removed_count = 0;
    int last_end_time = intervals[0][1];

    for (int i = 1; i < n; ++i) {
      if (intervals[i][0] < last_end_time) {
        // Overlap found, remove the interval with the larger end time
        ++removed_count;
        last_end_time = std::min(last_end_time, intervals[i][1]);
      } else {
        // No overlap, update last_end_time
        last_end_time = intervals[i][1];
      }
    }

    return removed_count;
  }

  // Time Limit Exceeded!
  //
  // See: solutions/0300-longest-increasing-subsequence.cpp
  //
  // - Time complexity: O(n^2)
  // - Space complexity: O(n), depending on the specific sorting
  //   algorithm implementation used.
  int erase_overlap_intervals_v3(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n <= 1) {
      return 0;
    }

    // clang-format off
    //
    // Sort intervals primarily by start time, secondarily by end time (ascending).
    //
    // Sorting by start time allows iterating through intervals and considering predecessors.
    // The secondary sort by end time is CRUCIAL for the correctness of this DP approach,
    // particularly when intervals share the same start time, including degenerate ones (e.g., [S, S]).
    // It ensures that an interval `j` potentially ending earlier (like [S, S]) has an index `j < i`
    // relative to another interval `i` starting at `S` (like [S, E]), allowing the DP transition
    // `dp[i] = max(dp[i], 1 + dp[j])` to correctly consider `j` if the non-overlap
    // condition `intervals[j][1] <= intervals[i][0]` holds.
    //
    // Example: Input {{0, 1}, {1, 2}, {1, 1}}
    // - Correct order (with secondary sort): [[0, 1], [1, 1], [1, 2]]
    //   - DP correctly finds `max_len = 3` -> 0 removals. (Correct)
    // - Incorrect order (e.g., only primary sort): [[0, 1], [1, 2], [1, 1]]
    //   - DP might fail to utilize the optimal substructure involving [1, 1] correctly,
    //     potentially finding only `max_len = 2` -> 1 removal. (Incorrect)
    // Thus, the secondary sort ensures the DP state transitions evaluate the correct predecessors.
    //
    // clang-format on
    std::sort(intervals.begin(), intervals.end(),
              [](vector<int> const& lhs, vector<int> const& rhs) {
                if (lhs[0] == rhs[0]) {
                  return lhs[1] < rhs[1];
                }
                return lhs[0] < rhs[0];
              });

    // dp[i] stores the maximum number of non-overlapping intervals ending with
    // intervals[i]
    //
    // Initialize all dp values to 1 (each interval itself is a sequence of
    // length 1)
    vector<int> dp(n, 1);

    int max_len = 1;

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (intervals[j][1] <= intervals[i][0]) {
          dp[i] = std::max(dp[i], dp[j] + 1);
        }
      }
      max_len = std::max(max_len, dp[i]);
    }

    return n - max_len;
  }
};
