// HoNooD
// 2024.05.17 17:58

// 399. Evaluate Division
// https://leetcode.com/problems/evaluate-division/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Directed_graph
// https://en.wikipedia.org/wiki/Adjacency_matrix
// https://en.wikipedia.org/wiki/Adjacency_list
// https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Glossary_of_graph_theory

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    // build the graph
    graph_.clear();
    for (int i = 0; i < equations.size(); ++i) {
      string const& u = equations[i][0];
      string const& v = equations[i][1];
      double weight = values[i];
      graph_[u][v] = weight;
      graph_[v][u] = 1.0 / weight;
    }

    // Note: do not use brace-initialization, i.e. uniform initialization
    vector<double> results(queries.size(), -1.0);
    for (int i = 0; i < queries.size(); ++i) {
      visited_.clear();
      results[i] = dfs(queries[i][0], queries[i][1]);
    }

    return results;
  }

private:
  double dfs(string const& start, string const& end) {
    if (graph_.find(start) == graph_.end() || graph_.find(end) == graph_.end()) {
      return -1.0;
    }

    if (start == end) {
      return 1.0;
    }

    if (graph_[start].find(end) != graph_[start].end()) {
      return graph_[start][end];
    }

    visited_.insert(start);

    for (auto const& neighbor : graph_[start]) {
      if (visited_.find(neighbor.first) != visited_.end()) {
        continue;
      }

      double res = dfs(neighbor.first, end);
      // Note: do not use `res != -1.0`
      if (std::abs(-1.0 - res) > std::numeric_limits<double>::epsilon()) {
        return res * neighbor.second;
      }
    }

    // Backtrack by unmarking the current node as visited (optional)
    visited_.erase(start);

    return -1.0;
  }

  unordered_map<string, unordered_map<string, double>> graph_{};
  unordered_set<string> visited_{};
};

class Solution_2 {
public:
  vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    // build the graph
    unordered_map<string, unordered_map<string, double>> graph{};
    for (int i = 0; i < equations.size(); ++i) {
      string const& u = equations[i][0];
      string const& v = equations[i][1];
      double weight = values[i];
      graph[u][v] = weight;
      graph[v][u] = 1.0 / weight;
    }

    vector<double> results(queries.size(), -1.0);
    for (int i = 0; i < queries.size(); ++i) {
      string const& start = queries[i][0];
      string const& end = queries[i][1];

      if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
        // Note: no need to set results[i] as `-1.0`, it already is.
        continue;
      }

      if (start == end) {
        results[i] = 1.0;
        continue;
      }

      unordered_set<string> visited{};
      visited.reserve(graph.size());
      visited.emplace(start);
      queue<pair<string, double>> q{};
      q.emplace(start, 1.0);
      while (!q.empty()) {
        pair<string, double> curr = q.front();
        q.pop();

        string const& vertex = curr.first;
        double acc = curr.second;
        if (vertex == end) {
          results[i] = acc;
          break;
        }

        for (auto const& neighbor : graph[vertex]) {
          string const& vertex = neighbor.first;
          if (visited.find(vertex) != visited.end()) {
            continue;
          }

          double weight = neighbor.second;
          q.emplace(vertex, acc * weight);
          visited.emplace(vertex);
        } // for
      } // while
    } // for

    return results;
  }
};
