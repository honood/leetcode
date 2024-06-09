// HoNooD <honood@gmail.com>
// 2024.06.07 11:17

// 149. Max Points on a Line
// https://leetcode.com/problems/max-points-on-a-line/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// https://en.wikipedia.org/wiki/Slope
class Solution {
public:
  int maxPoints(vector<vector<int>>& points) {
    int n = points.size();
    if (n < 3) {
      return n;
    }

    int maxCount = 0;
    for (int i = 0; i < n - 1; ++i) {
      unordered_map<string, int> slopeCount{};
      int duplicate = 1; // 1 means the base point itself
      int currMax = 0;
      for (int j = i + 1; j < n; ++j) {
        int dx = points[j][0] - points[i][0];
        int dy = points[j][1] - points[i][1];
        if (dx == 0 && dy == 0) {
          ++duplicate;
          continue;
        }

        string slope{};
        if (dx == 0) {
          // vertical line
          slope = "1/0";
        } else if (dy == 0) {
          // horizontal line
          slope = "0/1";
        } else {
          int gcd = findGCD(dx, dy);
          dx /= gcd;
          dy /= gcd;

          if (dx < 0) {
            dx = -dx;
            dy = -dy;
          }

          slope = std::to_string(dy) + '/' + std::to_string(dx);
        }

        ++slopeCount[slope];
        currMax = std::max(currMax, slopeCount[slope]);
      }

      maxCount = std::max(maxCount, currMax + duplicate);
    }

    return maxCount;
  }

private:
  // https://en.wikipedia.org/wiki/Greatest_common_divisor
  // https://en.wikipedia.org/wiki/Least_common_multiple
  /*
  int findGCD(int a, int b) {
    return b == 0 ? a : findGCD(b, a % b);
  }
  */
  int findGCD(int a, int b) {
    while (b != 0) {
      int temp = b;
      b = a % b;
      a = temp;
    }

    return a;
  }
};
