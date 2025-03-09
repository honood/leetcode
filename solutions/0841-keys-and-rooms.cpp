// HoNooD <honood@gmail.com>
// 2025.03.09 10:31

// 841. Keys and Rooms
// https://leetcode.com/problems/keys-and-rooms/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  bool canVisitAllRooms(vector<vector<int>>& rooms) {
    return can_visit_all_rooms_v1(rooms);
  }

private:
  // BFS
  //
  // - Time complexity: O(n + e) where n is the number of rooms and e is the
  // total number of keys
  // - Space complexity: O(n)
  bool can_visit_all_rooms_v1(vector<vector<int>> const& rooms) {
    int n = rooms.size();
    vector<bool> visited(n, false);
    visited[0] = true;
    std::queue<int> queue{{0}};
    int visited_count = 1; // Optimization for early termination, not required

    while (!queue.empty()) {
      int room = queue.front();
      queue.pop();

      for (int key : rooms[room]) {
        if (!visited[key]) {
          visited[key] = true;
          queue.push(key);

          ++visited_count;
          if (visited_count == n) {
            return true;
          }
        }
      }
    }

    return std::all_of(visited.cbegin(), visited.cend(),
                       [](bool visited) { return visited; });
  }

  // DFS (recursive)
  //
  // - Time complexity: O(n + e) where n is the number of rooms and e is the
  // total number of keys
  // - Space complexity: O(n)
  bool can_visit_all_rooms_v2(vector<vector<int>> const& rooms) {
    int n = rooms.size();
    vector<bool> visited(n, false);
    can_visit_all_rooms_v2_dfs(rooms, 0, visited);

    return std::all_of(visited.cbegin(), visited.cend(),
                       [](bool visited) { return visited; });
  }

  void can_visit_all_rooms_v2_dfs(vector<vector<int>> const& rooms, int room,
                                  vector<bool>& visited) {
    visited[room] = true;

    for (int key : rooms[room]) {
      if (!visited[key]) {
        can_visit_all_rooms_v2_dfs(rooms, key, visited);
      }
    }
  }

  // DFS (iterative)
  //
  // - Time complexity: O(n + e) where n is the number of rooms and e is the
  // total number of keys
  // - Space complexity: O(n)
  bool can_visit_all_rooms_v3(vector<vector<int>> const& rooms) {
    int n = rooms.size();
    vector<bool> visited(n, false);
    visited[0] = true;
    std::stack<int> stack{{0}};

    while (!stack.empty()) {
      int room = stack.top();
      stack.pop();

      for (int key : rooms[room]) {
        if (!visited[key]) {
          visited[key] = true;
          stack.push(key);
        }
      }
    }

    return std::all_of(visited.cbegin(), visited.cend(),
                       [](bool visited) { return visited; });
  }
};
