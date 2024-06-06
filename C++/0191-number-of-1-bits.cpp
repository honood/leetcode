// HoNooD <honood@gmail.com>
// 2024.06.06 13:03

// 191. Number of 1 Bits
// https://leetcode.com/problems/number-of-1-bits/?envType=study-plan-v2&envId=top-interview-150

// A set bit refers to a bit in the binary representation of a number that has a value of 1.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // https://en.wikipedia.org/wiki/Hamming_weight
  int hammingWeight(int n) {
    assert(n > 0);

    int res = 0;
    for (int i = 0; i < std::numeric_limits<int>::digits; ++i) {
      // Parentheses are not needed as `>>` has higher precedence than `&`.
      res += (n >> i) & 1;
    }

    return res;
  }
};
