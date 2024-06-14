// HoNooD <honood@gmail.com>
// 2024.06.14 14:16

// 74. Search a 2D Matrix
// https://leetcode.com/problems/search-a-2d-matrix/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Logarithm
// https://en.wikipedia.org/wiki/Analysis_of_algorithms
// https://en.wikipedia.org/wiki/Time_complexity
// https://en.wikipedia.org/wiki/Space_complexity

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// more complex and verbose, and less intuitive
//
// time complexity: O(log(m)) + O(log(n)) = O(log(m) + log(n)) = O(log(m * n))
class Solution {
public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
      return false;
    }

    // binary search to find the potential row
    // time complexity: O(log(m))
    int startRow = 0;
    int endRow = matrix.size() - 1;
    while (startRow <= endRow) {
      int midRow = startRow + (endRow - startRow) / 2;
      if (matrix[midRow][0] == target) {
        return true;
      }

      if (matrix[midRow][0] > target) {
        endRow = midRow - 1;
      } else {
        startRow = midRow + 1;
      }
    }

    // if `startRow` is 0, the target is smaller than the first element of the
    // matrix
    if (startRow == 0) {
      return false;
    }

    // determine the target row
    int targetRow = startRow - 1;

    // binary search in the target row
    // time complexity: O(log(n))
    int startCol = 0;
    int endCol = matrix[0].size() - 1;
    while (startCol <= endCol) {
      int midCol = startCol + (endCol - startCol) / 2;
      if (matrix[targetRow][midCol] == target) {
        return true;
      }

      if (matrix[targetRow][midCol] > target) {
        endCol = midCol - 1;
      } else {
        startCol = midCol + 1;
      }
    }

    return false;
  }
};

// Treat the 2D matrix as a 1D sorted array of length `m * n`, where `m` is the
// number of rows and `n` is the number of columns, and apply binary search.
//
// Recommended: straightforward and concise, and easy to understand
class Solution_2 {
public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
      return false;
    }

    int rows = matrix.size();
    int cols = matrix[0].size();
    int low = 0;
    int high = cols * rows - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      int midVal = matrix[mid / cols][mid % cols];
      if (midVal == target) {
        return true;
      }

      if (midVal < target) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return false;
  }
};
