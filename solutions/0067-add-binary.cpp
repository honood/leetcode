// HoNooD
// 2024.06.05 22:03

// 67. Add Binary
// https://leetcode.com/problems/add-binary/?envType=study-plan-v2&envId=top-interview-150

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

class Solution {
public:
  string addBinary(string a, string b) {
    // DO NOT use list initialization (uniform initialization, braced
    // initialization) syntax here:
    //
    // string sum{std::max(a.size(), b.size()) + 1, '0'};
    //
    string sum(std::max(a.size(), b.size()) + 1, '0');

    for (int i = a.size() - 1, j = b.size() - 1, k = sum.size() - 1;
         i >= 0 || j >= 0;
         --i, --j, --k) {
      char left = i < 0 ? '0' : a[i];
      char right = j < 0 ? '0' : b[j];
      char carry = sum[k];
      auto [x, y] = addBinary(left, right, carry);
      sum[k] = y;
      sum[k - 1] = x;
    }

    if (sum[0] == '0') {
      return sum.substr(1, sum.size() - 1);
    }

    return sum;
  }

private:
  pair<char, char> addBinary(char a, char b, char c)  {
    auto [x, y] = addBinary(a, b);
    if (x == '0') {
      return addBinary(y, c);
    }

    assert(x == '1' && y == '0');
    return {x, c};
  }

  pair<char, char> addBinary(char a, char b) {
    if (a != b) {
      return {'0', '1'};
    }

    if (a == '0') {
      return {'0', '0'};
    }

    return {'1', '0'};
  }
};

class Solution_2 {
public:
  string addBinary(string a, string b) {
    string res{};
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry != 0) {
      int sum = carry;
      if (i >= 0) {
        sum += a[i] - '0';
        --i;
      }
      if (j >= 0) {
        sum += b[j] - '0';
        --j;
      }

      res = static_cast<char>(sum % 2 + '0') + res;
      carry = sum / 2;
    }

    return res;
  }
};
