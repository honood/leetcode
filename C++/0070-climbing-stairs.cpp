// HoNooD <honood@gmail.com>
// 2024.07.03 20:38

// 70. Climbing Stairs
// https://leetcode.com/problems/climbing-stairs/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int climbStairs(int n) {
    assert(n >= 0);
    if (n <= 1) {
      return 1;
    }

    int prev1 = 1;
    int prev2 = 1;

    for (int i = 2; i <= n; ++i) {
      int curr = prev1 + prev2;
      prev1 = prev2;
      prev2 = curr;
    }

    return prev2;
  }
};

class Solution_2 {
public:
  int climbStairs(int n) {
    assert(n >= 0);
    // if the number of stairs is less than or equal to 1, there's only one way
    // to climb
    if (n <= 1) {
      return 1;
    }

    // create a vector to store the number of ways to reach each step
    vector<int> dp(n + 1);
    // there is 1 way to stay at step 0 and 1 way to reach step 1
    dp[0] = 1;
    dp[1] = 1;

    // calculate the number of ways to reach each subsequent step
    for (int i = 2; i <= n; ++i) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
  }
};

// maybe TLE (Time Limit Exceeded)
class Solution_3 {
public:
  int climbStairs(int n) {
    assert(n >= 0);
    if (n <= 1) {
      return 1;
    }

    return climbStairs(n - 1) + climbStairs(n - 2);
  }
};
