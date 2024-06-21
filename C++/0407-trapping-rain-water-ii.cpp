// HoNooD <honood@gmail.com>
// 2024.06.21 13:28

// 407. Trapping Rain Water II
// https://leetcode.com/problems/trapping-rain-water-ii/description/

// https://en.wikipedia.org/wiki/Heap_(data_structure)

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// The algorithm uses a min-heap (priority queue) to simulate a water-filling
// process starting from the boundary. It continuously processes the lowest cell
// and attempts to "fill" water into its lower adjacent cells. If a lower
// adjacent cell is found, it calculates the trapped water and updates the cell's
// height to the current processing height, ensuring no repeated water filling.
// The process continues until all cells are evaluated, and each cell is only
// processed once using a visited matrix to avoid redundant computations.
//
// Note: To understand how the algorithm works, fill in the appropriate height
// values in the empty cells of the matrix below, and then follow the code logic
// step by step.
//
// ┌─────┬─────┬─────┬─────┬─────┬─────┐
// │     │     │  1  │     │     │     │
// ├─────┼─────┼─────┼─────┼─────┼─────┤
// │     │     │     │     │     │     │
// ├─────┼─────┼─────┼─────┼─────┼─────┤
// │     │     │     │     │     │     │
// ├─────┼─────┼─────┼─────┼─────┼─────┤
// │     │     │     │     │     │     │
// ├─────┼─────┼─────┼─────┼─────┼─────┤
// │     │     │     │     │     │     │
// ├─────┼─────┼─────┼─────┼─────┼─────┤
// │     │     │     │     │     │     │
// └─────┴─────┴─────┴─────┴─────┴─────┘
//
class Solution {
public:
  int trapRainWater(vector<vector<int>> const& heightMap) {
    if (heightMap.empty() || heightMap[0].empty()) {
      return 0;
    }

    int m = heightMap.size();
    int n = heightMap[0].size();

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    // min-heap (priority queue) to store the boundary cells
    priority_queue<Cell, vector<Cell>, std::greater<Cell>> pq{};

    // initialize the priority queue with the boundary cells
    for (int i = 0; i < m; ++i) {
      pq.emplace(heightMap[i][0], i, 0);
      pq.emplace(heightMap[i][n - 1], i, n - 1);
      visited[i][0] = true;
      visited[i][n - 1] = true;
    }
    for (int j = 1; j < n - 1; ++j) {
      pq.emplace(heightMap[0][j], 0, j);
      pq.emplace(heightMap[m - 1][j], m - 1, j);
      visited[0][j] = true;
      visited[m - 1][j] = true;
    }

    int waterTrapped = 0;
    while (!pq.empty()) {
      Cell cell = pq.top();
      pq.pop();

      for (auto const& [dx, dy] : directions) {
        int nx = cell.x + dx;
        int ny = cell.y + dy;

        if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
          visited[nx][ny] = true;
          waterTrapped += std::max(0, cell.height - heightMap[nx][ny]);
          pq.emplace(std::max(heightMap[nx][ny], cell.height), nx, ny);
        }
      }
    }

    return waterTrapped;
  }

private:
  int const directions[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  struct Cell {
    int height;
    int x;
    int y;

    bool operator>(Cell const& other) const {
      return height > other.height;
    }
  };
};
