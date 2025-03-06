// HoNooD <honood@gmail.com>
// 2024.06.25 09:30

// 48. Rotate Image
// https://leetcode.com/problems/rotate-image/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Transpose
// https://en.wikipedia.org/wiki/In-place_matrix_transposition

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Note: simpler, easier to understand
class Solution {
public:
  void rotate(vector<vector<int>>& matrix) {
    rotate_clockwise_90(matrix);
  }

private:
  void rotate_clockwise_90(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty() || matrix.size() != matrix[0].size()) {
      return;
    }

    // 1. transpose the matrix
    transpose(matrix);
    // 2. reverse each row
    for (int i = 0; i < matrix.size(); ++i) {
      std::reverse(matrix[i].begin(), matrix[i].end());
    }

    // Note: An alternative approach to achieve the same 90-degree rotation is:
    // 1. Reverse each column of the matrix.
    // 2. Transpose the matrix.
  }

  void rotate_counterclockwise_90(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty() || matrix.size() != matrix[0].size()) {
      return;
    }

    // 1. transpose the matrix
    transpose(matrix);
    // 2. reverse each column
    int n = matrix.size();
    for (int j = 0; j < n; ++j) {
      for (int i = 0, k = n - 1; i < k; ++i, --k) {
        std::swap(matrix[i][j], matrix[k][j]);
      }
    }

    // Note: An alternative approach to achieve the same 90-degree
    // counterclockwise rotation is:
    // 1. Reverse each row of the matrix.
    // 2. Transpose the matrix.
  }

  void transpose(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty() || matrix.size() != matrix[0].size()) {
      return;
    }

    int n = matrix.size();
    // for (int i = 0; i < n; ++i) {
    //   for (int j = 0; j < n; ++j) {
    //     if (i < j) {
    //       std::swap(matrix[i][j], matrix[j][i]);
    //     }
    //   }
    // }
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        std::swap(matrix[i][j], matrix[j][i]);
      }
    }
  }
};

// Rotate the matrix 90 degrees clockwise layer by layer.
//
// The matrix is rotated in concentric layers, starting from the outermost layer
// and moving towards the center.
//
// Each layer is rotated by swapping elements in four positions in a circular
// manner.
//
// Example with a 4x4 matrix:
// Original:
//  1  2  3  4
//  5  6  7  8
//  9 10 11 12
// 13 14 15 16
//
// Rotate outer layer (Layer 0):
//
// | Original Position | Moves To | New Position    |
// |-------------------|----------|-----------------|
// |  (3, 0) -> 13     |    ->    |  (0, 0) ->  1   |
// |  (3, 3) -> 16     |    ->    |  (3, 0) -> 13   |
// |  (0, 3) ->  4     |    ->    |  (3, 3) -> 16   |
// |  (0, 0) ->  1     |    ->    |  (0, 3) ->  4   |
// |  (2, 0) ->  9     |    ->    |  (0, 1) ->  2   |
// |  (3, 2) -> 15     |    ->    |  (2, 0) ->  9   |
// |  (1, 3) ->  8     |    ->    |  (3, 2) -> 15   |
// |  (0, 1) ->  2     |    ->    |  (1, 3) ->  8   |
// |  (1, 0) ->  5     |    ->    |  (0, 2) ->  3   |
// |  (3, 1) -> 14     |    ->    |  (1, 0) ->  5   |
// |  (2, 3) -> 12     |    ->    |  (3, 1) -> 14   |
// |  (0, 2) ->  3     |    ->    |  (2, 3) -> 12   |
//
// Intermediate stages after rotating Layer 0:
// Step 1:                Step 2:                Step 3:
// 13  2  3  1            13  9  3  1            13  9  5  1
//  5  6  7  8             5  6  7  2            14  6  7  2
//  9 10 11 12            15 10 11 12            15 10 11  3
// 16 14 15  4            16 14  8  4            16 12  8  4
//
// Rotate inner layer (Layer 1):
//
// | Original Position | Moves To | New Position    |
// |-------------------|----------|-----------------|
// |  (2, 1) -> 10     |    ->    |  (1, 1) ->  6   |
// |  (2, 2) -> 11     |    ->    |  (2, 1) -> 10   |
// |  (1, 2) ->  7     |    ->    |  (2, 2) -> 11   |
// |  (1, 1) ->  6     |    ->    |  (1, 2) ->  7   |
//
// Final rotated matrix:
// 13  9  5  1
// 14 10  6  2
// 15 11  7  3
// 16 12  8  4
//
// Note: more complex due to offsets
class Solution_2 {
public:
  void rotate(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty() || matrix.size() != matrix[0].size()) {
      return;
    }

    int n = matrix.size();
    for (int layer = 0; layer < n / 2; ++layer) {
      // the index of the first element in the current layer (top row and left
      // column)
      int first = layer;
      // the index of the last element in the current layer (bottom row and
      // right column)
      int last = n - 1 - layer;
      for (int i = first; i < last; ++i) {
        // the offset from the start of the current layer; helps to map
        // positions
        int offset = i - first;
        // save the top element before it gets overwritten
        int top = matrix[first][i];
        // move the left element to the top
        matrix[first][i] = matrix[last - offset][first];
        // move the bottom element to the left
        matrix[last - offset][first] = matrix[last][last - offset];
        // move the right element to the bottom
        matrix[last][last - offset] = matrix[i][last];
        // move the saved top element to the right
        matrix[i][last] = top;
      }
    }
  }
};
