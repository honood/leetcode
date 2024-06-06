// HoNooD <honood@gmail.com>
// 2024.06.06 21:12

// 50. Pow(x, n)
// https://leetcode.com/problems/powx-n/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Do not use, TLE (Time Limit Exceeded)!
class Solution {
public:
  double myPow(double x, int n) {
    if (n == 0) {
      return 1.0;
    }

    bool negative = n < 0;
    if (negative) {
      n = -n;
    }

    double res = 1.0;
    while (n-- > 0) {
      res *= x;
    }

    return negative ? 1.0 / res : res;
  }
};

// Exponentiation by Squaring
// https://en.wikipedia.org/wiki/Exponentiation_by_squaring
//
// Note: more readable and intuitive
class Solution_2 {
public:
  double myPow(double x, int n) {
    // Use long long to store n to avoid overflow issues when n is a large
    // negative number
    // On Apple M3 Max: INT_MIN = -2147483648, INT_MAX = 2147483647
    long long N = n;
    if (N < 0) {
      N = -N;
      x = 1.0 / x;
    }

    return impl(x, N);
  }

private:
  double impl(double x, long long n) {
    if (n == 0) {
      return 1.0;
    }

    double half = impl(x, n / 2);
    if ((n & 1) == 0) {
      return half * half;
    }

    return x * half * half;
  }
};

// Exponentiation by Squaring
// https://en.wikipedia.org/wiki/Exponentiation_by_squaring
class Solution_3 {
public:
  double myPow(double x, int n) {
    if (n == 0) {
      return 1.0;
    }

    // Use long long to store n to avoid overflow issues when n is a large
    // negative number
    // On Apple M3 Max: INT_MIN = -2147483648, INT_MAX = 2147483647
    long long N = n;
    if (N < 0) {
      // x != 0
      assert(std::fabs(x) > std::numeric_limits<double>::epsilon());

      N = -N;
      x = 1.0 / x;
    }

    if (N == 1) {
      return x;
    }

    double res = 1.0;
    double curr_prod = x;
    while (N > 0) {
      if ((N & 1) == 1) {
        res *= curr_prod;
      }

      curr_prod *= curr_prod;
      N >>= 1; // divide N by 2
    }

    return res;
  }
};
