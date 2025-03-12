// HoNooD <honood@gmail.com>
// 2025.03.11 18:55
// 2024.05.17 17:58

// 399. Evaluate Division
// https://leetcode.com/problems/evaluate-division/?envType=study-plan-v2&envId=leetcode-75
// https://leetcode.com/problems/evaluate-division/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Directed_graph
// https://en.wikipedia.org/wiki/Adjacency_matrix
// https://en.wikipedia.org/wiki/Adjacency_list
// https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Glossary_of_graph_theory

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Note:
// 1. The input is always valid. You may assume that evaluating the queries will
// not result in division by zero and that there is no contradiction.
// 2. The variables that do not occur in the list of equations are undefined, so
// the answer cannot be determined for them.
class Solution {
public:
  // Constraints:
  //   - values.length == equations.length
  //   - 0.0 < values[i] <= 20.0
  //
  // Note: Nodes in `equations` and `queries` may not form a connected graph!!!
  vector<double> calcEquation(vector<vector<string>>& equations,
                              vector<double>& values,
                              vector<vector<string>>& queries) {
    return calc_equation_v1(equations, values, queries);
  }

private:
  // DFS
  //
  // - Time complexity: O(E + Q*V) where E is the number of equations, Q is the
  // number of queries, and V is the number of variables
  // - Space complexity: O(V) for the graph and visited set
  vector<double> calc_equation_v1(vector<vector<string>> const& equations,
                                  vector<double> const& values,
                                  vector<vector<string>> const& queries) {
    unordered_map<string, unordered_map<string, double>> graph{};
    for (int i = 0; i < values.size(); ++i) {
      string const& u = equations[i][0];
      string const& v = equations[i][1];
      double w = values[i];
      graph[u][v] = w;
      graph[v][u] = 1.0 / w;
    }

    unordered_set<string> visited{};

    using csr = string const&;
    std::function<double(csr, csr)> dfs
        = [&dfs, &graph, &visited](csr current, csr target) {
            visited.emplace(current);

            if (graph[current].contains(target)) {
              return graph[current][target];
            }

            for (auto const& [neighbor, value] : graph[current]) {
              if (visited.contains(neighbor)) {
                continue;
              }

              double result = dfs(neighbor, target);
              if (fabs(result + 1.0) > numeric_limits<double>::epsilon()) {
                // result != -1.0
                return value * result;
              }
            }
            return -1.0;
          };

    vector<double> answers(queries.size(), -1.0);
    for (int i = 0; i < queries.size(); ++i) {
      string const& start = queries[i][0];
      string const& end = queries[i][1];
      if (!graph.contains(start) || !graph.contains(end)) {
        continue;
      }

      if (start == end) {
        answers[i] = 1.0;
        continue;
      }

      visited.clear();
      answers[i] = dfs(start, end);
    }
    return answers;
  }

  // BFS
  //
  // - Time complexity: O(E + Q*V) where E is the number of equations, Q is the
  // number of queries, and V is the number of variables
  // - Space complexity: O(V) for the graph and queue
  vector<double> calc_equation_v2(vector<vector<string>> const& equations,
                                  vector<double> const& values,
                                  vector<vector<string>> const& queries) {
    unordered_map<string, unordered_map<string, double>> graph{};
    for (int i = 0; i < values.size(); ++i) {
      string const& u = equations[i][0];
      string const& v = equations[i][1];
      double w = values[i];
      graph[u][v] = w;
      graph[v][u] = 1.0 / w;
    }

    vector<double> answers(queries.size(), -1.0);
    for (int i = 0; i < queries.size(); ++i) {
      string const& start = queries[i][0];
      string const& end = queries[i][1];

      if (!graph.contains(start) || !graph.contains(end)) {
        answers[i] = -1.0;
        continue;
      }

      if (start == end) {
        answers[i] = 1.0;
        continue;
      }

      std::queue<pair<string, double>> queue{{{start, 1.0}}};
      unordered_set<string> visited{start};
      bool found = false;
      while (!queue.empty() && !found) {
        auto [node, acc] = queue.front();
        queue.pop();

        for (auto const& [neighbor, value] : graph[node]) {
          if (visited.contains(neighbor)) {
            continue;
          }

          visited.emplace(neighbor);

          double new_acc = value * acc;
          if (neighbor == end) {
            answers[i] = new_acc;
            found = true;
            break;
          }

          queue.emplace(neighbor, new_acc);
        }
      }

      if (!found) {
        answers[i] = -1.0;
      }
    }
    return answers;
  }

  // Union-Find: https://en.wikipedia.org/wiki/Disjoint-set_data_structure
  // 并查集：https://zh.wikipedia.org/wiki/%E5%B9%B6%E6%9F%A5%E9%9B%86
  //
  // Connectivity (graph theory):
  // https://en.wikipedia.org/wiki/Connectivity_(graph_theory) Kruskal's
  // algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
  //
  // - Time complexity: O((E + Q) * α(N)) where E is the number of equations, Q
  // is the number of queries, and N is the total number of variables.
  // - Space complexity: O(N)
  vector<double> calc_equation_v3(vector<vector<string>> const& equations,
                                  vector<double> const& values,
                                  vector<vector<string>> const& queries) {
    class UnionFind {
    public:
      string find(string const& x) {
        if (!parent.contains(x)) {
          parent.emplace(x, x);
          weight.emplace(x, 1.0);
          return x;
        }

        if (string original_parent = parent[x]; original_parent != x) {
          parent[x] = find(original_parent);
          // Given, before updating parent[x]:
          //   1. weight[x] = x / original_parent
          //   2. weight[original_parent] = original_parent / parent[x]
          // Then, after updating parent[x]:
          //   weight[x] = x / parent[x]
          //             = (weight[x] * original_parent)
          //               / (original_parent / weight[original_parent])
          //             = weight[x] * weight[original_parent]
          weight[x] *= weight[original_parent];
        }
        return parent[x];
      }

      void union_sets(string const& x, string const& y, double value) {
        string root_x = find(x);
        string root_y = find(y);
        if (root_x != root_y) {
          // Given, before updating parent[root_x]:
          //   1. x / y = value
          //   2. x / root_x = weight[x];
          //   3. y / root_y = weight[y];
          // Then, after updating parent[root_x]:
          //   weight[root_x] = root_x / root_y
          //                  = (x / weight[x]) / (y / weight[y])
          //                  = (x / y) * (weight[y] / weight[x])
          //                  = value * weight[y] / weight[x]
          parent[root_x] = root_y;
          weight[root_x] = value * weight[y] / weight[x];
        }
      }

      double query(string const& x, string const& y) {
        if (!parent.contains(x) || !parent.contains(y)) {
          return -1.0;
        }

        if (x == y) {
          return 1.0;
        }

        string root_x = find(x);
        string root_y = find(y);
        if (root_x != root_y) {
          return -1.0;
        }

        // Given:
        //   1. weight[x] = x / root_x
        //   2. weight[y] = y / root_y
        //   3. root_x = root_y
        // Then:
        //   x / y = (weight[x] * root_x) / (weight[y] * root_y)
        //         = (weight[x] / weight[y]) * (root_x / root_y)
        //         = (weight[x] / weight[y]) * 1.0
        //         = weight[x] / weight[y]
        return weight[x] / weight[y];
      }

    private:
      unordered_map<string, string> parent;
      unordered_map<string, double> weight;
    };

    UnionFind uf{};

    for (int i = 0; i < values.size(); ++i) {
      string const& u = equations[i][0];
      string const& v = equations[i][1];
      double w = values[i];
      uf.union_sets(u, v, w);
    }

    vector<double> answers(queries.size(), -1.0);
    for (int i = 0; i < queries.size(); ++i) {
      string start = queries[i][0];
      string end = queries[i][1];
      answers[i] = uf.query(start, end);
    }
    return answers;
  }
};
