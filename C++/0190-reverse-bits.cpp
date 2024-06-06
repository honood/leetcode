// HoNooD <honood@gmail.com>
// 2024.06.06 11:10

// 190. Reverse Bits
// https://leetcode.com/problems/reverse-bits/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < std::numeric_limits<uint32_t>::digits; ++i) {
      res = (res << 1) | ((n >> i) & 1);
      //                  ^      ^
      // Note: Parentheses are not needed as `>>` has higher precedence than `&`.
    }

    return res;
  }
};
