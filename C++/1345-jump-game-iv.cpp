// HoNooD <honood@gmail.com>
// 2024.07.27 18:48

// 1345. Jump Game IV
// https://leetcode.com/problems/jump-game-iv/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// This problem can be visualized as finding the shortest path in an unweighted
// graph, which makes Breadth-First Search (BFS) a suitable method.

class Solution {
public:
  int minJumps(vector<int>& arr) {
    return min_jumps_v1(arr);
  }

private:
  int min_jumps_v1(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
      return 0;
    }

    unordered_map<int, vector<int>> graph{};
    for (int i = 0; i < n; ++i) {
      graph[arr[i]].emplace_back(i);
    }

    vector<bool> visited(n, false);
    queue<int> queue{};

    queue.emplace(0);
    visited[0] = true;

    int steps = 0;

    while (!queue.empty()) {
      int sz = queue.size();
      for (int i = 0; i < sz; ++i) {
        int curr = queue.front();
        queue.pop();

        if (curr == n - 1) {
          return steps;
        }

        // Note: Do not replace the other four `visited[xxx] = true;` statements
        // with the following line `visited[curr] = true;`!
        //
        // Consider the array [100, -23, -23, 404, 100, 23, 23, 23, 3, 404] as
        // an example:
        // 1. When curr = 1, since 2 is both `curr + 1` and exists in
        //    `graph[arr[1]]` ([1, 2]), two instances of 2 will consecutively
        //    appear in the queue;
        // 2. (Assuming the above case is resolved) When the queue has elements
        //    `4->2`, and 4 is dequeued resulting in the queue being `2->3->5`;
        //    when 2 is dequeued next, since 3 is already in the queue but not
        //    marked as visited, the queue becomes `3->5->3`, hence 3 appears
        //    twice in the queue.

        // visited[curr] = true;

        if (curr - 1 >= 0 && !visited[curr - 1]) {
          queue.emplace(curr - 1);
          visited[curr - 1] = true;
        }

        if (curr + 1 < n && !visited[curr + 1]) {
          queue.emplace(curr + 1);
          visited[curr + 1] = true;
        }

        for (int next : graph[arr[curr]]) {
          if (!visited[next]) {
            queue.emplace(next);
            visited[next] = true;
          }
        }
        graph[arr[curr]].clear();
      }

      ++steps;
    }

    return -1;
  }

  int min_jumps_v2(vector<int> const& arr) {
    int n = arr.size();
    if (n <= 1) {
      return 0;
    }

    vector<int> dp(n, std::numeric_limits<int>::max());
    dp[0] = 0;

    unordered_map<int, vector<int>> graph{};
    for (int i = 0; i < n; ++i) {
      graph[arr[i]].emplace_back(i);
    }

    queue<int> queue{};
    queue.push(0);

    while (!queue.empty()) {
      int i = queue.front();
      queue.pop();

      if (i + 1 < n && dp[i] + 1 < dp[i + 1]) {
        dp[i + 1] = dp[i] + 1;
        queue.emplace(i + 1);
      }

      if (i - 1 >= 0 && dp[i] + 1 < dp[i - 1]) {
        dp[i - 1] = dp[i] + 1;
        queue.emplace(i - 1);
      }

      for (int next : graph[arr[i]]) {
        if (dp[i] + 1 < dp[next]) {
          dp[next] = dp[i] + 1;
          queue.emplace(next);
        }
      }
      graph[arr[i]].clear();
    }

    return dp[n - 1];
  }
};
