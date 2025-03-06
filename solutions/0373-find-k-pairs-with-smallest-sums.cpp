// HoNooD <honood@gmail.com>
// 2024.07.02 10:44

// 373. Find K Pairs with Smallest Sums
// https://leetcode.com/problems/find-k-pairs-with-smallest-sums/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    if (nums1.empty() || nums2.empty() || nums1.size() * nums2.size() < k) {
      return {};
    }

    struct greater {
      bool operator()(std::tuple<int, int, int> const& left, std::tuple<int, int, int> const& right) {
        return std::get<0>(left) > std::get<0>(right);
      }
    };
    priority_queue<std::tuple<int, int, int>, vector<std::tuple<int, int, int>>, greater> min_heap{};

    for (int j = 0; j < nums2.size() && j < k; ++j) {
      min_heap.emplace(nums1[0] + nums2[j], 0, j);
    }

    vector<vector<int>> res{};
    while (!min_heap.empty() && res.size() < k) {
      auto [_, i, j] = min_heap.top();
      min_heap.pop();

      res.push_back({nums1[i], nums2[j]});

      if (i + 1 < nums1.size()) {
        min_heap.emplace(nums1[i + 1] + nums2[j], i + 1, j);
      }
    }

    return res;
  }
};

// do not use, will tle (Time Limit Exceeded).
class Solution_2 {
public:
  vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    if (nums1.empty() || nums2.empty() || nums1.size() * nums2.size() < k) {
      return {};
    }

    auto less = [](pair<int, int> const& left, pair<int, int> const& right) {
      return left.first + left.second < right.first + right.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(less)> max_heap{less};
    for (int i = 0; i < nums1.size(); ++i) {
      for (int j = 0; j < nums2.size(); ++j) {
        max_heap.emplace(nums1[i], nums2[j]);
        if (max_heap.size() > k) {
          max_heap.pop();
        }
      }
    }

    vector<vector<int>> res{};
    while (!max_heap.empty()) {
      auto [first, second] = max_heap.top();
      max_heap.pop();

      res.emplace_back(vector<int>{first, second});
    }

    return res;
  }
};
