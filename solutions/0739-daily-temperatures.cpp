// HoNooD <honood@gmail.com>
// 2024.07.13 23:41
// 2025.04.22 10:00

// 739. Daily Temperatures
// https://leetcode.com/problems/daily-temperatures/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    return daily_temperatures_v2(temperatures);
  }

private:
  // Time Limit Exceeded!
  //
  // - Time complexity: O(n^2)
  // - Space complexity: O(n)
  vector<int> daily_temperatures_v1(vector<int> const& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (temperatures[j] > temperatures[i]) {
          result[i] = j - i;
          break;
        }
      }
    }
    return result;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  vector<int> daily_temperatures_v2(vector<int> const& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    std::stack<int> stack{};

    for (int i = n - 1; i >= 0; --i) {
      while (!stack.empty() && temperatures[i] >= temperatures[stack.top()]) {
        stack.pop();
      }

      if (!stack.empty()) {
        result[i] = stack.top() - i;
      }

      stack.push(i);
    }

    return result;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  vector<int> daily_temperatures_v3(vector<int> const& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    std::stack<int> stack{};

    for (int i = 0; i < n; ++i) {
      while (!stack.empty() && temperatures[i] > temperatures[stack.top()]) {
        result[stack.top()] = i - stack.top();
        stack.pop();
      }

      stack.push(i);
    }

    return result;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  vector<int> daily_temperatures_v4(vector<int> const& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);

    for (int i = n - 2; i >= 0; --i) {
      int j = i + 1;
      while (j < n && temperatures[i] >= temperatures[j]) {
        if (result[j] == 0) {
          j = n; // No warmer day
        } else {
          j += result[j]; // Jump to next warmer day
        }
      }

      if (j < n) {
        result[i] = j - i;
      }
    }

    return result;
  }
};
