// HoNooD <honood@gmail.com>
// 2024.07.10 09:14

// 72. Edit Distance
// https://leetcode.com/problems/edit-distance/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Edit_distance
// https://en.wikipedia.org/wiki/Dynamic_programming

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Dynamic Programming (DP)
class Solution {
public:
  int minDistance(string const& word1, string const& word2) {
    if (word1 == word2) {
      return 0;
    }

    int m = word1.size();
    int n = word2.size();

    // create a 2D DP array
    //
    // Note: `dp[i][j]` represents the minimum number of operations required to
    // convert the first `i` characters of `word1` to the first `j` characters
    // of `word2`
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // initialize the DP array
    for (int i = 0; i <= m; ++i) {
      // deleting all characters from `word1`
      dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
      // inserting all characters of `word2`
      dp[0][j] = j;
    }

    // fill the DP array
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          // no operation needed if characters match
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = std::min({
                       dp[i - 1][j - 1], // replace
                       dp[i][j - 1],     // insert
                       dp[i - 1][j]      // delete
                     }) + 1;
        }
      }
    }

    return dp[m][n];
  }

  int min_distance_debug(string const& word1, string const& word2) {
    int m = word1.size();
    int n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    struct Op {
      enum class T { none, equal, deletion, insertion, substitution } t;
      int i, j;
    };
    vector<vector<Op>> ops(m + 1, vector<Op>(n + 1));

    for (int i = 0; i <= m; ++i) {
      dp[i][0] = i;
      if (i > 0) {
        ops[i][0] = {Op::T::deletion, i - 1, 0};
      }
    }
    for (int j = 0; j <= n; ++j) {
      dp[0][j] = j;
      if (j > 0) {
        ops[0][j] = {Op::T::insertion, 0, j - 1};
      }
    }

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
          ops[i][j] = {Op::T::equal, i - 1, j - 1};
        } else {
          int prev_state = std::min({
                             dp[i - 1][j - 1], // replace
                             dp[i][j - 1],     // insert
                             dp[i - 1][j]      // delete
                           });
          dp[i][j] = prev_state + 1;

          if (prev_state == dp[i - 1][j - 1]) {
            ops[i][j] = {Op::T::substitution, i - 1, j - 1};
          } else if (prev_state == dp[i][j - 1]) {
            ops[i][j] = {Op::T::insertion, i, j - 1};
          } else if (prev_state == dp[i - 1][j]) {
            ops[i][j] = {Op::T::deletion, i - 1, j};
          }
        }
      }
    }

    // backtrack to find the edit operations
    vector<Op> edit_ops{};
    for (int i = m, j = n; i > 0 || j > 0;) {
      Op op = ops[i][j];
      if (op.t != Op::T::equal) {
        edit_ops.emplace_back(op);
      }

      i = op.i;
      j = op.j;
    }
    std::reverse(edit_ops.begin(), edit_ops.end());

    // adjust indices of edit operations to reflect changes in the current string
    vector<Op> adjusted_edit_ops{};
    for (auto const& op : edit_ops) {
      int index = op.i;
      for (auto const& adj_op : adjusted_edit_ops) {
        if (adj_op.t == Op::T::insertion && adj_op.i <= index) {
          ++index;
        } else if (adj_op.t == Op::T::deletion && adj_op.i < index) {
          --index;
        }
      }
      adjusted_edit_ops.push_back({op.t, index, op.j});
    }

    // print the transformation process
    string curr{word1};
    cout << "< START > " << std::quoted(curr) << '\n';
    for (int i = 0; i < adjusted_edit_ops.size(); ++i) {
      Op const& op = adjusted_edit_ops[i];
      if (op.t == Op::T::insertion) {
        curr.insert(op.i, 1, word2[op.j]);
        cout << std::format(R"(({:>2}) [INSERT ] '{}' at position {}: "{}")", i + 1, word2[op.j], op.i, curr) << '\n';
      } else if (op.t == Op::T::deletion) {
        char c = curr[op.i];
        curr.erase(op.i, 1);
        cout << std::format(R"(({:>2}) [DELETE ] '{}' at position {}: "{}")", i + 1, c, op.i, curr) << '\n';
      } else if (op.t == Op::T::substitution) {
        char c = curr[op.i];
        curr[op.i] = word2[op.j];
        cout << std::format(R"(({:>2}) [REPLACE] '{}' at position {} with '{}': "{}")", i + 1, c, op.i, word2[op.j], curr) << '\n';
      }
    }
    if (curr != word2) {
      throw std::runtime_error(std::format(R"(Failed to transform "{}" to "{}". Current state: "{}")", word1, word2, curr));
    }
    cout << "<  END  > " << std::quoted(curr) << '\n';

    return dp[m][n];
  }
};

// Recursive
//
// Note: result in Time Limit Exceeded (TLE)
class Solution_2 {
public:
  int minDistance(string const& word1, string const& word2) {
    if (word1 == word2) {
      return 0;
    }

    return impl(word1, word2, word1.size(), word2.size());
  }

private:
  int impl(string const& word1, string const& word2, int i, int j) {
    // if `word1` is empty, insert all characters of `word2`
    if (i == 0) {
      return j;
    }

    // if `word2` is empty, delete all characters of `word1`
    if (j == 0) {
      return i;
    }

    // characters match, move to next
    if (word1[i - 1] == word2[j - 1]) {
      return impl(word1, word2, i - 1, j - 1);
    }

    return std::min({
             impl(word1, word2, i - 1, j),    // delete
             impl(word1, word2, i, j - 1),    // insert
             impl(word1, word2, i - 1, j - 1) // replace
           }) + 1;
  }
};

// Recursive with Memoization
class Solution_3 {
public:
  int minDistance(string const& word1, string const& word2) {
    if (word1 == word2) {
      return 0;
    }

    int m = word1.size();
    int n = word2.size();
    // `memo[i][j]` represents the minimum edit distance between the first `i`
    // characters of `word1` and the first `j` characters of `word2`
    //
    // initialized with `-1` to indicate that no subproblems have been solved yet
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    return impl(word1, word2, m, n, memo);
  }

private:
  int impl(string const& word1, string const& word2, int i, int j, vector<vector<int>>& memo) {
    // if `word1` is empty, insert all characters of `word2`
    if (i == 0) {
      return j;
    }

    // if `word2` is empty, delete all characters of `word1`
    if (j == 0) {
      return i;
    }

    // return previously computed result
    if (memo[i][j] != -1) {
      return memo[i][j];
    }

    if (word1[i - 1] == word2[j - 1]) {
      memo[i][j] = impl(word1, word2, i - 1, j - 1, memo);
    } else {
      memo[i][j] = std::min({
                     impl(word1, word2, i - 1, j, memo),    // delete
                     impl(word1, word2, i, j - 1, memo),    // insert
                     impl(word1, word2, i - 1, j - 1, memo) // replace
                   }) + 1;
    }

    return memo[i][j];
  }
};
