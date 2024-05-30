// HoNooD
// 2024.05.30 15:12

// 136. Single Number
// https://leetcode.com/problems/single-number/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Bitwise_operation
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
// 1. Commutative Property: A ⊕ B = B ⊕ A
// 2. Associative Property: (A ⊕ B) ⊕ C = A ⊕ (B ⊕ C)
// 3. Identity Property: A ⊕ 0 = A
// 4. Self-inverse Property: A ⊕ A = 0

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
// 1. Commutative Property: A & B = B & A
// 2. Associative Property: (A & B) & C = A & (B & C)
// 3. Identity Property: A & 1 = A
// 4. Zero Property: A & 0 = 0

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
// 1. Commutative Property: A | B = B | A
// 2. Associative Property: (A | B) | C = A | (B | C)
// 3. Identity Property: A | 0 = A
// 4. Domination Property: A | 1 = 1

// Bitwise NOT Truth Table
//
//  A | ~A
// ---|----
//  0 |  1
//  1 |  0
//
// Key Properties of Bitwise NOT
//
// 1. Inversion Property:
//     ~A = 1 if A = 0
//     ~A = 0 if A = 1
// 2. Double Inversion Property: ~~A = A

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int singleNumber(vector<int>& nums) {
    assert(!nums.empty());

    int res = 0;
    for (auto const& num : nums) {
      res ^= num;
    }

    return res;
  }
};
