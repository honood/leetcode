// HoNooD <honood@gmail.com>
// 2025.03.26 08:30

// 1137. N-th Tribonacci Number
// https://leetcode.com/problems/n-th-tribonacci-number/?envType=study-plan-v2&envId=leetcode-75

// https://en.wikipedia.org/wiki/Generalizations_of_Fibonacci_numbers#Tribonacci_numbers

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int tribonacci(int n) {
    return tribonacci_v3(n);
  }

private:
  // Time Limit Exceeded
  //
  // - Time complexity: O(3^n)
  // - Space complexity: O(n)
  int tribonacci_v1(int n) {
    assert(n >= 0);

    std::function<int(int)> tribonacci = [&tribonacci](int n) {
      if (n == 0) return 0;
      if (n == 1) return 1;
      if (n == 2) return 1;

      return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
    };

    return tribonacci(n);
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int tribonacci_v2(int n) {
    assert(n >= 0);

    unordered_map<int, int> memo{};

    std::function<int(int)> tribonacci = [&tribonacci, &memo](int n) {
      if (memo.contains(n)) {
        return memo[n];
      }

      if (n == 0) return 0;
      if (n == 1) return 1;
      if (n == 2) return 1;

      int result = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
      return memo[n] = result;
    };

    return tribonacci(n);
  }

  // https://en.wikipedia.org/wiki/Dynamic_programming
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int tribonacci_v3(int n) {
    assert(n >= 0);

    // Handle base cases
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;

    // Create DP array
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    // Fill the array
    for (int i = 3; i <= n; ++i) {
      dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    return dp[n];
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int tribonacci_v4(int n) {
    assert(n >= 0);

    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;

    int t0 = 0, t1 = 1, t2 = 1, tn;
    for (int i = 3; i <= n; ++i) {
      tn = t0 + t1 + t2;

      t0 = t1;
      t1 = t2;
      t2 = tn;
    }

    return t2;
  }

  // 矩阵快速幂
  // https://en.wikipedia.org/wiki/Matrix_exponential
  // https://en.wikipedia.org/wiki/Exponentiation_by_squaring
  //
  // The Tribonacci sequence follows the recurrence relation:
  //
  // \[
  // T(n) = T(n-1) + T(n-2) + T(n-3)
  // \]
  //
  // This sequence can be represented in matrix form as:
  //
  // \[
  // \begin{bmatrix}
  // T(n+1) \\
  // T(n) \\
  // T(n-1)
  // \end{bmatrix} =
  // \begin{bmatrix}
  // 1 & 1 & 1 \\
  // 1 & 0 & 0 \\
  // 0 & 1 & 0
  // \end{bmatrix}
  // \begin{bmatrix}
  // T(n) \\
  // T(n-1) \\
  // T(n-2)
  // \end{bmatrix}
  // \]
  //
  // The matrix representation allows for efficient computation of Tribonacci
  // numbers through matrix exponentiation techniques, particularly for
  // calculating higher terms in the sequence.
  //
  // - Time complexity: O(log(n))
  // - Space complexity: O(1)
  int tribonacci_v5(int n) {
    assert(n >= 0);

    // Handle base cases
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;

    // Note: Using long long to prevent integer overflow
    using row_t = vector<long long>;
    using matrix_t = vector<row_t>;

    auto multiply = [](matrix_t const& A, matrix_t const& B) {
      matrix_t C(3, row_t(3, 0));
      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          for (int k = 0; k < 3; ++k) {
            C[i][j] += A[i][k] * B[k][j];
          }
        }
      }
      return C;
    }; // multiply

    // Computes A^n using binary exponentiation
    // Time complexity: O(log(n))
    auto matrix_power = [&multiply](matrix_t A, int n) {
      matrix_t result(3, row_t(3, 0));
      // Initialize identity matrix
      for (int i = 0; i < 3; ++i) {
        result[i][i] = 1;
      }

      // Binary exponentiation algorithm
      // Example: A^13 = A^(1101₂) = A^8 * A^4 * A^1
      while (n > 0) {
        if (n % 2 == 1) {
          // If current bit is 1, multiply A^(2^k) to the result
          result = multiply(result, A);
        }
        // A = A^2, A^2, A^4, A^8, ...
        A = multiply(A, A);
        // Right shift, check next bit
        n /= 2;
      }

      return result;
    }; // matrix_power

    /**
     * Define state transition matrix for Tribonacci sequence
     *
     * The recurrence relation can be represented in matrix form:
     * [T(n)  ]   [1 1 1]   [T(n-1)]
     * [T(n-1)] = [1 0 0] × [T(n-2)]
     * [T(n-2)]   [0 1 0]   [T(n-3)]
     *
     * By applying this relation repeatedly:
     * [T(n), T(n-1), T(n-2)] = A^(n-2) × [T(2), T(1), T(0)]
     *                        = A^(n-2) × [1, 1, 0]
     *
     * Therefore, T(n) = A'[0][0] + A'[0][1], where A' = A^(n-2)
     */
    matrix_t A = {
      {1, 1, 1},
      {1, 0, 0},
      {0, 1, 0},
    };

    // Calculate A^(n - 2)
    A = matrix_power(A, n - 2);

    // Compute the final result: T(n) = A'[0][0] + A'[0][1]
    return A[0][0] + A[0][1];
  }
};
