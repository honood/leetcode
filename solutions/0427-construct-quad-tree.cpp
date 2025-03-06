// HoNooD
// 2024.05.29 10:06

// 427. Construct Quad Tree
// https://leetcode.com/problems/construct-quad-tree/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Quadtree
// https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm

// Definition for a QuadTree node.
class Node {
public:
  bool val;
  bool isLeaf;
  Node* topLeft;
  Node* topRight;
  Node* bottomLeft;
  Node* bottomRight;
  
  Node() {
    val = false;
    isLeaf = false;
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
  }
  
  Node(bool _val, bool _isLeaf) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
  }
  
  Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = _topLeft;
    topRight = _topRight;
    bottomLeft = _bottomLeft;
    bottomRight = _bottomRight;
  }
};

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  Node* construct(vector<vector<int>>& grid) {
    if (grid.empty()) {
      return nullptr;
    }

    return impl(grid, 0, 0, grid.size());
  }

private:
  Node* impl(vector<vector<int>> const& grid, int row, int col, int size) {
    if (grid.size() == 1) {
      assert(grid[0].size() == 1);
      return new Node{static_cast<bool>(grid[row][col]), true};
    }

    if (isSame(grid, row, col, size)) {
      return new Node{static_cast<bool>(grid[row][col]), true};
    }

    int subgridSize = size / 2;
    return new Node{
      true, // true or false both is OK.
      false,
      impl(grid, row, col, subgridSize),
      impl(grid, row, col + subgridSize, subgridSize),
      impl(grid, row + subgridSize, col, subgridSize),
      impl(grid, row + subgridSize, col + subgridSize, subgridSize),
    };
  }

  bool isSame(vector<vector<int>> const& grid, int row, int col, int size) {
    for (int i = row; i < row + size; ++i) {
      for (int j = col; j < col + size; ++j) {
        if (grid[i][j] != grid[row][col]) {
          return false;
        }
      }
    }

    return true;
  }
};
