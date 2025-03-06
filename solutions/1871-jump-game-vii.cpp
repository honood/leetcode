// HoNooD <honood@gmail.com>
// 2024.07.29 11:08

// 1871. Jump Game VII
// https://leetcode.com/problems/jump-game-vii/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool canReach(string s, int min_jump, int max_jump) {
    return can_reach_v4(s, min_jump, max_jump);
  }

private:
  // DFS (recursive)
  // https://leetcode.com/tag/depth-first-search/
  // Memoization
  // https://leetcode.com/tag/memoization/
  //
  // - Time complexity: O(n * (max_jump - min_jump + 1))
  // - Space complexity: O(n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  bool can_reach_v1(string const& s, int min_jump, int max_jump) {
    if (s.empty()) {
      return false;
    }

    int n = s.size();
    if (s[n - 1] != '0') {
      return false;
    }

    if (n == 1) {
      return true;
    }

    if (max_jump <= 0) {
      return false;
    }

    vector<int> memo(n, -1);
    return dfs(s, min_jump, max_jump, 0, memo);
  }

  bool dfs(string const& s, int const& min_jump, int const& max_jump, int i, vector<int>& memo) {
    if (i == s.size() - 1) {
      return true;
    }

    if (memo[i] != -1) {
      return memo[i] == 1 ? true : false;
    }

    for (int j = min_jump; j <= max_jump && i + j < s.size(); ++j) {
      if (s[i + j] == '0' && dfs(s, min_jump, max_jump, i + j, memo)) {
        memo[i] = 1;
        return true;
      }
    }

    memo[i] = 0;
    return false;
  }

  /*
  // Similar to the `can_reach_v1` implementation
  bool can_reach_v1_2(string const& s, int min_jump, int max_jump) {
    if (s.empty()) {
      return false;
    }

    int n = s.size();
    if (s[n - 1] != '0') {
      return false;
    }

    if (n == 1) {
      return true;
    }

    if (max_jump <= 0) {
      return false;
    }

    vector<bool> visited(n, false);
    return dfs(s, 0, min_jump, max_jump, visited);
  }

  bool dfs(string const& s, int index, int const& min_jump, int const& max_jump, vector<bool>& visited) {
    int n = s.size();
    if (index == n - 1) {
      return true;
    }

    visited[index] = true;

    for (int i = index + min_jump; i <= std::min(index + max_jump, n - 1); ++i) {
      if (s[i] == '0' && !visited[i]) {
        if (dfs(s, i, min_jump, max_jump, visited)) {
          return true;
        }
      }
    }

    return false;
  }
  */

  // DFS (iterative)
  // https://leetcode.com/tag/breadth-first-search/
  //
  // - Time complexity: O(n * (max_jump - min_jump + 1))
  // - Space complexity: O(n)
  //
  // Note: result in Time Limit Exceeded (TLE)
  bool can_reach_v2(string const& s, int min_jump, int max_jump) {
    if (s.empty()) {
      return false;
    }

    int n = s.size();
    if (s[n - 1] != '0') {
      return false;
    }

    if (n == 1) {
      return true;
    }

    if (max_jump <= 0) {
      return false;
    }

    vector<bool> visited(n, false);
    stack<int> stack{};

    stack.emplace(0);
    visited[0] = true;

    while (!stack.empty()) {
      int curr = stack.top();
      stack.pop();

      if (curr == n - 1) {
        return true;
      }

      for (int i = curr + min_jump; i <= std::min(curr + max_jump, n - 1); ++i) {
        if (s[i] == '0' && !visited[i]) {
          stack.emplace(i);
          visited[i] = true;
        }
      }
    }

    return false;
  }

  // BFS
  // https://leetcode.com/tag/breadth-first-search/
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  bool can_reach_v3(string const& s, int min_jump, int max_jump) {
    if (s.empty()) {
      return false;
    }

    int n = s.size();
    if (s[n - 1] != '0') {
      return false;
    }

    if (n == 1) {
      return true;
    }

    if (max_jump <= 0) {
      return false;
    }

    vector<bool> visited(n, false);
    queue<int> queue{};
    int farthest = 0;

    queue.emplace(0);
    visited[0] = true;

    while (!queue.empty()) {
      int curr = queue.front();
      queue.pop();

      if (curr == n - 1) {
        return true;
      }

      int start = std::max(curr + min_jump, farthest + 1);
      int end = std::min(curr + max_jump, n - 1);
      for (int i = start; i <= end; ++i) {
        if (s[i] == '0' && !visited[i]) {
          queue.emplace(i);
          visited[i] = true;
        }
      }

      farthest = end;
    }

    return false;
  }

  // Sliding Window
  // https://leetcode.com/tag/sliding-window/
  // Dynamic Programming (DP)
  // https://leetcode.com/tag/dynamic-programming/
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  bool can_reach_v4(string const& s, int min_jump, int max_jump) {
    if (s.empty()) {
      return false;
    }

    int n = s.size();
    if (s[n - 1] != '0') {
      return false;
    }

    if (n == 1) {
      return true;
    }

    if (max_jump <= 0) {
      return false;
    }

    // `reachable[i]` indicates whether position `i` in the string `s` is
    // reachable from the starting position (index 0) by making jumps within the
    // specified minimum (`min_jump`) and maximum (`max_jump`) jump distances.
    vector<bool> reachable(n, false);
    reachable[0] = true;

    // Number of reachable positions in the current sliding window
    int count = 0;

    // Iterate through the string `s`, updating `reachable[i]` to `true` if
    // position `i` can be reached by jumping from any previously reachable
    // position within the range defined by `min_jump` and `max_jump`.
    for (int i = 1; i < n; ++i) {
      // The sliding window for the current position `i` is in the range:
      // `[i - max_jump, i - min_jump]`
      //
      // --------|----------------|-----------●------>
      //         ^                ^           ^
      //   (i - max_jump)   (i - min_jump)    i

      // Note: The following four lines of code are difficult to understand and
      // are replaced with similar code below.
      /*
      if (i >= minJump) {
        count += reachable[i - minJump];
      }
      if (i > maxJump) {
        count -= reachable[i - maxJump - 1];
      }
      */

      int left = i - max_jump; // left boundary of the window
      int right = i - min_jump; // right boundary of the window

      // If the position `left - 1` is within the bounds of the array, subtract
      // its reachability from `count`. This is because the position `left - 1`
      // is no longer within the sliding window.
      if (left - 1 >= 0) {
        count -= reachable[left - 1] ? 1 : 0;
      }
      // If the position `right` is within the bounds of the array, add its
      // reachability to `count`. This is because the position `right` is now
      // included in the sliding window.
      if (right >= 0) {
        count += reachable[right] ? 1 : 0;
      }

      // If there are reachable positions in the current window and the current
      // character is '0', mark the current position as reachable.
      if (count > 0 && s[i] == '0') {
        reachable[i] = true;
      }
    }

    // Return whether the last position is reachable
    return reachable[n - 1];
  }
};
