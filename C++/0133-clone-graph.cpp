// HoNooD
// 2024.05.17 11:14

// 133. Clone Graph
// https://leetcode.com/problems/clone-graph/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Adjacency_matrix
// https://en.wikipedia.org/wiki/Adjacency_list
// https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Glossary_of_graph_theory

// Definition for a Node.
class Node {
public:
  int val;
  vector<Node*> neighbors;
  Node() {
    val = 0;
    neighbors = vector<Node*>();
  }
  Node(int _val) {
    val = _val;
    neighbors = vector<Node*>();
  }
  Node(int _val, vector<Node*> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  Node* cloneGraph(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }

    unordered_map<Node*, Node*> visited{};
    visited.emplace(node, new Node{node->val});

    queue<Node*> q{};
    q.push(node);
    while (!q.empty()) {
      Node* node = q.front();
      q.pop();

      for (auto const& neighbor : node->neighbors) {
        if (visited.find(neighbor) == visited.end()) {
          visited.emplace(neighbor, new Node{neighbor->val});
          q.push(neighbor);
        }
        visited[node]->neighbors.push_back(visited[neighbor]);
      }
    }

    return visited[node];
  }
};

class Solution_2 {
public:
  Node* cloneGraph(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }

    unordered_map<Node*, Node*> visited{};
    visited.emplace(node, new Node{node->val});

    stack<Node*> stack{};
    stack.push(node);
    while (!stack.empty()) {
      Node* node = stack.top();
      stack.pop();

      for (auto const& neighbor : node->neighbors) {
        if (visited.find(neighbor) == visited.end()) {
          visited.emplace(neighbor, new Node{neighbor->val});
          stack.push(neighbor);
        }

        visited[node]->neighbors.push_back(visited[neighbor]);
      }
    }

    return visited[node];
  }
};

class Solution_3 {
public:
  Node* cloneGraph(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }

    unordered_map<Node*, Node*> visited{};
    return cloneNode(node, visited);
  }

private:
  Node* cloneNode(Node* node, unordered_map<Node*, Node*>& visited) {
    if (node == nullptr) {
      return nullptr;
    }

    if (visited.find(node) != visited.end()) {
      return visited[node];
    }

    visited.emplace(node, new Node{node->val});
    for (auto const& neighbor : node->neighbors) {
      visited[node]->neighbors.push_back(cloneNode(neighbor, visited));
    }
    return visited[node];
  }
};
