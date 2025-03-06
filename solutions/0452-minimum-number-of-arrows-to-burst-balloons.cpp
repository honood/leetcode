// HoNooD <honood@gmail.com>
// 2024.06.12 09:10

// 452. Minimum Number of Arrows to Burst Balloons
// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int findMinArrowShots(vector<vector<int>>& points) {
    int n = points.size();
    if (n < 2) {
      return n;
    }

    std::sort(points.begin(), points.end());

    int res = 1;
    int left = points[0][0];
    int right = points[0][1];
    for (int i = 1; i < n; ++i) {
      if (points[i][0] <= right) {
        left = std::max(left, points[i][0]);
        right = std::min(right, points[i][1]);
      } else {
        ++res;

        left = points[i][0];
        right = points[i][1];
      }
    }

    return res;
  }
};

// More concise and straightforward
class Solution_2 {
public:
  int findMinArrowShots(vector<vector<int>>& points) {
    int n = points.size();
    if (n <= 1) {
      return n;
    }

    std::sort(points.begin(), points.end(), [](auto const& l, auto const& r) {
      return l[1] < r[1];
    });

    int arrows = 1;
    int end = points[0][1];
    for (int i = 1; i < n; ++i) {
      if (points[i][0] > end) {
        ++arrows;
        end = points[i][1];
      }
    }

    return arrows;
  }
};
