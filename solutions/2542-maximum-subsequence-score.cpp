// HoNooD <honood@gmail.com>
// 2025.03.21 17:00

// 2542. Maximum Subsequence Score
// https://leetcode.com/problems/maximum-subsequence-score/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
    return max_score_v2(nums1, nums2, k);
  }

private:
  // Time Limit Exceeded
  // - Time complexity: O(C(n,k) * k)
  // - Space complexity: O(C(n,k) + k)
  long long max_score_v1(vector<int> const& nums1, vector<int> const& nums2,
                         int k) {
    assert(nums1.size() == nums2.size());
    assert(k >= 1 && k <= nums1.size());

    priority_queue<long long> max_heap{};
    std::function<void(int, int, long long, int)> backtrack
        = [&backtrack, &nums1, &nums2, &max_heap](
              int index, int k, long long nums1_sum, int nums2_min) {
            if (k == 0) {
              max_heap.push(nums1_sum * static_cast<long long>(nums2_min));
              return;
            }

            if (index + k > nums1.size()) {
              return;
            }

            for (int i = index; i < nums1.size(); ++i) {
              backtrack(i + 1, k - 1, nums1_sum + nums1[i],
                        std::min(nums2_min, nums2[i]));
            }
          };

    backtrack(0, k, 0, std::numeric_limits<int>::max());

    return max_heap.top();
  }

  // - Time complexity: O(n * log(n))
  // - Space complexity: O(n)
  long long max_score_v2(vector<int> const& nums1, vector<int> const& nums2,
                         int k) {
    int n = nums1.size();
    assert(nums2.size() == n);
    assert(k >= 1 && k <= n);

    vector<pair<int, int>> pairs{};
    pairs.reserve(n);
    for (int i = 0; i < n; ++i) {
      pairs.emplace_back(nums2[i], nums1[i]);
    }
    // Sort pairs in descending order based on nums2 values
    // O(n * log(n))
    // Note: Using reverse iterators is slower than custom comparator
    // std::sort(pairs.rbegin(), pairs.rend());
    std::sort(pairs.begin(), pairs.end(), [](auto const& lhs, auto const& rhs) {
      return lhs.first > rhs.first;
    });

    // Min-heap to keep track of the k selected elements from nums1, allowing us
    // to efficiently remove the smallest one
    priority_queue<int, vector<int>, std::greater<>> min_heap{};
    long long sum = 0;
    for (int i = 0; i < k; ++i) {
      sum += pairs[i].second;
      min_heap.push(pairs[i].second); // O(log(k))
    }

    long long max_score = sum * pairs[k - 1].first;
    // Try all possible minimun values from nums2
    for (int i = k; i < n; ++i) {
      // Current minimum value from nums2
      int curr_min = pairs[i].first;
      int curr_val = pairs[i].second;

      // Note: This if-check is an optimization, not necessary for correctness.
      //
      // When curr_val <= min_heap.top(), replacing would only decrease sum, and
      // since curr_min is also not increasing, the score would not improve.
      if (curr_val > min_heap.top()) {
        // Remove smallest element from sum and heap
        sum -= min_heap.top();
        min_heap.pop(); // O(log(k))

        sum += curr_val;
        min_heap.push(curr_val); // O(log(k))

        max_score = std::max(max_score, sum * curr_min);
      }
    }
    return max_score;
  }
};
