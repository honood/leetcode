// HoNooD <honood@gmail.com>
// 2024.06.06 18:37

// 69. Sqrt(x)
// https://leetcode.com/problems/sqrtx/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int mySqrt(int x) {
    assert(x >= 0);

    if (x == 0) {
      return 0;
    }

    int res = 0;
    int low = 1;
    int high = x;
    while (low <= high) {
      // Prevent overflow when calculating `mid` using `(left + right) / 2`
      int mid = low + (high - low) / 2;
      if (mid <= x / mid) { // Prevent overflow of `mid * mid`
        res = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return res;
  }
};

// Newton's Method
// https://en.wikipedia.org/wiki/Newton%27s_method#Use_of_Newton's_method_to_compute_square_roots
//
// Not recommended for algorithm interviews because it is difficult to
// understand and requires mathematical knowledge.
class Solution_2 {
public:
  int mySqrt(int x) {
    if (x == 0) {
      return 0;
    }

    long r = x;
    while (r * r > x) {
      r = (r + x / r) / 2;
    }
    return r;
  }
};
