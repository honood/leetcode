// HoNooD <honood@gmail.com>
// 2025.03.11 08:41

// 1466. Reorder Routes to Make All Paths Lead to the City Zero
// https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int minReorder(int n, vector<vector<int>>& connections) {
    return min_reorder_v2(n, connections);
  }

private:
  // DFS
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int min_reorder_v1(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adjacency_list(n);
    vector<unordered_set<int>> outgoing_edges(n);
    // Build graph
    for (auto const& conn : connections) {
      int u = conn[0];
      int v = conn[1];
      adjacency_list[u].emplace_back(v); // u - v
      adjacency_list[v].emplace_back(u); // v - u
      outgoing_edges[u].emplace(v); // u -> v
    }

    std::function<int(int, int)> dfs = [&dfs, &adjacency_list, &outgoing_edges](
                                           int current_city, int parent_city) {
      int reorder_count = 0;
      for (int neighbor_city : adjacency_list[current_city]) {
        // Skip the parent to avoid cycles
        if (neighbor_city == parent_city) {
          continue;
        }

        if (outgoing_edges[current_city].contains(neighbor_city)) {
          ++reorder_count;
        }
        reorder_count += dfs(neighbor_city, current_city);
      }
      return reorder_count;
    };

    // Start DFS from city 0 with no parent (-1)
    return dfs(0, -1);
  }

  // DFS
  //
  // - Time complexity: O(n) where n is the number of cities
  // - Space complexity: O(n) for adjacency list and visited array
  int min_reorder_v2(int n, vector<vector<int>>& connections) {
    vector<vector<pair<int, bool>>> adjacency_list(n);
    for (auto const& conn : connections) {
      int u = conn[0];
      int v = conn[1];
      adjacency_list[u].emplace_back(v, true);
      adjacency_list[v].emplace_back(u, false);
    }

    vector<bool> visited(n, false);

    std::function<int(int)> dfs = [&dfs, &adjacency_list, &visited](int city) {
      visited[city] = true;

      int count = 0;
      for (auto const& [neighbor, original] : adjacency_list[city]) {
        if (visited[neighbor]) {
          continue;
        }
        // If this is an original edge, we need to reorient it
        count += original ? 1 : 0;
        count += dfs(neighbor);
      }
      return count;
    };

    return dfs(0);
  }

  // BFS
  //
  // - Time complexity: O(n) where n is the number of cities
  // - Space complexity: O(n) for adjacency list, queue, and visited array
  int min_reorder_v3(int n, vector<vector<int>>& connections) {
    vector<vector<pair<int, bool>>> adjacency_list(n);
    for (auto const& conn : connections) {
      int u = conn[0];
      int v = conn[1];
      adjacency_list[u].emplace_back(v, true);
      adjacency_list[v].emplace_back(u, false);
    }

    std::queue<int> queue{{0}};
    vector<bool> visited(n, false);
    visited[0] = true;
    int count = 0;

    while (!queue.empty()) {
      int city = queue.front();
      queue.pop();

      for (auto const& [neighbor, original] : adjacency_list[city]) {
        if (visited[neighbor]) {
          continue;
        }

        count += original ? 1 : 0;
        visited[neighbor] = true;
        queue.emplace(neighbor);
      }
    }

    return count;
  }
};
