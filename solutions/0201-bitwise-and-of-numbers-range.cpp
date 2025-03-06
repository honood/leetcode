// HoNooD <honood@gmail.com>
// 2024.06.06 13:35

// 201. Bitwise AND of Numbers Range
// https://leetcode.com/problems/bitwise-and-of-numbers-range/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Bitwise_operation
// https://en.wikipedia.org/wiki/Bitwise_operations_in_C
// https://en.wikipedia.org/wiki/Two%27s_complement
// https://en.wikipedia.org/wiki/Ones%27_complement
// https://www.ruanyifeng.com/blog/2009/08/twos_complement.html
// https://en.cppreference.com/w/cpp/language/operator_arithmetic#Bitwise_logic_operators
// https://en.cppreference.com/w/cpp/language/operator_arithmetic#Bitwise_shift_operators

// Bitwise XOR Truth Table
//
//  A | B | A ⊕ B
// ---|---|------
//  0 | 0 |   0
//  0 | 1 |   1
//  1 | 0 |   1
//  1 | 1 |   0
//
// Key Properties of Bitwise XOR
//
// 1. x ^ y = y ^ x
// 2. x ^ (y ^ z) = (x ^ y) ^ z
// 3. x ^ 0 = x
// 4. x ^ y ^ y = x
// 5. x ^ x = 0
// 6. x ^ 0xFFFF = ~x
//    Note: `0xFFFF` means that all the bits in your data type need to be set to
//          `1`. The exact number of bits depends on the width of the data type.
// 7. a ^ b = (a | b) & (~a | ~b)
// 8. a ^ b = (a & ~b) | (~a & b)

// Bitwise AND Truth Table
//
//  A | B | A & B
// ---|---|------
//  0 | 0 |   0
//  0 | 1 |   0
//  1 | 0 |   0
//  1 | 1 |   1
//
// Key Properties of Bitwise AND
//
// 1. x & y = y & x
// 2. x & (y & z) = (x & y) & z
// 3. x & 0xFFFF = x
//    Note: `0xFFFF` means that all the bits in your data type need to be set to
//          `1`. The exact number of bits depends on the width of the data type.
// 4. x & 0 = 0
// 5. x & x = x

// Bitwise OR Truth Table
//  A | B | A | B
// ---|---|------
//  0 | 0 |   0
//  0 | 1 |   1
//  1 | 0 |   1
//  1 | 1 |   1
//
// Key Properties of Bitwise OR
//
// 1. x | y = y | x
// 2. x | (y | z) = (x | y) | z
// 3. x | 0 = x
// 4. x | 0xFFFF = 0xFFFF
//    Note: `0xFFFF` means that all the bits in your data type need to be set to
//          `1`. The exact number of bits depends on the width of the data type.
// 5. x | x = x

// Bitwise NOT Truth Table
//
//  A | ~A
// ---|----
//  0 |  1
//  1 |  0
//
// Key Properties of Bitwise NOT
//
// 1. ~(~x) = x

// Others Properties
//
// 1. x | (x & y) = x
// 2. x & (x | y) = x
// 3. ~(x | y) = ~x & ~y
// 4. ~(x & y) = ~x | ~y
// 5. x | (y & z) = (x | y) & (x | z)
// 6. x & (y | z) = (x & y) | (x & z)
// 7. x & (y ^ z) = (x & y) ^ (x & z)
// 8. x + y = (x ^ y) + ((x & y) << 1)
// 9. x - y = ~(~x + y)

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// NOT use!
// Time Limit Exceeded
class Solution {
public:
  int rangeBitwiseAnd(int left, int right) {
    int res = std::numeric_limits<int>::max();
    for (int i = left; i <= right; ++i) {
      res &= i;
    }

    return res;
  }
};

class Solution_2 {
public:
  int rangeBitwiseAnd(int left, int right) {
    int shift = 0;
    while (left < right) {
      left >>= 1;
      right >>= 1;
      ++shift;
    }

    return left << shift;
  }
};
