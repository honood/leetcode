// HoNooD
// 2022.06.10 01:25

// https://leetcode.com/problems/zigzag-conversion/

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
class Solution {
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

int main(int argc, char* argv[]) {
  int num_rows = 4;
  std::string s{"MyNameIsHoNooD"};
  
  Solution solution;
  std::cout << solution.convert(s, 3) << std::endl;
  std::cout << solution.convert(s, 4) << std::endl;
  std::cout << solution.convert("A", 3) << std::endl;

  return 0;
}
