// HoNooD <honood@gmail.com>
// 2024.05.30 15:12
// 2025.04.11 14:30

// 136. Single Number
// https://leetcode.com/problems/single-number/description/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/single-number/?envType=study-plan-v2&envId=leetcode-75

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

#include <cinttypes>
#include <functional>
auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int singleNumber(vector<int>& nums) {
    return single_number_v1(nums);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int single_number_v1(vector<int> const& nums) {
    assert(!nums.empty());

    int result = 0;
    for (int num : nums) {
      result ^= num;
    }
    return result;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int single_number_v2(vector<int> const& nums) {
    assert(!nums.empty());
    return std::reduce(nums.cbegin(), nums.cend(), 0, std::bit_xor<>{});
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int single_number_v3(vector<int> const& nums) {
    assert(!nums.empty());

    unordered_map<int, int> counts{};
    for (int num : nums) {
      ++counts[num];
    }

    for (auto const& [num, count] : counts) {
      if (count == 1) {
        return num;
      }
    }

    return -1;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int single_number_v4(vector<int> const& nums) {
    assert(!nums.empty());

    unordered_set<int> uniq_nums{};
    long long sum_all = 0;
    for (int num : nums) {
      uniq_nums.emplace(num);
      sum_all += num;
    }

    long long sum_uniq = 0;
    for (int num : uniq_nums) {
      sum_uniq += num;
    }

    return sum_uniq * 2 - sum_all;
  }

  // - Time complexity: O(n * log(n))
  // - Space complexity: O(1)
  int single_number_v5(vector<int>& nums) {
    assert(!nums.empty());

    std::sort(nums.begin(), nums.end());

    for (int i = 0, n = nums.size(); i < n; i += 2) {
      if (i == n - 1 || nums[i] != nums[i + 1]) {
        return nums[i];
      }
    }

    return -1;
  }
};
