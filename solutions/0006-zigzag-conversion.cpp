// HoNooD <honood@gmail.com>
// 2024.06.22 12:52

// 6. Zigzag Conversion
// https://leetcode.com/problems/zigzag-conversion/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Best
class Solution {
public:
  string convert(string s, int numRows) {
    assert(numRows > 0);
    if (numRows == 1 || s.size() <= numRows) {
      return s;
    }

    vector<string> rows(numRows);
    int currRow = 0;
    bool goingDown = false;

    for (auto const& c : s) {
      rows[currRow] += c;

      if (currRow == 0 || currRow == numRows - 1) {
        goingDown = !goingDown;
      }
      currRow += goingDown ? 1 : -1;
    }

    string res{};
    for (auto& row : rows) {
      res += row;
    }
    return res;
  }
};

// For this problem,
//
// 1        9          17
// 2     8 10       16 18
// 3   7   11    15    19
// 4 6     12 14       20
// 5       13
//
// is equivalent to
//
// 1    9    17
// 2 8 10 16 18
// 3 7 11 15 19
// 4 6 12 14 20
// 5   13
//
class Solution_2 {
public:
  std::string convert(std::string s, int num_rows) {
    if (s.empty() || num_rows == 1) {
      return s;
    }

    int a = static_cast<int>(s.size());
    int b = num_rows + (num_rows - 2);
    int c = a / b;
    int d = a % b;
    int num_cols = c * 2 + (d == 0 ? 0 : (d > num_rows ? 2 : 1));

    { // [DEBUG]
      std::cout << "num_rows: " << num_rows << std::endl;
      std::cout << "num_cols: " << num_cols << std::endl;
    }

    std::vector<std::vector<char>> matrix(num_rows, std::vector<char>(num_cols, '\0'));

    int s_index = 0;
    for (int j = 0; j < num_cols; ++j) {
      bool inner_break = false;
      for (int i = 0; i < num_rows; ++i) {
        if (s_index >= s.size()) {
          inner_break = true;
          break;
        }

        if (j & 0x1) { // odd column
          if (i == 0 || i == num_rows - 1) {
            continue;
          } else {
            matrix[(num_rows - 1) - i][j] = s[s_index++];
          }
        } else { // even column
          matrix[i][j] = s[s_index++];
        }
      }

      if (inner_break) { break; }
    }

    { // [DEBUG] print matrix
      for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
          char ch = matrix[i][j];
          if (ch == '\0') { ch = ' '; }
          std::cout << ch << " ";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }

    std::string result{};
    for (int i = 0; i < num_rows; ++i) {
      for (int j = 0; j < num_cols; ++j) {
        if (char ch = matrix[i][j]; ch != '\0') {
          result.push_back(ch);
        }
      }
    }

    return result;
  }
};
