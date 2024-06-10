// HoNooD <honood@gmail.com>
// 2024.06.10 12:57

// 202. Happy Number
// https://leetcode.com/problems/happy-number/?envType=study-plan-v2&envId=top-interview-150

// A happy number is a number defined by the following process:
// 1. Starting with any positive integer, replace the number by the sum of the
// squares of its digits.
// 2. Repeat the process until the number equals 1 (where it will stay), or it
// loops endlessly in a cycle which does not include 1.
// 3. Those numbers for which this process ends in 1 are happy.

class Solution {
public:
  bool isHappy(int n) {
    if (n <= 0) {
      return false;
    }

    if (n == 1) {
      return true;
    }

    unordered_set<int> seen{};
    while (n != 1 && !seen.contains(n)) {
      seen.emplace(n);
      n = sumOfSquares(n);
    }

    return n == 1;
  }

private:
  int sumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
      int digit = n % 10;
      sum += digit * digit;

      n /= 10;
    }

    return sum;
  }
};
