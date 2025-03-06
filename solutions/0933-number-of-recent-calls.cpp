// HoNooD <honood@gmail.com>
// 2025.03.02 15:00

// 933. Number of Recent Calls
// https://leetcode.com/problems/number-of-recent-calls/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// Constraints:
//   - Each test case will call `ping` with strictly increasing values of `t`.
class RecentCounter {
public:
  RecentCounter() {}

  int ping(int t) {
    int window_start_t = t - 3000;
    while (!requests_.empty() && requests_.front() < window_start_t) {
      requests_.pop();
    }

    requests_.push(t);

    return requests_.size();
  }

private:
  std::queue<int> requests_{};
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
