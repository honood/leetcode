// HoNooD <honood@gmail.com>
// 2024.06.20 14:17

// 42. Trapping Rain Water
// https://leetcode.com/problems/trapping-rain-water/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Best
class Solution {
public:
  int trap(vector<int>& height) {
    int n = height.size();
    if (n <= 2) {
      return 0;
    }

    int left = 0;
    int right = n - 1;
    int leftMax = std::numeric_limits<int>::min();
    int rightMax = std::numeric_limits<int>::min();
    int waterTrapped = 0;
    while (left < right) {
      if (height[left] < height[right]) {
        leftMax = std::max(leftMax, height[left]);
        waterTrapped += leftMax - height[left];
        ++left;
      } else {
        rightMax = std::max(rightMax, height[right]);
        waterTrapped += rightMax - height[right];
        --right;
      }
    }

    return waterTrapped;
  }
};

// Not recommended
// Complex and less intuitive than `Solution`
class Solution_2 {
public:
  int trap(std::vector<int>& height) {
    int n = height.size();
    if (n <= 2) {
      return 0;
    }

    int waterTrapped = 0;
    int leftMax = std::numeric_limits<int>::min();
    int rightMax = std::numeric_limits<int>::min();

    for (int i = 0; i < n; ++i) {
      if (height[i] > leftMax) {
        leftMax = height[i];
      } else {
        waterTrapped += leftMax - height[i];
      }
    }

    for (int i = n - 1; height[i] != leftMax; --i) {
      waterTrapped -= leftMax - height[i];

      if (height[i] > rightMax) {
        rightMax = height[i];
      } else {
        waterTrapped += rightMax - height[i];
      }
    }

    return waterTrapped;
  }
};

// Brute Force: Easy to implement and understand but very slow for large inputs.
//
// Do not use, will TLE (Time Limit Exceeded).
class Solution_3 {
public:
  int trap(std::vector<int>& height) {
    int n = height.size();
    if (n <= 2) {
      return 0;
    }

    int waterTrapped = 0;
    for (int i = 1; i < n - 1; ++i) {
      int leftMax = std::numeric_limits<int>::min();
      for (int j = 0; j <= i; ++j) {
        leftMax = std::max(leftMax, height[j]);
      }

      int rightMax = std::numeric_limits<int>::min();
      for (int j = i; j < n; ++j) {
        rightMax = std::max(rightMax, height[j]);
      }

      waterTrapped += std::min(leftMax, rightMax) - height[i];
    }

    return waterTrapped;
  }
};

// Dynamic Programming (DP): Efficient with a good balance of time and space but
// requires extra space, suitable for medium-sized datasets.
class Solution_4 {
public:
  int trap(std::vector<int>& height) {
    int n = height.size();
    if (n <= 2) {
      return 0;
    }

    std::vector<int> leftMax(n);
    leftMax[0] = height[0];
    for (int i = 1; i < n; ++i) {
      leftMax[i] = std::max(leftMax[i - 1], height[i]);
    }

    std::vector<int> rightMax(n);
    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      rightMax[i] = std::max(height[i], rightMax[i + 1]);
    }

    int waterTrapped = 0;
    for (int i = 1; i < n - 1; ++i) {
      waterTrapped += std::min(leftMax[i], rightMax[i]) - height[i];
    }

    return waterTrapped;
  }
};

// This solution uses a stack-based approach to calculate the trapped water.
// Although the logic behind the stack method is complex and not immediately
// intuitive, it effectively addresses the problem by identifying boundaries and
// calculating the volume of trapped water between them. Here's a breakdown of
// how the stack method works:
//
// 1. Maintain a Monotonic Decreasing Stack: We store indices of the height
//    array in a stack such that the heights are in non-increasing order.
//
// 2. Handle Taller Bars: When we encounter a bar taller than the height at the
//    top of the stack, we may have found a right boundary for trapping water.
//    We then pop elements from the stack and compute the trapped water between
//    the current bar and the new top of the stack (left boundary).
//
// 3. Calculate Trapped Water: For each element popped from the stack, calculate
//    the water trapped between it and the current bar. The effective height of
//    trapped water (`boundedHeight`) is determined by the minimum of the current
//    bar and the new stack top's height, minus the height of the popped element.
//
// The `boundedHeight` ensures we only consider the vertical space that can
// actually hold water, making the method efficient and accurate.
//
// While the stack method's logic may seem intricate, its ability to manage
// varying bar heights and efficiently compute trapped water makes it a powerful
// solution for this problem.
class Solution_5 {
public:
  int trap(std::vector<int>& height) {
    int n = height.size();
    if (n <= 2) {
      return 0;
    }

    stack<int> stack{};
    int waterTrapped = 0;
    for (int i = 0; i < n; ++i) {
      while (!stack.empty() && height[i] > height[stack.top()]) {
        int top = stack.top();
        stack.pop();
        if (stack.empty()) {
          break;
        }

        int distance = i - stack.top() - 1;
        int boundedHeight = std::min(height[i], height[stack.top()]) - height[top];
        waterTrapped += distance * boundedHeight;
      }

      stack.emplace(i);
    }

    return waterTrapped;
  }
};
