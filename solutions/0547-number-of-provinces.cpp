// HoNooD <honood@gmail.com>
// 2025.03.09 16:17

// 547. Number of Provinces
// https://leetcode.com/problems/number-of-provinces/?envType=study-plan-v2&envId=leetcode-75

// Component (graph theory)
// https://en.wikipedia.org/wiki/Component_(graph_theory)

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // Constraints:
  //   - n == isConnected.length
  //   - n == isConnected[i].length
  //   - isConnected[i][i] == 1
  //   - isConnected[i][j] == isConnected[j][i]
  int findCircleNum(vector<vector<int>>& isConnected) {
    return find_circle_num_v3(isConnected);
  }

private:
  // DFS
  //
  // - Time Complexity: O(n^2) where n is the number of cities
  // - Space Complexity: O(n) for visited array and recursion stack
  int find_circle_num_v1(vector<vector<int>> const& is_connected) {
    int n = is_connected.size();
    vector<bool> visited(n, false);

    std::function<void(int)> dfs = [&](int city) {
      visited[city] = true;

      for (int neighbor = 0; neighbor < n; ++neighbor) {
        if (is_connected[city][neighbor] == 1 && !visited[neighbor]) {
          dfs(neighbor);
        }
      }
    };

    int provinces = 0;
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        ++provinces;
        dfs(i);
      }
    }
    return provinces;
  }

  // BFS
  //
  // - Time Complexity: O(n^2) where n is the number of cities
  // - Space Complexity: O(n) for visited array and queue
  int find_circle_num_v2(vector<vector<int>> const& is_connected) {
    int n = is_connected.size();
    vector<bool> visited(n, false);
    std::queue<int> queue{};

    int provinces = 0;
    for (int i = 0; i < n; ++i) {
      if (visited[i]) {
        continue;
      }

      ++provinces;

      queue.push(i);
      visited[i] = true;

      while (!queue.empty()) {
        int city = queue.front();
        queue.pop();

        // Check all neighbors
        for (int neighbor = 0; neighbor < n; ++neighbor) {
          if (is_connected[city][neighbor] == 1 && !visited[neighbor]) {
            visited[neighbor] = true;
            queue.push(neighbor);
          }
        }
      } // while
    } // for

    return provinces;
  }

  // Union-Find: https://en.wikipedia.org/wiki/Disjoint-set_data_structure
  // 并查集：https://zh.wikipedia.org/wiki/%E5%B9%B6%E6%9F%A5%E9%9B%86
  //
  // Connectivity (graph theory): https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
  // Kruskal's algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
  //
  // - Time Complexity: O(n^2 * α(n)) where α is the inverse Ackermann function
  // - Space Complexity: O(n) for parent and rank arrays
  int find_circle_num_v3(vector<vector<int>> const& is_connected) {
    class UnionFind {
    public:
      explicit UnionFind(int n): parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
          parent[i] = i;
        }
      }

      int find(int x) {
        if (parent[x] != x) {
          parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
      }

      void union_sets(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x == root_y) {
          return;
        }

        if (rank[root_x] < rank[root_y]) {
          parent[root_x] = root_y;
        } else {
          parent[root_y] = root_x;
          if (rank[root_x] == rank[root_y]) {
            ++rank[root_x];
          }
        }
      }

      bool connected(int x, int y) {
        return find(x) == find(y);
      }

    private:
      vector<int> parent;
      vector<int> rank;
    };

    int n = is_connected.size();
    UnionFind uf{n};

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (is_connected[i][j] == 1) {
          uf.union_sets(i, j);
        }
      }
    }

    int provinces = 0;
    for (int i = 0; i < n; ++i) {
      if (uf.find(i) == i) {
        ++provinces;
      }
    }
    return provinces;
  }
};
