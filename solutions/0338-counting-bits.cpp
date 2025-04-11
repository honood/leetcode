// HoNooD <honood@gmail.com>
// 2025.04.10 14:35
//
// 338. Counting Bits
// https://leetcode.com/problems/counting-bits/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<int> countBits(int n) {
    return count_bits_v3(n);
  }

private:
  // - Time complexity: O(n * log(n))
  //
  // clang-format off
  // Total Time complexity calculation:
  // 1. Outer Loop:
  //    - Runs n+1 times (from i=0 to n).
  //
  // 2. Inner Loop Work (for a given i):
  //    - Dominated by the while loop processing bits.
  //    - Let work(i) be the number of operations for the inner loop.
  //    - work(i) is proportional to the number of bits in i, which is roughly log₂(i).
  //      - Let k is the number of bits required to represent 'i'.
  //      - We know that k satisfies 2^(k-1) <= i < 2^k (for i > 0).
  //      - Taking log base 2: k - 1 <= log₂(i) < k.
  //      - This implies k is approximately log₂(i).
  //    - Therefore:
  //      - work(i) = O(log i) for i >= 1.
  //      - work(0) = O(1).
  //    - Implication: There exists a constant 'c' such that work(i) <= c * log i for i >= 2
  //      (and work(0), work(1) are bounded by some constant C').
  //
  // 3. Total Time T(n) - Summation:
  //    - T(n) is the sum of work for each i from 0 to n:
  //      T(n) = work(0) + work(1) + work(2) + ... + work(n)
  //    - Using the bounds from step 2:
  //      T(n) <= C' + c * log 2 + ... + c * log n
  //           <= C' + c * (log 1 + log 2 + ... + log n)  // Adding c*log 1 = 0
  //           <= C' + c * Sum_{i=1 to n} log i
  //
  // 4. Analyzing the Sum S = Sum_{i=1 to n} log i:
  //    - This sum is log(1) + log(2) + ... + log(n) = log(n!).
  //    - Estimating the size of S:
  //      * Upper bound:
  //        - Each term log i <= log n.
  //        - n terms total.
  //        - Result: S <= n * log n.
  //      * Lower bound:
  //        - Consider terms from i=n/2 to n (at least n/2 terms).
  //        - Each term log i >= log(n/2) = log n - 1.
  //        - Result: S >= (n/2) * (log n - 1) = (1/2)n log n - n/2.
  //      * Conclusion from bounds: Since S <= O(n log n) and S >= Ω(n log n), we have S = Θ(n log n).
  //    - Alternative estimations confirming Θ(n log n):
  //      * Stirling's approximation: log(n!) ≈ n log n - n log e + O(log n). Dominant term is n log n.
  //        - Stirling's approximation (斯特林近似，Stirling's formula, 斯特林公式)
  //          https://en.wikipedia.org/wiki/Stirling%27s_approximation
  //      * Integral approximation: ∫ log x dx ≈ x log x. Integral from 1 to n gives ≈ n log n.
  //
  // 5. Final Complexity Derivation:
  //    - We have S = Sum_{i=1 to n} log i = Θ(n log n), which implies S = O(n log n).
  //    - We established T(n) <= C' + c * S.
  //    - So, T(n) <= C' + c * O(n log n).
  //    - This means T(n) is bounded above by a constant plus a constant times n log n.
  //    - Therefore, T(n) = O(n log n).
  //
  // Hence, the overall time complexity is O(n log n).
  // clang-format on

  // - Space complexity: O(1)
  vector<int> count_bits_v1(int n) {
    assert(n >= 0);
    vector<int> result(n + 1);

    for (int i = 0; i <= n; ++i) {
      int count = 0;
      int num = i;

      // Count bits for each number
      while (num > 0) {
        count += num & 0x1; // Check if least significant bit is 1
        num >>= 1;
      }

      result[i] = count;
    }

    return result;
  }

  // Complexity Analysis:
  // - Time complexity: O(n * k), where k is the cost of the __builtin_popcount
  // operation for a single number.
  //   Since this often maps to a highly optimized hardware instruction, k is
  //   effectively O(1) for standard integer types. Therefore, the overall time
  //   complexity is typically considered O(n).
  // - Space complexity: O(n) - Primarily for the output vector `result` which
  // stores n+1 elements.
  //   The auxiliary space (memory used besides the input and output) is O(1).
  vector<int> count_bits_v2(int n) {
    assert(n >= 0);
    vector<int> result(n + 1);

    for (int i = 0; i <= n; ++i) {
#if __cplusplus >= 202002L
      // C++20 standard available: use std::popcount
      //   https://en.cppreference.com/w/cpp/numeric/popcount
      // It operates on unsigned types, so cast i.
      result[i] = std::popcount(static_cast<unsigned int>(i));
#elif defined(__clang__) || defined(__GNUC__)
      // Clang or GCC compiler detected: use __builtin_popcount
      //   https://clang.llvm.org/docs/LanguageExtensions.html#builtin-popcountg
      // It also typically operates on unsigned int.
      result[i] = __builtin_popcount(static_cast<unsigned int>(i));
#elif defined(_MSC_VER)
      // Microsoft Visual C++ compiler detected: use __popcnt
      //   https://learn.microsoft.com/en-us/cpp/intrinsics/popcnt16-popcnt-popcnt64
      // __popcnt operates on 32-bit unsigned int.
      // For 64-bit, use __popcnt64(static_cast<unsigned __int64>(i)) if needed,
      // but for standard int likely fitting in 32 bits, __popcnt is fine.
      result[i] = __popcnt(static_cast<unsigned int>(i));
#else
      // No known efficient intrinsic found - generate a compile-time error.
      // Alternatively, you could implement a software fallback here,
      // like the O(log i) loop, but it would be less efficient.
      static_assert(
        false,
        "No efficient popcount intrinsic found for this compiler/standard "
        "combination. Please add support or use C++20/GCC/Clang/MSVC.");
#endif
    }

    return result;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  vector<int> count_bits_v3(int n) {
    assert(n >= 0);
    vector<int> result(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
      // result[i] = result[i / 2] + (i % 2);
      //
      // Note: Using bitwise operators is slightly more efficient
      // result[i >> 1] gives the count for number i without its last bit
      // (i & 1) checks if the last bit is 1 (odd number) or 0 (even number)
      result[i] = result[i >> 1] + (i & 0x1);
    }

    return result;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  vector<int> count_bits_v4(int n) {
    assert(n >= 0);
    vector<int> result(n + 1, 0);
    int highest_bit = 0;

    for (int i = 1; i <= n; ++i) {
      // Check if i is a power of 2
      //
      // 1 = 2^0: 0b1 & (0b1 - 1) = 0b1 & 0b0 = 0
      // 8 = 2^3: 0b1000 & (0b1000 - 1) = 0b1000 & 0b0111 = 0
      if ((i & (i - 1)) == 0) {
        highest_bit = i;
      }
      result[i] = result[i - highest_bit] + 1;
    }

    return result;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  vector<int> count_bits_v5(int n) {
    assert(n >= 0);
    vector<int> result(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
      // The operation `i & (i-1)` clears (sets to 0) the rightmost set bit of
      // i. For example, if i = 6 (0b110), i-1 = 5 (0b101), i & (i-1) = 4
      // (0b100)
      //
      // The number of set bits in i is exactly one more that the number of set
      // bits in `i & (i-1)`.
      result[i] = result[i & (i - 1)] + 1;
    }

    return result;
  }
};
