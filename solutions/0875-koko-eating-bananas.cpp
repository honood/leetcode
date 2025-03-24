// HoNooD <honood@gmail.com>
// 2025.03.24 09:00

// 875. Koko Eating Bananas
// https://leetcode.com/problems/koko-eating-bananas/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // Constraints:
  //   1. 1 <= piles.length <= 10^4
  //   2. piles.length <= h <= 10^9
  //   3. 1 <= piles[i] <= 10^9
  int minEatingSpeed(vector<int>& piles, int h) {
    return min_eating_speed_v3(piles, h);
  }

private:
  // Time Limit Exceeded
  //
  // - Time complexity: (max(piles) * n)
  // - Space complexity: O(1)
  int min_eating_speed_v1(vector<int> const& piles, int h) {
    int n = piles.size();
    assert(n > 0 && h >= n);

    int max_pile = *std::max_element(piles.cbegin(), piles.cend());

    for (int speed = 1; speed <= max_pile; ++speed) {
      long long total_hours = 0;
      for (int pile : piles) {
        total_hours += (pile + speed - 1) / speed;
      }

      if (total_hours <= h) {
        return speed;
      }
    }

    throw std::runtime_error("Unreachable code reached!");
    return max_pile;
  }

  // - Time complexity: (n * log(max(piles)))
  // - Space complexity: O(1)
  int min_eating_speed_v2(vector<int> const& piles, int h) {
    int n = piles.size();
    assert(n > 0 && h >= n);

    int left = 1;
    int right = *std::max_element(piles.cbegin(), piles.cend());

    while (left < right) {
      int mid = left + (right - left) / 2;

      long long total_hours = 0;
      for (int pile : piles) {
        // Ceiling division
        total_hours += (pile + mid - 1) / mid;
      }

      if (total_hours <= h) {
        right = mid;
      } else {
        left = mid + 1;
      }

      // Incorrect implementation: Early return when total_hours == h
      // Fails for test case: piles = [3,6,7,11], h = 8 (returns 5 instead of 4)
      /*
      if (total_hours == h) {
        return mid;
      } else if (total_hours < h) {
        right = mid;
      } else {
        left = mid + 1;
      }
      */

      // Incorrect implementation: Narrowing search range incorrectly
      // Fails for test case: piles = [10], h = 9 (returns 1 instead of 2)
      /*
      if (total_hours == h) {
        return mid;
      } else if (total_hours < h) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
      */
    }

    return left;
  }

  // - Time complexity: (n * log(max(piles)))
  // - Space complexity: O(1)
  int min_eating_speed_v3(vector<int> const& piles, int h) {
    int n = piles.size();
    assert(n > 0 && h >= n);

    int max_pile = *std::max_element(piles.cbegin(), piles.cend());
    if (h == n) {
      return max_pile;
    }

    // Note: Use the overloaded version of `reduce` with `0ll` (`long long`) as
    // the initial value to prevent integer overflow when summing large arrays
    long long total_bananas = std::reduce(piles.cbegin(), piles.cend(), 0ll);
    // Ceiling division
    int lower_bound_speed = (total_bananas + h - 1) / h;

    int left = lower_bound_speed;
    int right = max_pile;

    while (left < right) {
      int mid = left + (right - left) / 2;

      long long total_hours = 0;
      for (int pile : piles) {
        total_hours += (pile + mid - 1) / mid;
        if (total_hours > h) {
          break;
        }
      }

      if (total_hours <= h) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};
