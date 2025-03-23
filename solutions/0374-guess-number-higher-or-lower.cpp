// HoNooD <honood@gmail.com>
// 2025.03.23 15:00

// 374. Guess Number Higher or Lower
// https://leetcode.com/problems/guess-number-higher-or-lower/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return       -1 if num is higher than the picked number
 *                1 if num is lower than the picked number
 *                0 if num is equal to the picked number
 * int guess(int num);
 */

class Solution {
public:
  int guessNumber(int n) {
    return guess_number_v2(n);
  }

public:
  // Time Limit Exceeded
  //
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int guess_number_v1(int n) {
    for (int i = 1; i <= n; ++i) {
      if (guess(i) == 0) {
        return i;
      }
    }

    throw std::runtime_error("Unreachable code reached!");
    return -1;
  }

  // https://en.wikipedia.org/wiki/Binary_search
  //
  // - Time complexity: O(log(n))
  // - Space complexity: O(1)
  int guess_number_v2(int n) {
    int left = 1;
    int right = n;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int result = guess(mid);
      if (0 == result) {
        return mid;
      } else if (-1 == result) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }

    throw std::runtime_error("Unreachable code reached!");
    return -1;
  }

  // https://en.wikipedia.org/wiki/Binary_search
  //
  // - Time complexity: O(log(n))
  // - Space complexity: O(log(n))
  int guess_number_v3(int n) {
    std::function<int(int, int)> binary_search
        = [&binary_search](int left, int right) {
            if (left > right) {
              throw std::runtime_error("Unreachable code reached!");
              return -1;
            }

            int mid = left + (right - left) / 2;
            int result = guess(mid);
            if (result == 0) {
              return mid;
            } else if (result == -1) {
              return binary_search(left, mid - 1);
            } else {
              return binary_search(mid + 1, right);
            }
          };

    return binary_search(1, n);
  }

  // https://en.wikipedia.org/wiki/Ternary_search
  //
  // - Time complexity: O(log(n))
  // - Space complexity: O(1)
  int guess_number_v4(int n) {
    int left = 1;
    int right = n;
    while (left <= right) {
      int mid1 = left + (right - left) / 3;
      int mid2 = right - (right - left) / 3;

      int result1 = guess(mid1);
      int result2 = guess(mid2);

      if (result1 == 0) {
        return mid1;
      }

      if (result2 == 0) {
        return mid2;
      }

      if (result1 == -1) {
        right = mid1 - 1;
      } else if (result2 == 1) {
        left = mid2 + 1;
      } else {
        left = mid1 + 1;
        right = mid2 - 1;
      }
    }

    throw std::runtime_error("Unreachable code reached!");
    return -1;
  }
};
