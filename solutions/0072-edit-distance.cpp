// HoNooD <honood@gmail.com>
// 2024.07.10 09:14

// 72. Edit Distance
// https://leetcode.com/problems/edit-distance/description/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/edit-distance/description/?envType=study-plan-v2&envId=leetcode-75

// Edit distance
// https://en.wikipedia.org/wiki/Edit_distance

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int minDistance(string word1, string word2) {
    return min_distance_v1(std::move(word1), std::move(word2));
  }

private:
  // - Time complexity: O(m * n)
  // - Space complexity: O(m * n)
  int min_distance_v1(string const& word1, string const& word2) {
    int m = word1.size();
    int n = word2.size();

    // dp[i][j]: minimun cost to convert word1[0...i-1] to word2[0...j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Initialize base cases
    // Convert empty string to word2[0...j-1] requires j inserts
    for (int j = 0; j <= n; ++j) {
      dp[0][j] = j;
    }
    // Convert word1[0...i-1] to empty string requires i deletions
    for (int i = 0; i <= m; ++i) {
      dp[i][0] = i;
    }

    // Fill the dp table
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        // If the last characters are the same
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1]; // No operation needed
        } else {
          // If the last characters are different, consider 3 operations
          // Insert word2[j-1] into word1
          int insert_cost = dp[i][j - 1];
          // Delete word1[i-1] from word1
          int delete_cost = dp[i - 1][j];
          // Replace word1[i-1] with word2[j-1]
          int replace_cost = dp[i - 1][j - 1];

          dp[i][j] = std::min({insert_cost, delete_cost, replace_cost}) + 1;
        }
      }
    }

    return dp[m][n];
  }

  // - Time complexity: O(m * n)
  // - Space complexity: O(min(m, n))
  int min_distance_v2(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();

    // Optimize space: Ensure n is the smaller dimension if possible
    if (m < n) {
      word1.swap(word2);
      std::swap(m, n);
    }

    assert(n <= m);

    // dp[j] stores the minimum cost to convert word1's prefix to word2[0...j-1]
    // using the previous row's information
    vector<int> dp(n + 1);

    // Initialize base case (equivalent to dp[0][j] = j)
    for (int j = 0; j <= n; ++j) {
      dp[j] = j;
    }

    // ┼────────────┼──────────┼
    // │ (i-1, j-1) │ (i-1, j) │
    // ┼────────────┼──────────┼
    // │ (i, j-1)   │ (i, j)   │
    // ┼────────────┼──────────┼

    // Iterate through word1 (rows in the conceptual 2D DP table)
    for (int i = 1; i <= m; ++i) {
      // Store the value of dp[i-1][0] before it gets updated
      // This will be the 'upper-left' value for the first element (j=1)
      int prev_diag = dp[0];

      // Update the base case for the current row (equivalent to dp[i][0] = i)
      dp[0] = i;

      // Iterate through word2 (columns)
      for (int j = 1; j <= n; ++j) {
        // Store dp[j] before updating it. This is dp[i-1][j]
        int temp = dp[j];

        if (word1[i - 1] == word2[j - 1]) {
          // Characters match, cost is from diagonal dp[i-1][j-1]
          dp[j] = prev_diag;
        } else {
          // Characters differ, take min of insert, delete, replace
          // dp[j-1]   is dp[i][j-1] (insert)
          // dp[j]     is dp[i-1][j] (delete)
          // prev_diag is dp[i-1][j-1] (replace)
          dp[j] = std::min({dp[j - 1], dp[j], prev_diag}) + 1;
        }

        // Update prev_diag for the next iteration (j+1).
        // The 'temp' value (dp[i-1][j]) becomes the 'upper-left' for j+1
        prev_diag = temp;
      }
    }

    return dp[n];
  }

  // - Time complexity: O(m * n)
  // - Space complexity: O(m * n) + O(m + n)
  int min_distance_v3(string const& word1, string const& word2) {
    int m = word1.length();
    int n = word2.length();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));

    // Helper function for recursion with memoization
    // Calculates min distance for word1[0...i-1] and word2[0...j-1]
    std::function<int(int, int)> solve
      = [&solve, &word1, &word2, &memo](int i, int j) {
          // Base case: If word1 is empty, insert all characters of word2
          if (i == 0) return j;
          // Base case: If word2 is empty, delete all characters of word1
          if (j == 0) return i;

          if (memo[i][j] != -1) return memo[i][j];

          // If last characters match
          if (word1[i - 1] == word2[j - 1]) {
            memo[i][j] = solve(i - 1, j - 1); // No operation needed
          } else {
            // If last characters differ, consider 3 operations
            int insert_cost = solve(i, j - 1);
            int delete_cost = solve(i - 1, j);
            int replace_cost = solve(i - 1, j - 1);
            memo[i][j] = std::min({insert_cost, delete_cost, replace_cost}) + 1;
          }

          return memo[i][j];
        };

    return solve(m, n);
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
            dp[i][j - 1], // insert
            dp[i - 1][j] // delete
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

    // adjust indices of edit operations to reflect changes in the current
    // string
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
        cout << std::format(R"(({:>2}) [INSERT ] '{}' at position {}: "{}")",
                            i + 1, word2[op.j], op.i, curr)
             << '\n';
      } else if (op.t == Op::T::deletion) {
        char c = curr[op.i];
        curr.erase(op.i, 1);
        cout << std::format(R"(({:>2}) [DELETE ] '{}' at position {}: "{}")",
                            i + 1, c, op.i, curr)
             << '\n';
      } else if (op.t == Op::T::substitution) {
        char c = curr[op.i];
        curr[op.i] = word2[op.j];
        cout << std::format(
          R"(({:>2}) [REPLACE] '{}' at position {} with '{}': "{}")", i + 1, c,
          op.i, word2[op.j], curr)
             << '\n';
      }
    }
    if (curr != word2) {
      throw std::runtime_error(
        std::format(R"(Failed to transform "{}" to "{}". Current state: "{}")",
                    word1, word2, curr));
    }
    cout << "<  END  > " << std::quoted(curr) << '\n';

    return dp[m][n];
  }
};
