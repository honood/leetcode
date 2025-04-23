// HoNooD <honood@gmail.com>
// 2024.06.12 09:10
// 2025.04.22 16:19

// 452. Minimum Number of Arrows to Burst Balloons
// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int findMinArrowShots(vector<vector<int>>& points) {
    return find_min_arrow_shots_v2(points);
  }

private:
  // - Time complexity: O(n * log(n))
  // - Space complexity: O(log(n)) or O(n), depending on the specific sorting
  //   algorithm implementation used.
  int find_min_arrow_shots_v1(vector<vector<int>>& points) {
    int n = points.size();
    if (n < 2) {
      return n;
    }

    // Sort balloons by start coordinate
    std::sort(points.begin(), points.end(),
              [](auto const& lhs, auto const& rhs) {
                if (lhs[0] != rhs[0]) {
                  return lhs[0] < rhs[0];
                }
                // Secondary sort by end coordinate (OPTIONAL but good practice)
                return lhs[1] < rhs[1];
              });

    int arrows = 1;
    // Track the minimum end point of the current overlapping group
    int curr_overlap_end = points[0][1];

    for (int i = 1; i < n; ++i) {
      if (points[i][0] > curr_overlap_end) {
        ++arrows;
        curr_overlap_end = points[i][1];
      } else {
        curr_overlap_end = std::min(curr_overlap_end, points[i][1]);
      }
    }

    return arrows;
  }

  // - Time complexity: O(n * log(n))
  // - Space complexity: O(log(n)) or O(n), depending on the specific sorting
  //   algorithm implementation used.
  int find_min_arrow_shots_v2(vector<vector<int>>& points) {
    int n = points.size();
    if (n < 2) {
      return n;
    }

    // Sort balloons by end coordinate
    // If end coordinates are the same, sorting by start doesn't strictly matter
    // for correctness here, but it's a common practice.
    std::sort(points.begin(), points.end(),
              [](auto const& lhs, auto const& rhs) { return lhs[1] < rhs[1]; });

    int arrows = 1;
    int arrow_pos = points[0][1];

    for (int i = 1; i < n; ++i) {
      if (points[i][0] > arrow_pos) {
        ++arrows;
        arrow_pos = points[i][1];
      }
      // Otherwise (points[i][0] <= arrow_pos), the current balloon is burst by
      // the previous arrow, so do nothing and continue.
    }

    return arrows;
  }
};
