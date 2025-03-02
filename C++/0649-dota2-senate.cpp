// HoNooD <honood@gmail.com>
// 2025.03.02 15:23

// 649. Dota2 Senate
// https://leetcode.com/problems/dota2-senate/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  string predictPartyVictory(string senate) {
    std::queue<int> radiant{};
    std::queue<int> dire{};

    int n = senate.size();
    for (int i = 0; i < n; ++i) {
      if (senate[i] == 'R') {
        radiant.push(i);
      } else {
        dire.push(i);
      }
    }

    while (!radiant.empty() && !dire.empty()) {
      int r = radiant.front();
      radiant.pop();
      int d = dire.front();
      dire.pop();

      if (r < d) {
        radiant.push(r + n);
      } else {
        dire.push(d + n);
      }
    }

    return dire.empty() ? "Radiant" : "Dire";
  }
};
