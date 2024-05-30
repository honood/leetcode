// HoNooD
// 2024.05.30 16:05

// 137. Single Number II
// https://leetcode.com/problems/single-number-ii/description/?envType=study-plan-v2&envId=top-interview-150

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

// nums: [9, 9, 9, 5]
// ones: 0000
// twos: 0000
// 
//  i | nums[i] |  ones  |  twos
// ---|---------|--------|--------
//  0 |   1001  |  1001  |  0000
//  1 |   1001  |  0000  |  1001
//  2 |   1001  |  0000  |  0000
//  3 |   0101  |  0101  |  0000
//
//
// nums: [5, 9, 9, 9]
// ones: 0000
// twos: 0000
// 
//  i | nums[i] |  ones  |  twos
// ---|---------|--------|--------
//  0 |   0101  |  0101  |  0000
//  1 |   1001  |  1100  |  0001
//  2 |   1001  |  0100  |  1000
//  3 |   1001  |  0101  |  0000
//
//
// nums: [9, 5, 9, 9]
// ones: 0000
// twos: 0000
// 
//  i | nums[i] |  ones  |  twos
// ---|---------|--------|--------
//  0 |   1001  |  1001  |  0000
//  1 |   0101  |  1100  |  0001
//  2 |   1001  |  0100  |  1000
//  3 |   1001  |  0101  |  0000
//
//
// nums: [9, 9, 5, 9]
// ones: 0000
// twos: 0000
// 
//  i | nums[i] |  ones  |  twos
// ---|---------|--------|--------
//  0 |   1001  |  1001  |  0000
//  1 |   1001  |  0000  |  1001
//  2 |   0101  |  0100  |  1000
//  3 |   1001  |  0101  |  0000
class Solution {
public:
  int singleNumber(vector<int>& nums) {
    assert(!nums.empty());

    // `ones` stores the bits that have appeared once.
    int ones = 0;
    // `twos` stores the bits that have appeared twice.
    int twos = 0;
    for (auto const& num : nums) {
      // - `ones ^ num`: This performs an XOR operation between `ones` and the 
      // current number `num`, adding new bits from `num` to `ones` or removing 
      // bits that were already present.
      // - `& ~twos`: This ensures that bits that are already in `twos` are 
      // removed from `ones`. If a bit is set in `twos` (meaning it has appeared 
      // twice), it is cleared from `ones`.
      ones = (ones ^ num) & ~twos;
      // - `twos ^ num`: This performs an XOR operation between `twos` and the 
      // current number `num`, adding new bits from `num` to `twos` or removing 
      // bits that were already present.
      // - `& ~ones`: This ensures that bits that are already in `ones` are 
      // removed from `twos`. If a bit is set in `ones` (meaning it has appeared 
      // once), it is cleared from `twos`.
      twos = (twos ^ num) & ~ones;
    }

    // 'ones' contains the bit representation of the single number
    return ones;
  }
};

class Solution_2 {
public:
  int singleNumber(vector<int>& nums) {
    int res = 0;
    int const intWidth = 8 * sizeof(int);
    for (int i = 0; i < intWidth; ++i) {
      int sum = 0;
      for (auto const& num : nums) {
        sum += (num >> i) & 1;
      }
      res |= (sum % 3) << i;
    }

    return res;
  }
};

// Not recommended!
class Solution_3 {
public:
  int singleNumber(vector<int>& nums) {
    assert(!nums.empty());

    std::sort(nums.begin(), nums.end());

    int n = nums.size();
    for (int i = 1; i < n; i += 3) {
      if (nums[i] != nums[i - 1]) {
        return nums[i - 1];
      }
    }

    return nums[n - 1];
  }
};
