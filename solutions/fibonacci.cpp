// HoNooD <honood@gmail.com>
// 2024.07.16 11:27

// https://en.wikipedia.org/wiki/Fibonacci_sequence

/*
$ /opt/homebrew/opt/llvm/bin/clang++ -std=c++11 fibonacci.cpp -o fibonacci && ./fibonacci
$ /opt/homebrew/opt/gcc/bin/g++-14 -std=c++11 fibonacci.cpp -o fibonacci && ./fibonacci
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

long fibonacci_recursive(long n) {
  if (n <= 1) {
    return n;
  }

  return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

long fibonacci_iterative(long n) {
  if (n <= 1) {
    return n;
  }

  long a = 0;
  long b = 1;
  long c;
  for (long i = 2; i <= n; ++i) {
    c = a + b;
    a = b;
    b = c;
  }

  return b;
}

long fibonacci_dp(long n) {
  if (n <= 1) {
    return n;
  }

  std::vector<long> dp(n + 1);
  dp[0] = 0;
  dp[1] = 1;

  for (long i = 2; i <= n; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

long fibonacci_memo(long n, std::unordered_map<long, long>& memo) {
  if (memo.find(n) != memo.end()) {
    return memo[n];
  }

  if (n <= 1) {
    // memo[n] = n;
    return n;
  }

  memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo);
  return memo[n];
}

int main(int argc, char* argv[]) {
  long number = 0;
  std::unordered_map<long, long> memo{};

  std::cout << "Enter a number: ";
  std::cin >> number;

  long res_recursive = -1;
  long long duration_recursive = 0;
  {
    auto start = std::chrono::high_resolution_clock::now();
    res_recursive = fibonacci_recursive(number);
    auto end = std::chrono::high_resolution_clock::now();
    duration_recursive = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  long res_iterative = -1;
  long long duration_iterative = 0;
  {
    auto start = std::chrono::high_resolution_clock::now();
    res_iterative = fibonacci_iterative(number);
    auto end = std::chrono::high_resolution_clock::now();
    duration_iterative = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  long res_dp = -1;
  long long duration_dp = 0;
  {
    auto start = std::chrono::high_resolution_clock::now();
    res_dp = fibonacci_dp(number);
    auto end = std::chrono::high_resolution_clock::now();
    duration_dp = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  long res_memo = -1;
  long long duration_memo = 0;
  {
    auto start = std::chrono::high_resolution_clock::now();
    res_memo = fibonacci_memo(number, memo);
    auto end = std::chrono::high_resolution_clock::now();
    duration_memo = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  std::cout << "Fibonacci of " << number << " is:" << std::endl;
  std::cout << "\tfibonacci_recursive(" << number << ") = "
            << res_recursive << " (" << duration_recursive << " µs)"
            << std::endl;
  std::cout << "\tfibonacci_iterative(" << number << ") = "
            << res_iterative << " (" << duration_iterative << " µs)"
            << std::endl;
  std::cout << "\tfibonacci_dp(" << number << ")        = "
            << res_dp << " (" << duration_dp << " µs)"
            << std::endl;
  std::cout << "\tfibonacci_memo(" << number << ")      = "
            << res_memo << " (" << duration_memo << " µs)"
            << std::endl;

  return 0;
}
