// HoNooD <honood@gmail.com>
// 2024.07.02 18:06

// 502. IPO
// https://leetcode.com/problems/ipo/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();
    assert(n == capital.size());

    vector<pair<int, int>> projects{};
    projects.reserve(n);
    for (int i = 0; i < n; ++i) {
      projects.emplace_back(profits[i], capital[i]);
    }

    // Note: sorting projects by capital is crucial to avoid Time Limit Exceeded
    // (TLE) errors by optimizing project selection.
    std::sort(projects.begin(), projects.end(), [](pair<int, int> const& left, pair<int, int> const& right) {
      return std::get<1>(left) < std::get<1>(right);
    });

    priority_queue<int> max_heap{};
    int curr_capital = w;
    int i = 0;
    for (int j = 0; j < k; ++j) {
      // add all projects that can be started with the current capital
      while (i < n && projects[i].second <= curr_capital) {
        max_heap.emplace(projects[i].first);
        ++i;
      }

      if (max_heap.empty()) {
        break;
      }

      // select the most profitable project
      curr_capital += max_heap.top();
      max_heap.pop();
    }

    return curr_capital;
  }
};
