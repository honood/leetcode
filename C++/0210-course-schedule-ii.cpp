// HoNooD
// 2024.05.20 17:15

// 210. Course Schedule II
// https://leetcode.com/problems/course-schedule-ii/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Topological_sorting
// In computer science, a topological sort or topological ordering of a directed 
// graph is a linear ordering of its vertices such that for every directed edge 
// `(u,v)` from vertex `u` to vertex `v`, `u` comes before `v` in the ordering.
// For instance, the vertices of the graph may represent tasks to be performed, 
// and the edges may represent constraints that one task must be performed before 
// another; in this application, a topological ordering is just a valid sequence 
// for the tasks. Precisely, a topological sort is a graph traversal in which 
// each node `v` is visited only after all its dependencies are visited. A 
// topological ordering is possible if and only if the graph has no directed 
// cycles, that is, if it is a directed acyclic graph (DAG). Any DAG has at 
// least one topological ordering, and algorithms are known for constructing a 
// topological ordering of any DAG in linear time. 
// 
// Topological sorting is possible even when the DAG has disconnected components.
//
// The canonical application of topological sorting is in scheduling a sequence 
// of jobs or tasks based on their dependencies. The jobs are represented by 
// vertices, and there is an edge from `x` to `y` if job `x` must be completed  
// before job `y` can be started. Then, a topological sort gives an order in 
// which to perform the jobs.
// 
// https://en.wikipedia.org/wiki/Directed_acyclic_graph
// https://en.wikipedia.org/wiki/Directed_graph
// https://en.wikipedia.org/wiki/Adjacency_matrix
// https://en.wikipedia.org/wiki/Adjacency_list
// https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Glossary_of_graph_theory

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Kahn's algorithm
// https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm
// -----------------------------------------------------------------------------
// L ← Empty list that will contain the sorted elements
// S ← Set of all nodes with no incoming edge
//
// while S is not empty do
//     remove a node n from S
//     add n to L
//     for each node m with an edge e from n to m do
//         remove edge e from the graph
//         if m has no other incoming edges then
//             insert m into S
//
// if graph has edges then
//     return error   (graph has at least one cycle)
// else 
//     return L   (a topologically sorted order)
// -----------------------------------------------------------------------------
class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    if (numCourses <= 0) {
      return {};
    }

    // create adjacency list to represent the graph
    vector<vector<int>> graph(numCourses);
    // calculate indegree for each course
    vector<int> indegree(numCourses, 0);
    for (auto const& edge : prerequisites) {
      graph[edge[1]].emplace_back(edge[0]); // edge[1] -> edge[0]
      ++indegree[edge[0]];
    }

    vector<int> res{};
    res.reserve(numCourses);

    // Use queue for topological sorting
    queue<int> q{};
    for (int i = 0; i < numCourses; ++i) {
      if (0 == indegree[i]) {
        q.emplace(i);
      }
    }

    while (!q.empty()) {
      int curr = q.front();
      q.pop();

      res.emplace_back(curr);

      for (auto const& neighbor : graph[curr]) {
        if (0 == --indegree[neighbor]) {
          q.emplace(neighbor);
        }
      }
    } // while

    if (res.size() == numCourses) {
      return res;
    }

    return {};
  }
};

// https://en.wikipedia.org/wiki/Topological_sorting#Depth-first_search
// -----------------------------------------------------------------------------
// L ← Empty list that will contain the sorted nodes
// while exists nodes without a permanent mark do
//     select an unmarked node n
//     visit(n)
//
// function visit(node n)
//     if n has a permanent mark then
//         return
//     if n has a temporary mark then
//         stop   (graph has at least one cycle)
//
//     mark n with a temporary mark
//
//     for each node m with an edge from n to m do
//         visit(m)
//
//     remove temporary mark from n
//     mark n with a permanent mark
//     add n to head of L
// -----------------------------------------------------------------------------
class Solution_2 {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    if (numCourses <= 0) {
      return {};
    }

    vector<State> visited(numCourses, State::UNVISITED);

    // create adjacency list to represent the graph
    vector<vector<int>> graph(numCourses);
    for (auto const& edge : prerequisites) {
      graph[edge[1]].emplace_back(edge[0]); // edge[1] -> edge[0]
    }

    forward_list<int> res{};
    for (int i = 0; i < numCourses; ++i) {
      bool noCycle = dfs(graph, i, res, visited);
      if (!noCycle) {
        return {};
      }
    }

    return {res.cbegin(), res.cend()};
  }

private:
  enum State { UNVISITED, VISITING, VISITED };

  bool dfs(vector<vector<int>> const& graph, int course, forward_list<int>& res, vector<State>& visited) {
    if (State::VISITING == visited[course]) {
      return false; // cycle detected
    }

    if (State::VISITED == visited[course]) {
      return true;
    }

    visited[course] = State::VISITING;

    for (auto const& neighbor : graph[course]) {
      bool noCycle = dfs(graph, neighbor, res, visited);
      if (!noCycle) {
        return false;
      }
    }

    visited[course] = State::VISITED;
    res.emplace_front(course);
    return true;
  }
};
