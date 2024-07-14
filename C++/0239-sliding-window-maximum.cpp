// HoNooD <honood@gmail.com>
// 2024.07.14 21:39

// 239. Sliding Window Maximum
// https://leetcode.com/problems/sliding-window-maximum/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    return max_sliding_window_v3(nums, k);
  }

private:
  // Brute Force
  //
  // Time complexity: O((n-k)*k)
  //
  // Note: result in Time Limit Exceeded (TLE)
  vector<int> max_sliding_window_v1(vector<int> const& nums, int k) {
    int n = nums.size();
    if (k <= 0 || n < k) {
      return {};
    }

    vector<int> res(n - k + 1);
    for (int i = 0; i <= n - k; ++i) {
      res[i] = *std::max_element(std::next(nums.cbegin(), i),
                                 std::next(nums.cbegin(), i + k));
    }

    return res;
  }

  // using priority queue
  // https://leetcode.com/tag/heap-priority-queue/
  //
  // Time complexity:
  //   - worst case: O(n*log(n)), when nums is monotonically increasing.
  //   - average case: O(n*log(k))
  vector<int> max_sliding_window_v2(vector<int> const& nums, int k) {
    int n = nums.size();
    if (k <= 0 || n < k) {
      return {};
    }

    // [NOTE] In this context, a custom comparator for `std::priority_queue` is
    // not strictly necessary. However, it can help reduce unnecessary
    // comparisons.
    //
    // The default `operator<` provided by the C++ STL for `std::pair` would
    // work for this purpose, but it compares the `first` members and, only if
    // they are equivalent, it compares the `second` members (see:
    // https://en.cppreference.com/w/cpp/utility/pair/operator_cmp). In this
    // case, the `first` members are elements from the `nums` array, and they
    // might be equal. However, even if they are, the `second` members do not
    // need to be compared.
    auto less = [](pair<int, int> const& left, pair<int, int> const& right) {
      return left.first < right.first;
    };
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(less)> pq{less};

    vector<int> res{};
    res.reserve(n - k + 1);
    for (int i = 0; i < n; ++i) {
      pq.emplace(nums[i], i);

      // remove the elements which are out of the current window
      while (!pq.empty() && pq.top().second <= i - k) {
        pq.pop();
      }

      if (i >= k - 1) {
        res.emplace_back(pq.top().first);
      }
    }

    return res;
  }

  // using monotonic decreasing queue
  // https://leetcode.com/tag/monotonic-queue/
  //
  // Time complexity: O(n). Since each element is pushed and popped at most
  // once, the total number of operations across all elements is 2n (each push
  // and pop operation is O(1)).
  vector<int> max_sliding_window_v3(vector<int> const& nums, int k) {
    int n = nums.size();
    if (k <= 0 || n < k) {
      return {};
    }

    std::deque<int> dq{};

    vector<int> res(n - k + 1);
    for (int i = 0; i < n; ++i) {
      // remove indices that are out of the current window
      if (!dq.empty() && dq.front() == i - k) {
        dq.pop_front();
      }

      // maintain the monotonic decreasing order in `dq`
      while (!dq.empty() && nums[i] > nums[dq.back()]) {
        dq.pop_back();
      }
      dq.emplace_back(i);

      if (i >= k - 1) {
        res[i - k + 1] = nums[dq.front()];
      }
    }

    return res;
  }
};
