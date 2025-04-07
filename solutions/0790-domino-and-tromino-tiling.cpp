// HoNooD <honood@gmail.com>
// 2025.04.06 15:30
//
// 790. Domino and Tromino Tiling
// https://leetcode.com/problems/domino-and-tromino-tiling/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int numTilings(int n) {
    return num_tilings_v1(n);
  }

private:
  // # Core Idea: Dynamic Programming
  //
  // This problem exhibits optimal substructure and overlapping subproblems,
  // making it suitable for dynamic programming. The key is to define states
  // that effectively capture all relevant configurations of the tiling boundary
  // as we build the solution column by column.
  //
  // ## State Definition
  //
  // Consider the state after tiling up to column `i`:
  //
  // 1. `dp[i][0]`: Represents the total number of ways to fully tile the `2 x
  // i` rectangular area.
  // 2. `dp[i][1]`: Represents the number of ways to tile the `2 x i` area such
  // that the top-right cell (`(1, i)`) is uncovered, while all other cells up
  // to column `i` are covered.
  // 3. `dp[i][2]`: Represents the number of ways to tile the `2 x i` area
  // such that the bottom-right cell (`(2, i)`) is uncovered, while all other
  // cells up to column `i` are covered.
  //
  // ## State Transition Derivation
  //
  // 1. Deriving `dp[i][0]` (Fully Tiled `2 x i`): How can we arrive at a
  // completely tiled `2 x i` board?
  //     - From a fully tiled `2 x (i-1)` board (`dp[i-1]`): Place a vertical
  //     Domino in column `i` (covering `(1, i)` and `(2, i)`).
  //     - From a fully tiled `2 x (i-2)` board (`dp[i-2]`): Place two
  //     horizontal Dominoes covering columns `i-1` and `i`.
  //     - From a partially tiled `2 x (i-1)` board with the top cell `(1, i-1)`
  //     uncovered (`dp[i-1][1]`): Place an L-shaped Tromino covering `(1,
  //     i-1)`, `(1, i)`, and `(2, i)`. This fills the gap and completes column
  //     `i`.
  //     - From a partially tiled `2 x (i-1)` board with the bottom cell `(2,
  //     i-1)` uncovered (`dp[i-1][2]`): Place an L-shaped Tromino covering
  //     `(2, i-1)`, `(1, i)`, and `(2, i)`. This fills the gap and completes
  //     column `i`.
  //     - Therefore: `dp[i][0] = dp[i-1][0] + dp[i-2][0] + dp[i-1][1] +
  //     dp[i-1][2]`
  //
  // 2. Deriving `dp[i][1]` (Top-Right Cell `(1, i)` Uncovered): How can we
  // reach a state where `(1, i)` is the only uncovered cell in column `i`?
  //     - From a fully tiled `2 x (i-2)` board (`dp[i-2][0]`): Place an
  //     L-shaped Tromino covering `(1, i-1)`, `(2, i-1)`, and `(2, i)`. This
  //     leaves cell `(1, i)` uncovered.
  //     - From a partially tiled `2 x (i-1)` board with `(2, i-1)` uncovered
  //     (`dp[i-1][2]`): Place a horizontal Domino covering `(2, i-1)` and
  //     `(2, i)`. This fills the gap and covers `(2, i)`, leaving `(1, i)`
  //     uncovered (as `(1, i-1)` was already covered).
  //     - Therefore: `dp[i][1] = dp[i-2][0] + dp[i-1][2]`
  //
  // 3. Deriving `dp[i][2]` (Bottom-Right Cell `(2, i)` Uncovered):
  // (Symmetric to `dp[i][1]`)
  //     - From a fully tiled `2 x (i-2)` board (`dp[i-2][0]`): Place an
  //     L-shaped Tromino covering `(1, i-1)`, `(2, i-1)`, and `(1, i)`. This
  //     leaves cell `(2, i)` uncovered.
  //     - From a partially tiled `2 x (i-1)` board with `(1, i-1)` uncovered
  //     (`dp[i-1][1]`): Place a horizontal Domino covering `(1, i-1)` and `(1,
  //     i)`. This fills the gap and covers `(1, i)`, leaving `(2, i)`
  //     uncovered.
  //     - Therefore: `dp[i][2] = dp[i-2][0] + dp[i-1][1]`
  //
  // ## Derivation of the Simplified Recurrence Relation
  //
  // 1. Symmetry: Observe that by symmetry, the number of ways to tile with the
  // top-right cell uncovered is equal to the number of ways with the
  // bottom-right cell uncovered.
  //     - `dp[n][1] = dp[n][2]`
  //
  // 2. Notation: Let's simplify the notation:
  //     - Let `f(n) = dp[n][0]` (number of ways to fully tile a `2 x n` board).
  //     - Let `p(n) = dp[n][1] = dp[n][2]` (number of ways for a partially
  //     tiled `2 x n` board ending in a single gap).
  //
  // 3. Initial Recurrences: The state transitions derived earlier can now be
  // written as:
  //     - `f(n) = f(n-1) + f(n-2) + 2*p(n-1)`                           --- (1)
  //     - `p(n) = f(n-2) + p(n-1)`                                      --- (2)
  //
  // 4. Algebraic Manipulation: Our goal is to find a recurrence relation solely
  // in terms of `f(n)`.
  //     - Shift the index in equation (1) by replacing `n` with `n-1`:
  //         - `f(n-1) = f(n-2) + f(n-3) + 2*p(n-2)`                     --- (3)
  //     - Subtract equation (3) from equation (1):
  //         - `f(n) - f(n-1) = (f(n-1) - f(n-3)) + 2*(p(n-1) - p(n-2))`
  //         - Rearranging gives: `f(n) = 2*f(n-1) - f(n-3) + 2*(p(n-1) -
  //         p(n-2))`                                                    --- (4)
  //     - From equation (2), rearrange to express the difference in `p`:
  //         - `p(n) - p(n-1) = f(n-2)`
  //     - Shift the index in this difference equation by replacing `n` with
  //     `n-1`:
  //         - `p(n-1) - p(n-2) = f(n-3)`                                --- (5)
  //     - Substitute the result from (5) into equation (4):
  //         - `f(n) = 2*f(n-1) - f(n-3) + 2*f(n-3)`
  //
  // 5. Final Simplified Recurrence: This simplifies to the single recurrence
  // relation for the fully tiled state:
  //     - `f(n) = 2*f(n-1) + f(n-3)`
  //
  // ## Correctness of Intermediate Modulo Operations in DP Calculation
  //
  // The dynamic programming solutions for the Domino and Tromino Tiling problem
  // involve recurrence relations where the number of ways can grow very large.
  // To manage this and prevent integer overflow, we apply the modulo operator
  // (`% MOD`) frequently within the calculation loop. The mathematical validity
  // of this approach rests on the fundamental properties of modular arithmetic,
  // specifically as they apply to the operations used in our recurrence
  // relations.
  //
  // ### 1. Relevant Properties of Modular Arithmetic:
  //
  // For any integers `a`, `b`, and a positive integer modulus `m`:
  //
  // - Addition Congruence: `(a + b) % m = ((a % m) + (b % m)) % m`
  // - Multiplication Congruence: `(a * b) % m = ((a % m) * (b % m)) % m`
  // - Subtraction Congruence: `(a - b) % m = ((a % m) - (b % m) + m) % m`
  //
  // These properties state that the result of an addition or multiplication
  // followed by a modulo operation is the same as taking the modulo of the
  // operands first, performing the operation, and then taking the modulo of the
  // result.
  //
  // References:
  // - [Modular arithmetic](https://en.wikipedia.org/wiki/Modular_arithmetic)
  //
  // ### 2. Operations in the Target Recurrence Relations:
  //
  // The dynamic programming recurrence relations we implement in the code
  // involve only addition and multiplication (implicitly, e.g., in `2 *
  // f(n-1)`):
  //
  // - Three-State:Additions only.
  //     - `dp[i][0] = (dp[i-1][0] + dp[i-2][0] + dp[i-1][1] + dp[i-1][2]) %
  //     MOD`
  //     - `dp[i][1] = (dp[i-2][0] + dp[i-1][2]) % MOD`
  //     - `dp[i][2] = (dp[i-2][0] + dp[i-1][1]) % MOD`
  // - Simplified One-State:
  //     - `f(n) = (2 * f(n-1) + f(n-3)) % MOD`, involving multiplication and
  //     addition.
  //
  // (Note: While subtraction was used algebraically during the derivation of
  // the simplified recurrence, the final computational step implemented in the
  // code does not involve subtraction. Therefore, the subtraction congruence
  // property is not directly needed to justify the modulo operations within the
  // loop's computation.)
  //
  // **Note:** f(n) = 2 * f(n-1) + f(n-3) = f(n-1) + f(n-1) + f(n-3).
  // We need the addition congruence property for three terms:
  // (a + b + c) % m = ((a % m) + (b % m) + (c % m)) % m.
  // How to prove this derived property?
  // Assume (by definition of modulo):
  //   a = p1 * m + q1  (so a % m = q1)
  //   b = p2 * m + q2  (so b % m = q2)
  //   c = p3 * m + q3  (so c % m = q3)
  // LHS: (a + b + c) % m
  //      = ((p1 + p2 + p3) * m + (q1 + q2 + q3)) % m
  //      = (q1 + q2 + q3) % m
  // RHS: ((a % m) + (b % m) + (c % m)) % m
  //      = (q1 + q2 + q3) % m
  // Since LHS = RHS, the property is proven.
  //
  // ### 3. Proof of Correctness (via Induction):
  //
  // We can formally demonstrate the correctness using induction:
  //
  // - Base Case: The initialized DP values (e.g., for `i=0, 1` or `i=1, 2`) are
  // the correct counts modulo `MOD`. `dp[base][state] = True_Count(base, state)
  // % MOD`.
  // - Inductive Hypothesis (IH): Assume that for all indices `k < i`, the
  // stored value `dp[k][state]` (or `f(k)`) is equal to the true count modulo
  // `MOD`: `dp[k][state] == True_Count(k, state) % MOD`.
  // - Inductive Step: We show that calculating `dp[i][state]` (or `f(i)`) using
  // the recurrence and intermediate modulo operations yields `True_Count(i,
  // state) % MOD`. Let's use the simplified recurrence `f(n) = 2*f(n-1) +
  // f(n-3)` as an example:
  //
  //     - True Count: `True_f(i) = 2 * True_f(i-1) + True_f(i-3)`
  //     - Desired Value: `True_f(i) % MOD`
  //     - Applying Congruence Properties (Deriving the Mathematical Target):
  //         `True_f(i) % MOD = (2 * True_f(i-1) + True_f(i-3)) % MOD`
  //         `= ( (2 * True_f(i-1)) % MOD + (True_f(i-3) % MOD) ) % MOD` (by
  //         Addition Congruence)
  //         `= ( ((2 % MOD) * (True_f(i-1) % MOD)) % MOD + (True_f(i-3) % MOD)
  //         ) % MOD` (by Multiplication Congruence)
  //         Let's call this the Target Expression.
  //
  //     - Code Calculation (What the code computes):
  //         `Code_f(i) = (2 * f(i-1) + f(i-3)) % MOD`
  //         Substitute IH (`f(k) = True_f(k) % MOD`):
  //         `Code_f(i) = (2 * (True_f(i-1) % MOD) + (True_f(i-3) % MOD)) % MOD`
  //         Let's call this the Code Expression.
  //
  //     - Equivalence (Comparing Target and Code Expressions): Now, we need to
  //     rigorously show why the Target Expression is equivalent (under modulo
  //     `MOD`) to the Code Expression.
  //         - Target Expression: `( ((2 % MOD) * (True_f(i-1) % MOD)) % MOD +
  //         (True_f(i-3) % MOD) ) % MOD`
  //         - Code Expression: `( (2 * (True_f(i-1) % MOD)) + (True_f(i-3) %
  //         MOD) ) % MOD`
  //
  //         Let's analyze the difference:
  //         1.  `2 % MOD` vs `2`: Since `MOD = 10^9 + 7` is greater than 2, `2
  //         % MOD` is simply `2`. So, `(2 % MOD)` can be replaced by `2` in the
  //         Target Expression.
  //         2.  Internal Modulo: The Target Expression has `(... % MOD + ...) %
  //         MOD`, while the Code Expression has `(... + ...) % MOD`. Let `X = 2
  //         * (True_f(i-1) % MOD)` and `Y = True_f(i-3) % MOD`.
  //             - Target form: `( (X % MOD) + Y ) % MOD`
  //             - Code form: `( X + Y ) % MOD`
  //             Are these equivalent? Yes. By the Addition Congruence property:
  //             `(X + Y) % MOD = ((X % MOD) + (Y % MOD)) % MOD`.
  //             Since `Y` is already `True_f(i-3) % MOD`, `Y % MOD` is just
  //             `Y`. Therefore, `(X + Y) % MOD = ((X % MOD) + Y) % MOD`. This
  //             shows that applying an extra modulo to the term `X` before
  //             adding `Y` does not change the final result when the entire sum
  //             is taken modulo `MOD`.
  //
  //         - Conclusion of Equivalence: Based on points 1 and 2, the Target
  //         Expression simplifies and is mathematically equivalent to the Code
  //         Expression under modulo `MOD`. The value computed by the code is
  //         indeed the desired `True_f(i) % MOD`.
  //
  //     The same logic applies to the three-state recurrences, primarily
  //     relying on the addition congruence property.
  //
  // ### 4. Practical Necessity:
  //
  // Applying the modulo operation at each step (or after each logical group of
  // additions/multiplications) is crucial to prevent integer overflow. Without
  // it, the intermediate `True_Count` values would quickly exceed the maximum
  // value representable by standard integer types (like `int` or `long long`),
  // leading to incorrect results.
  //
  // ### Conclusion:
  //
  // The use of intermediate modulo operations in the dynamic programming
  // calculation for this problem is mathematically sound due to the congruence
  // properties of modular arithmetic with respect to addition and
  // multiplication (the operations present in the implemented recurrences).
  // This practice is also practically essential to avoid integer overflow and
  // ensure the final result is the correct count modulo `MOD`.
  //
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int num_tilings_v1(int n) {
    // Base case n=0 MUST be handled first to avoid out-of-bounds access
    // when trying to initialize dp[1] if dp table size is 1.
    if (n == 0) {
      return 1; // One way to tile a 2x0 board (do nothing)
    }
    // n=1 case is correctly handled by the initialization and loop logic below.

    constexpr int MOD = 1e9 + 7;

    // Create the DP table. dp[i][state]
    //
    // state 0: Fully tiled 2xi board
    // state 1: Tiled 2xi board with top-right cell (1, i) uncovered
    // state 2: Tiled 2xi board with bottom-right cell (2, i) uncovered
    //
    // Note: Use long long for intermediate calculations to prevent overflow
    // before modulo
    vector<vector<long long>> dp(n + 1, vector<long long>(3));
    // Base case i=0:
    dp[0][0] = 1; // Fully tiled 2x0
    dp[0][1] = 0; // Impossible to have a gap in 2x0
    dp[0][2] = 0; // Impossible to have a gap in 2x0
    // Base case i=1:
    dp[1][0] = 1; // Fully tiled 2x1 (one vertical domino)
    dp[1][1] = 0; // Cannot end with a top gap at i=1
    dp[1][2] = 0; // Cannot end with a bottom gap at i=1

    // Iterate and fill the DP table starting from i=2
    // The loop condition i <= n correctly handles n=1 (loop doesn't run)
    for (int i = 2; i <= n; ++i) {
      dp[i][0]
        = (dp[i - 1][0] + dp[i - 2][0] + dp[i - 1][1] + dp[i - 1][2]) % MOD;
      dp[i][1] = (dp[i - 2][0] + dp[i - 1][2]) % MOD;
      dp[i][2] = (dp[i - 2][0] + dp[i - 1][1]) % MOD;
    }

    return static_cast<int>(dp[n][0]);
  }

  int num_tilings_v1_2(int n) {
    // Base case n=0 MUST be handled as this approach starts from i=1.
    if (n == 0) {
      return 1;
    }
    // Base case n=1 MUST be handled to avoid out-of-bounds access
    // when trying to initialize dp[2] if dp table size is 2.
    if (n == 1) {
      return 1;
    }
    // n=2 case is correctly handled by the initialization and loop logic below.

    constexpr int MOD = 1e9 + 7;

    // DP table size needs to accommodate n
    vector<vector<long long>> dp(n + 1, vector<long long>(3));
    // Base case i=1:
    dp[1][0] = 1; // Fully tiled 2x1
    dp[1][1] = 0; // Cannot end with a top gap
    dp[1][2] = 0; // Cannot end with a bottom gap
    // Base case i=2:
    dp[2][0] = 2; // Fully tiled 2x2 (|| or =)
    dp[2][1] = 1; // Tile with top-right gap (needs Tromino from 2x0)
    dp[2][2] = 1; // Tile with bottom-right gap (needs Tromino from 2x0)

    // Iterate and fill the DP table starting from i=3
    // The loop condition i <= n correctly handles n=2 (loop doesn't run)
    for (int i = 3; i <= n; ++i) {
      dp[i][0]
        = (dp[i - 1][0] + dp[i - 2][0] + dp[i - 1][1] + dp[i - 1][2]) % MOD;
      dp[i][1] = (dp[i - 2][0] + dp[i - 1][2]) % MOD;
      dp[i][2] = (dp[i - 2][0] + dp[i - 1][1]) % MOD;
    }

    return static_cast<int>(dp[n][0]);
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int num_tilings_v2(int n) {
    // Base cases
    if (n == 0) return 1;
    if (n == 1) return 1;

    constexpr int MOD = 1e9 + 7;

    // clang-format off

    // dp_full_i_1: stores dp[i-1], number of ways to fully tile 2x(i-1)
    // dp_full_i_2: stores dp[i-2], number of ways to fully tile 2x(i-2)
    // dp_part_i_1: stores dp_partial[i-1], number of ways for partial tiling ending at i-1

    // Initialize for calculation of i=2
    // dp[0] = 1, dp[1] = 1
    // dp_partial[0] = 0 (no way to leave a gap in 2x0)
    // dp_partial[1] = dp[-1] + dp_partial[0] -> we need dp_partial[1]
    // Let's calculate dp_partial[1]: Need dp[-1] + dp_partial[0]. Assume dp[-1]=0, dp_part[0]=0 -> dp_part[1]=0
    // Let's calculate dp_partial[2]: Need dp[0] + dp_partial[1] = 1 + 0 = 1
    // Let's calculate dp[2]: Need dp[1] + dp[0] + 2*dp_partial[1] = 1 + 1 + 2*0 = 2. Matches.

    long long dp_full_i_2 = 1; // Corresponds to dp[0]
    long long dp_full_i_1 = 1; // Corresponds to dp[1]
    long long dp_part_i_1 = 0; // Corresponds to dp_partial[1]

    // Iterate from i = 2 to n
    for (int i = 2; i <= n; ++i) {
      // Calculate current dp_partial[i] using previous states (i-1 and i-2)
      long long dp_part_i = (dp_full_i_2 + dp_part_i_1) % MOD;
      // Calculate current dp[i] using previous states (i-1 and i-2)
      long long dp_full_i = (dp_full_i_1 + dp_full_i_2 + (2 * dp_part_i_1) % MOD) % MOD;

      // Update states for the next iteration (i+1)
      // The old dp[i-1] becomes the new dp[i-2]
      dp_full_i_2 = dp_full_i_1;
      // The old dp_partial[i-1] becomes the new dp_partial[i-2] conceptually,
      // but we need the calculated dp_part_i for the next step's dp_partial[i-1] role.
      dp_part_i_1 = dp_part_i;
      // The calculated dp_full_i becomes the new dp[i-1]
      dp_full_i_1 = dp_full_i;
    }
    // clang-format on

    // After the loop finishes (i=n), dp_full_i_1 holds the value for dp[n]
    return dp_full_i_1;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int num_tilings_v3(int n) {
    // Base cases for small n
    if (n == 0) return 1;
    if (n == 1) return 1;

    constexpr int MOD = 1e9 + 7;

    // dp[i] stores the number of ways to fully tile a 2xi board
    vector<long long> dp(n + 1);
    // Initialize base cases
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;

    // Fill the dp table using simplified recurrence relation
    // f(n) = 2 * f(n-1) + f(n-3)
    for (int i = 3; i <= n; ++i) {
      dp[i] = (2 * dp[i - 1] + dp[i - 3]) % MOD;
    }

    return static_cast<int>(dp[n]);
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int num_tilings_v4(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;

    constexpr int MOD = 1e9 + 7;

    long long dp_i_3 = 1; // Stores dp[i-3], initialized to dp[0]
    long long dp_i_2 = 1; // Stores dp[i-2], initialized to dp[1]
    long long dp_i_1 = 2; // Stores dp[i-1], initialized to dp[2]

    long long dp_i = dp_i_1;
    for (int i = 3; i <= n; ++i) {
      // f(n) = 2 * f(n-1) + f(n-3)
      dp_i = ((2 * dp_i_1) + dp_i_3) % MOD;

      // Shift values for next iteration
      dp_i_3 = dp_i_2;
      dp_i_2 = dp_i_1;
      dp_i_1 = dp_i;
    }
    return static_cast<int>(dp_i);
  }

  // 矩阵快速幂 (Matrix Exponentiation)
  // https://en.wikipedia.org/wiki/Matrix_exponential
  // https://en.wikipedia.org/wiki/Exponentiation_by_squaring
  //
  // f(n) = 2 * f(n-1) + f(n - 3)
  //      = 2 * f(n-1) + 0 * f(n-2) + 1 * f(n-3)
  //
  // [f(n)  ]   [2 0 1]   [f(n-1)]
  // [f(n-1)] = [1 0 0] x [f(n-2)]
  // [f(n-2)]   [0 1 0]   [f(n-3)]
  //
  // - Time complexity: O(log N). Matrix exponentiation takes O(k^3 * log N)
  // time, where k=3 is the dimension of the matrix. Because k is a constant,
  // the overall time complexity simplifies to O(log N).
  // - Space complexity: O(1). Storing the matrices requires O(k^2) space (where
  // k=3). As k is constant, the space complexity is O(1) (constant space).
  int num_tilings_v5(int n) {
    // Handle base cases directly
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;

    // Define the transition matrix M based on dp[i] = 2*dp[i-1] + dp[i-3]
    matrix M = {
      {2, 0, 1},
      {1, 0, 0},
      {0, 1, 0},
    };

    // We need to calculate M^(n-2) because the recurrence relates S[n] to S[2]
    matrix M_pow_n_minus_2 = matrix_pow(M, n - 2);

    // Define the initial state vector S[2] = [dp[2], dp[1], dp[0]]^T
    // Represent S[2] as a 3x1 matrix for multiplication
    matrix S2 = {{2}, {1}, {1}};

    // Calculate the final state vector S[n] = M^(n-2) * S[2]
    matrix Sn = multiply(M_pow_n_minus_2, S2);

    // The result dp[n] is the top element (index [0][0]) of the resulting
    // vector Sn
    return Sn[0][0];
  }

  // Define matrix type alias for convenience
  using matrix = vector<vector<long long>>;

  // Function to multiply two matrices (a * b) modulo MOD
  matrix multiply(matrix const& a, matrix const& b) {
    // Ensure dimensions are compatible for multiplication
    int r1 = a.size();
    int c1 = a[0].size();
    int r2 = b.size();
    int c2 = b[0].size();

    if (c1 != r2) {
      throw invalid_argument("Matrix dimensions mismatch for multiplication");
    }

    constexpr int MOD = 1e9 + 7;

    // Initialize result matrix with zeros
    matrix result(r1, vector<long long>(c2, 0));

    // Perform matrix multiplication
    for (int i = 0; i < r1; ++i) {
      for (int j = 0; j < c2; ++j) {
        for (int k = 0; k < c1; ++k) {
          result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
        }
      }
    }
    return result;
  }

  // Function for matrix exponentiation (base^exp) using binary exponentiation
  matrix matrix_pow(matrix base, int exp) {
    int n = base.size();
    // Ensure matrix is square
    if (n == 0 || base[0].size() != n) {
      throw invalid_argument("Matrix must be square for exponentiation");
    }

    // Initialize result matrix as identity matrix
    matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
      result[i][i] = 1;
    }

    // Binary exponentiation loop
    while (exp > 0) {
      // If exponent is odd, multiply result by base
      if (exp % 2 == 1) {
        result = multiply(result, base);
      }
      // Square the base for the next iteration
      base = multiply(base, base);
      // Halve the exponent
      exp /= 2;
    }
    return result;
  }
};
