// HoNooD <honood@gmail.com>
// 2024.07.27 10:00

// 1306. Jump Game III
// https://leetcode.com/problems/jump-game-iii/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool canReach(vector<int>& arr, int start) {
    return can_reach_v3(arr, start);
  }

private:
  // DFS (recursive)
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  bool can_reach_v1(vector<int> const& arr, int start) {
    int n = arr.size();
    vector<bool> visited(n, false);

    return dfs(arr, start, visited);
  }

  bool dfs(vector<int> const& arr, int curr, vector<bool>& visited) {
    if (curr < 0 || curr >= arr.size() || visited[curr]) {
      return false;
    }

    if (arr[curr] == 0) {
      return true;
    }

    visited[curr] = true;

    return dfs(arr, curr - arr[curr], visited) ||
           dfs(arr, curr + arr[curr], visited);
  }

  // DFS (iterative)
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  bool can_reach_v2(vector<int> const& arr, int start) {
    int n = arr.size();
    vector<bool> visited(n, false);
    stack<int> stack{};

    stack.emplace(start);
    while (!stack.empty()) {
      int curr = stack.top();
      stack.pop();

      if (arr[curr] == 0) {
        return true;
      }

      visited[curr] = true;

      int left_jump = curr - arr[curr];
      if (left_jump >= 0 && !visited[left_jump]) {
        stack.emplace(left_jump);
      }

      int right_jump = curr + arr[curr];
      if (right_jump < n && !visited[right_jump]) {
        stack.emplace(right_jump);
      }
    }

    return false;
  }

  // BFS
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  bool can_reach_v3(vector<int> const& arr, int start) {
    int n = arr.size();
    vector<bool> visited(n, false);
    queue<int> queue{};

    queue.emplace(start);
    visited[start] = true;

    while (!queue.empty()) {
      int curr = queue.front();
      queue.pop();

      if (arr[curr] == 0) {
        return true;
      }

      int left_jump = curr - arr[curr];
      if (left_jump >= 0 && !visited[left_jump]) {
        queue.emplace(left_jump);
        visited[left_jump] = true;
      }

      int right_jump = curr + arr[curr];
      if (right_jump < n && !visited[right_jump]) {
        queue.emplace(right_jump);
        visited[right_jump] = true;
      }
    }

    return false;
  }
};
