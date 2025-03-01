// HoNooD <honood@gmail.com>
// 2025.03.01 10:08

// 735. Asteroid Collision
// https://leetcode.com/problems/asteroid-collision/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // Constraints:
  //   1. 2 <= asteroids.length <= 10^4
  //   2. -1000 <= asteroids[i] <= 1000
  //   3. asteroids[i] != 0
  vector<int> asteroidCollision(vector<int>& asteroids) {
    return asteroid_collision_v3(asteroids);
  }

private:
  vector<int> asteroid_collision_v1(vector<int> const& asteroids) {
    std::stack<int> stack{};

    for (int asteroid : asteroids) {
      assert(asteroid != 0);
      bool destroyed = false;

      while (!stack.empty() && stack.top() > 0 && asteroid < 0) {
        if (stack.top() > -asteroid) {
          destroyed = true;
          break;
        }

        if (stack.top() == -asteroid) {
          stack.pop();
          destroyed = true;
          break;
        }

        stack.pop();
      }

      if (!destroyed) {
        stack.push(asteroid);
      }
    }

    vector<int> result(stack.size());
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
      *it = stack.top();
      stack.pop();
    }
    return result;
  }

  // Using `std::vector` as a stack is more efficient thant `std::stack`.
  vector<int> asteroid_collision_v2(vector<int> const& asteroids) {
    vector<int> stack{};

    for (int asteroid : asteroids) {
      assert(asteroid != 0);
      bool destroyed = false;

      while (!stack.empty() && stack.back() > 0 && asteroid < 0) {
        if (stack.back() > -asteroid) {
          destroyed = true;
          break;
        }

        if (stack.back() == -asteroid) {
          stack.pop_back();
          destroyed = true;
          break;
        }

        stack.pop_back();
      }

      if (!destroyed) {
        stack.push_back(asteroid);
      }
    }

    return stack;
  }

  vector<int> asteroid_collision_v3(vector<int> const& asteroids) {
    vector<int> result{};

    for (int asteroid : asteroids) {
      assert(asteroid != 0);
      while (!result.empty() && result.back() > 0 && asteroid < 0) {
        int diff = result.back() + asteroid;
        if (diff > 0) {
          asteroid = 0;
          break;
        }

        if (diff == 0) {
          result.pop_back();
          asteroid = 0;
          break;
        }

        result.pop_back();
      }

      if (asteroid != 0) {
        result.push_back(asteroid);
      }
    }

    return result;
  }
};
