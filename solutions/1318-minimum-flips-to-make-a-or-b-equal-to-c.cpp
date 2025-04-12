// HoNooD <honood@gmail.com>
// 2025.04.11 15:05
//
// 1318. Minimum Flips to Make a OR b Equal to c
// https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int minFlips(int a, int b, int c) {
    return min_flips_v1(a, b, c);
  }

private:
  // - Time complexity: O(log max(a, b, c))
  // - Space complexity: O(1)
  int min_flips_v1(int a, int b, int c) {
    int flips = 0;

    while (a > 0 || b > 0 || c > 0) {
      int a_lsb = a & 1;
      int b_lsb = b & 1;
      int c_lsb = c & 1;

      // ╔═══════╤═══════╤═══════════════╦═══════╗
      // ║ a_lsb │ b_lsb │ a_lsb | b_lsb ║ c_lsb ║
      // ╠═══════╪═══════╪═══════════════╬═══════╣
      // ║   0   │   0   │       0       ║   1   ║
      // ╟───────┼───────┼───────────────╫───────╢
      // ║   0   │   1   │       1       ║   0   ║
      // ╟───────┼───────┼───────────────╫───────╢
      // ║   1   │   0   │       1       ║   0   ║
      // ╟───────┼───────┼───────────────╫───────╢
      // ║   1   │   1   │       1       ║   0   ║
      // ╚═══════╧═══════╧═══════════════╩═══════╝

      // if ((a_lsb | b_lsb) != c_lsb) {
      //   if (c_lsb == 1) {
      //     ++flips;
      //   } else { // c_lsb == 0
      //     flips += ((a_lsb & b_lsb) == 1) ? 2 : 1;
      //   }
      // }

      if (c_lsb == 0) {
        flips += a_lsb + b_lsb;
      } else { // c_lsb == 1
        if (a_lsb == 0 && b_lsb == 0) {
          flips += 1;
        }
      }

      a >>= 1;
      b >>= 1;
      c >>= 1;
    }

    return flips;
  }

  // - Time complexity: O(1)
  // - Space complexity: O(1)
  int min_flips_v2(int a, int b, int c) {
    int a_or_b = a | b;

    // Count bits where (a OR b) differs from c
    int diff = a_or_b ^ c;

    // Count bits where we need to flip 0 to 1 (when c has 1 but a OR b has 0)
    int flip_to_1 = diff & c;

    // Count bits where we need to flip 1 to 0 (when c has 0 but a OR b has 1)
    // For these positions, we need to check if both a and b have 1
    int flip_to_0 = diff & (~c);

    // Count set bits in flip_to_1 (each requires one flip)
    int count1 = count_set_bits(flip_to_1);

    // For flip_to_0, we need to count how many positions have both a and b set
    // to 1 as those require two flips
    int both_set = a & b & flip_to_0;

    // Count total flips needed for positions where a OR b is 1 but c is 0
    int count0 = count_set_bits(flip_to_0) + count_set_bits(both_set);

    return count0 + count1;
  }

  // Helper function to count set bits in an integer
  // See: solutions/0338-counting-bits.cpp
  int count_set_bits(int n) {
#if __cplusplus >= 202002L && defined(__cpp_lib_bitops)
    // C++20 standard available: use std::popcount
    //   https://en.cppreference.com/w/cpp/numeric/popcount
    return std::popcount(static_cast<unsigned int>(n));
#elif defined(__clang__) || defined(__GNUC__)
    // Clang or GCC compiler detected: use __builtin_popcount
    //   https://clang.llvm.org/docs/LanguageExtensions.html#builtin-popcountg
    return __builtin_popcount(static_cast<unsigned int>(n));
#elif defined(_MSC_VER)
    // Microsoft Visual C++ compiler detected: use __popcnt
    //   https://learn.microsoft.com/en-us/cpp/intrinsics/popcnt16-popcnt-popcnt64
    return __popcnt(static_cast<unsigned int>(n));
#else
    int count = 0;
    while (n > 0) {
      // Brian Kernighan's algorithm
      // https://en.wikipedia.org/wiki/Hamming_weight
      // https://en.wikipedia.org/wiki/Bit_manipulation
      // https://en.wikipedia.org/wiki/Bitwise_operation
      //
      // The operation `n & (n-1)` clears (sets to 0) the rightmost set bit of n
      // For example, if n = 6 (0b110), n-1 = 5 (0b101), n & (n-1) = 4 (0b100)
      n &= n - 1;
      ++count;
    }
    return count;
#endif
  }

  // - Time complexity: O(1)
  // - Space complexity: O(1)
  int min_flips_v3(int a, int b, int c) {
    // Count bits where c is 1 but a|b is 0 (need to flip 0->1)
    int need_to_flip_1 = count_set_bits(~(a | b) & c);

    // Count bits where c is 0 but a|b is 1 (need to flip 1->0)
    // For each position, count if both a and b have 1 (need two flips)
    int need_to_flip_0 = count_set_bits((a | b) & ~c);

    // Add extra flips for positions where both a and b are 1 and c is 0
    int both_one_but_c_zero = count_set_bits(a & b & ~c);

    return need_to_flip_1 + need_to_flip_0 + both_one_but_c_zero;
  }

  // - Time complexity: O(1)
  // - Space complexity: O(1)
  int min_flips_v4(int a, int b, int c) {
    // Flips needed when target bit c_i is 0:
    // Count flips needed for 'a' where a_i=1, c_i=0
    int flips_a_when_c0 = count_set_bits(a & ~c);
    // Count flips needed for 'b' where b_i=1, c_i=0
    int flips_b_when_c0 = count_set_bits(b & ~c);

    // Flips needed when target bit c_i is 1:
    // Count flips needed where c_i=1, but a_i=0 and b_i=0
    int flips_when_c1_a0_b0 = count_set_bits(c & ~(a | b));

    return flips_a_when_c0 + flips_b_when_c0 + flips_when_c1_a0_b0;
  }
};
