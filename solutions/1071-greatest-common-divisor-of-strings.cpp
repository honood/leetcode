// HoNooD <honood@gmail.com>
// 2025.02.19 14:13

// 1071. Greatest Common Divisor of Strings
// https://leetcode.com/problems/greatest-common-divisor-of-strings/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  string gcdOfStrings(string s, string t) {
    // 如果存在字符串 x, 使得：
    //   s = x * m
    //   t = x * n
    // 那么：
    //   s + t = x * (m + n)
    //   t + s = x * (n + m)
    // 即：
    //   s + t == t + s
    //
    // 所以：
    //   如果 s + t != t + s，则不存在这样的 x。
    if (s + t != t + s) {
      return "";
    }

    int len = gcd(s.size(), t.size()); // or C++17 `std::gcd`
    return s.substr(0, len);
  }

private:
  // https://en.wikipedia.org/wiki/Euclidean_algorithm
  // https://en.wikipedia.org/wiki/Greatest_common_divisor
  // https://en.wikipedia.org/wiki/Least_common_multiple
  int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
  }

  int lcm(int a, int b) {
    return a * b / gcd(a, b);
  }
};
