// HoNooD <honood@gmail.com>
// 2024.06.07 08:57

// 172. Factorial Trailing Zeroes
// https://leetcode.com/problems/factorial-trailing-zeroes/?envType=study-plan-v2&envId=top-interview-150

// Note: Could you write a solution that works in logarithmic time complexity?

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// To solve the problem of counting trailing zeroes in a factorial, we need to
// understand where these zeroes come from. Trailing zeroes are produced by
// factors of 10 in the number. Each 10 is a product of 2 and 5. Therefore, the
// number of trailing zeroes is determined by the number of such factor pairs in
// the factorial.
//
// In any factorial `n!`, the number of times 2 is a factor is generally much
// higher than the number of times 5 is a factor. This is because every second
// number is divisible by 2, but only every fifth number is divisible by 5.
// Hence, the number of trailing zeroes is determined by the number of times
// 5 is a factor in the numbers from 1 to `n`.
//
// To find the number of trailing zeroes:
// 1. Count the multiples of 5 up to `n`: Each multiple contributes at least one
// factor of 5.
// 2. Count the multiples of 25 up to `n`: Each multiple of 25 contributes an
// extra factor of 5 (since 25 = 5 * 5).
// 3. Continue this for higher powers of 5: Include multiples of 125, 625, etc.,
// up to the maximum power of 5 less than or equal to `n`.
//
// This approach ensures we count every instance where 5 is a factor in the
// factorial.
class Solution {
public:
  int trailingZeroes(int n) {
    int count = 0;
    while (n > 0) {
      n /= 5;
      count += n;
    }

    return count;
  }
};
