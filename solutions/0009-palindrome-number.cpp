// HoNooD <honood@gmail.com>
// 2024.06.06 15:20

// 9. Palindrome Number
// https://leetcode.com/problems/palindrome-number/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Palindromic_number

// An integer is a palindrome when it reads the same forward and backward.
// For example, 121 is a palindrome while 123 is not.

// Note: Could you solve it without converting the integer to a string?

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0) {
      return false;
    }

    if (x == 0) {
      return true;
    }

    // When the last digit of the number is 0, the first digit must also be 0
    // (only 0 itself satisfies this property).
    if (x % 10 == 0) {
      return false;
    }

    vector<int> c{};
    while (x > 0) {
      c.emplace_back(x % 10);
      x /= 10;
    }

    for (int l = 0, h = c.size() - 1; l < h; ++l, --h) {
      if (c[l] != c[h]) {
        return false;
      }
    }

    return true;
  }
};

// Recommended
class Solution_2 {
public:
  bool isPalindrome(int x) {
    if (x < 0) {
      return false;
    }

    if (x == 0) {
      return true;
    }

    // When the last digit of the number is 0, the first digit must also be 0
    // (only 0 itself satisfies this property).
    if (x % 10 == 0) {
      return false;
    }

    int revertedNumber = 0;
    while (x > revertedNumber) {
      revertedNumber = revertedNumber * 10 + x % 10;
      x /= 10;
    }

    return (x == revertedNumber ||
            // When the length is an odd number, we can get rid of the middle
            // digit by revertedNumber/10.
            // For example, when the input is 12321, at the end of the loop we
            // get x = 12, revertedNumber = 123, since the middle digit doesn't
            // matter in palidrome (it will always equal to itself), we can
            // simply get rid of it.
            x == revertedNumber / 10);
  }
};
