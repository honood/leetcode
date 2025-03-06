// HoNooD <honood@gmail.com>
// 2024.06.07 23:17

// 2280. Minimum Lines to Represent a Line Chart
// https://leetcode.com/problems/minimum-lines-to-represent-a-line-chart/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// https://en.wikipedia.org/wiki/Slope
class Solution {
public:
  int minimumLines(vector<vector<int>>& stockPrices) {
    int n = stockPrices.size();
    if (n < 2) {
      return 0;
    }

    std::sort(stockPrices.begin(), stockPrices.end(), [](vector<int> const& l, vector<int> const& r) {
      return l[0] < r[0];
    });

    int res = 0;
    pair<int, int> prevSlope{0, 0};
    for (int i = 0; i < n - 1; ++i) {
      int dx = stockPrices[i + 1][0] - stockPrices[i][0];
      int dy = stockPrices[i + 1][1] - stockPrices[i][1];
      if (dx == 0 && dy == 0) {
        continue;
      }

      if (dx == 0) {
        dy = 1;
      } else if (dy == 0) {
        dx = 1;
      } else {
        int gcd = findGCD(dx, dy);
        dx /= gcd;
        dy /= gcd;

        if (dx < 0) {
          dx = -dx;
          dy = -dy;
        }
      }

      pair<int, int> currSlope{dx, dy};
      if (currSlope != prevSlope) {
        ++res;
        prevSlope = currSlope;
      }
    }

    return res;
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
