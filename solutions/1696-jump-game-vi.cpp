// HoNooD <honood@gmail.com>
// 2024.07.28 19:55

// 1696. Jump Game VI
// https://leetcode.com/problems/jump-game-vi/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int maxResult(vector<int>& nums, int k) {
    return max_result_v4(nums, k);
  }

private:
  // DFS
  // https://leetcode.com/tag/depth-first-search/
  // Memoization
  // https://leetcode.com/tag/memoization/
  //
  // - Time complexity: O(n*k)
  // - Space complexity: O(n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int max_result_v1(vector<int> const& nums, int k) {
    if (nums.empty()) {
      return std::numeric_limits<int>::min();
    }

    int n = nums.size();
    if (k <= 0 || n == 1) {
      return nums[0];
    }

    vector<int> memo(n, -1);
    return dfs(nums, k, 0, memo);
  }

  int dfs(vector<int> const& nums, int const& k, int i, vector<int>& memo) {
    int n = nums.size();
    if (i == n - 1) {
      return nums[n - 1];
    }

    if (memo[i] != -1) {
      return memo[i];
    }

    int max_score = std::numeric_limits<int>::min();
    for (int j = 1; j <= k && i + j < n; ++j) {
      max_score = std::max(max_score, nums[i] + dfs(nums, k, i + j, memo));
    }

    memo[i] = max_score;
    return max_score;
  }

  // BFS
  // https://leetcode.com/tag/breadth-first-search/
  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // - Time complexity: O(n*k)
  // - Space complexity: O(n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  int max_result_v2(vector<int> const& nums, int k) {
    if (nums.empty()) {
      return std::numeric_limits<int>::min();
    }

    int n = nums.size();
    if (k <= 0 || n == 1) {
      return nums[0];
    }

    // `dp[i]` represents the maximum score achievable from the start of the
    // array (index 0) to the current position `i`
    vector<int> dp(n, std::numeric_limits<int>::min());
    dp[0] = nums[0];

    queue<int> queue{};
    queue.emplace(0);

    while (!queue.empty()) {
      int i = queue.front();
      queue.pop();

      // explore all reachable positions from `i` within `k` steps
      for (int j = 1; j <= k && i + j < n; ++j) {
        if (int temp = dp[i] + nums[i + j]; temp > dp[i + j]) {
          dp[i + j] = temp;
          queue.emplace(i + j);
        }
      }
    }

    return dp[n - 1];
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  // Heap (Priority Queue)
  // https://leetcode.com/tag/heap-priority-queue/
  //
  // - Time complexity: O(n*log(k))
  // - Space complexity: O(n)
  int max_result_v3(vector<int> const& nums, int k) {
    if (nums.empty()) {
      return std::numeric_limits<int>::min();
    }

    int n = nums.size();
    if (k <= 0 || n == 1) {
      return nums[0];
    }

    // `dp[i]` represents the maximum score achievable from the start of the
    // array (index 0) to the current position `i`
    vector<int> dp(n);
    dp[0] = nums[0];

    auto less = [](pair<int, int> const& left, pair<int, int> const& right) {
      return left.first < right.first;
    };
    // store pairs of (dp value, index)
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(less)> max_heap{less};
    max_heap.emplace(dp[0], 0);

    for (int i = 1; i < n; ++i) {
      // remove elements not within the window
      while (!max_heap.empty() && max_heap.top().second < i - k) {
        max_heap.pop();
      }

      // update `dp[i]` with the maximum value within the window
      dp[i] = nums[i] + max_heap.top().first;

      max_heap.emplace(dp[i], i);
    }

    return dp[n - 1];
  }

  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  // Monotonic (Decreasing) Queue
  // https://leetcode.com/tag/monotonic-queue/
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int max_result_v4(vector<int> const& nums, int k) {
    if (nums.empty()) {
      return std::numeric_limits<int>::min();
    }

    int n = nums.size();
    if (k <= 0 || n == 1) {
      return nums[0];
    }

    // `dp[i]` represents the maximum score achievable from the start of the
    // array (index 0) to the current position `i`
    vector<int> dp(n);
    dp[0] = nums[0];

    // store the indices of elements in the window
    deque<int> deque{};
    deque.emplace_back(0);

    for (int i = 1; i < n; ++i) {
      if (deque.front() < i - k) {
        deque.pop_front();
      }

      // update `dp[i]` with the maximum value within the window
      dp[i] = nums[i] + dp[deque.front()];

      // maintain deque in strictly decreasing order
      while (!deque.empty() && dp[i] >= dp[deque.back()]) {
        deque.pop_back();
      }

      deque.emplace_back(i);
    }

    return dp[n - 1];
  }
};
