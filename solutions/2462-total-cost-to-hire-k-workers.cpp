// HoNooD <honood@gmail.com>
// 2025.03.23 10:00

// 2462. Total Cost to Hire K Workers
// https://leetcode.com/problems/total-cost-to-hire-k-workers/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  long long totalCost(vector<int>& costs, int k, int candidates) {
    return total_cost_v3(costs, k, candidates);
  }

private:
  // - Time complexity: O((k + candidates) * log(candidates))
  // - Space complexity: O(candidates)
  //
  // Stirling's approximation（斯特林公式）
  // - https://en.wikipedia.org/wiki/Stirling%27s_approximation
  // - https://zh.wikipedia.org/wiki/%E5%8F%B2%E7%89%B9%E9%9D%88%E5%85%AC%E5%BC%8F
  long long total_cost_v1(vector<int> const& costs, int k, int candidates) {
    int n = costs.size();
    assert(n > 0);
    assert(k > 0 && k <= n);
    assert(candidates > 0 && candidates <= n);

    using item_t = pair<int, int>; // {cost, index}
    auto comp = [](item_t const& lhs, item_t const& rhs) {
      return lhs.first > rhs.first
             || (lhs.first == rhs.first && lhs.second > rhs.second);
    };
    using min_heap_t = priority_queue<item_t, vector<item_t>, decltype(comp)>;

    min_heap_t left_candidates{comp};
    min_heap_t right_candidates{comp};

    // Alternative implementation using std::greater<>
    /*
    using min_heap_t = priority_queue<item_t, vector<item_t>, std::greater<>>;

    min_heap_t left_candidates{};
    min_heap_t right_candidates{};
    */

    // Initialize pointers for the next candidates to consider
    int left = 0, right = n - 1;

    for (; left < candidates && left <= right; ++left) {
      left_candidates.emplace(costs[left], left);
    }
    for (; right >= n - candidates && right >= left; --right) {
      right_candidates.emplace(costs[right], right);
    }

    long long total_cost = 0;

    for (int hired = 0; hired < k; ++hired) {
      if (left_candidates.empty()) {
        auto [cost, index] = right_candidates.top();
        right_candidates.pop();
        total_cost += cost;
        continue;
      }

      if (right_candidates.empty()) {
        auto [cost, index] = left_candidates.top();
        left_candidates.pop();
        total_cost += cost;
        continue;
      }

      auto [left_cost, left_index] = left_candidates.top();
      auto [right_cost, right_index] = right_candidates.top();

      if (left_cost < right_cost
          || (left_cost == right_cost && left_index < right_index)) {
        left_candidates.pop();
        total_cost += left_cost;

        // Add next worker from left side if available
        if (left <= right) {
          left_candidates.emplace(costs[left], left);
          ++left;
        }
      } else {
        right_candidates.pop();
        total_cost += right_cost;

        // Add next worker from right side if available
        if (left <= right) {
          right_candidates.emplace(costs[right], right);
          --right;
        }
      }
    } // for

    return total_cost;
  }

  // - Time complexity: O((k + candidates) * log(candidates))
  // - Space complexity: O(candidates)
  long long total_cost_v2(vector<int> const& costs, int k, int candidates) {
    int n = costs.size();
    assert(n > 0);
    assert(k > 0 && k <= n);
    assert(candidates > 0 && candidates <= n);

    enum class section_t { left = 0, right = 1 };
    using item_t = pair<int, section_t>;
    auto comp = [](item_t const& lhs, item_t const& rhs) {
      if (lhs.first != rhs.first) {
        return lhs.first > rhs.first;
      }
      return lhs.second > rhs.second;
    };
    priority_queue<item_t, vector<item_t>, decltype(comp)> min_heap{comp};

    int left = 0, right = n - 1;
    for (int i = 0; i < candidates && left <= right; ++i, ++left) {
      min_heap.emplace(costs[left], section_t::left);
    }
    for (int i = 0; i < candidates && left <= right; ++i, --right) {
      min_heap.emplace(costs[right], section_t::right);
    }

    long long total_cost = 0;

    for (int hired = 0; hired < k; ++hired) {
      auto [cost, section] = min_heap.top();
      min_heap.pop();
      total_cost += cost;

      if (left <= right) {
        if (section == section_t::left) {
          min_heap.emplace(costs[left], section_t::left);
          ++left;
        } else {
          min_heap.emplace(costs[right], section_t::right);
          --right;
        }
      }
    }

    return total_cost;
  }

  // - Time complexity: O((k + candidates) * log(candidates))
  // - Space complexity: O(candidates)
  long long total_cost_v3(vector<int> const& costs, int k, int candidates) {
    int n = costs.size();
    assert(n > 0);
    assert(k > 0 && k <= n);
    assert(candidates > 0 && candidates <= n);

    multiset<pair<int, int>> ms{};

    int left = 0, right = n - 1;
    for (int i = 0; i < candidates && left <= right; ++i, ++left) {
      ms.emplace(costs[left], left);
    }
    for (int i = 0; i < candidates && left <= right; ++i, --right) {
      ms.emplace(costs[right], right);
    }

    long long total_cost = 0;

    for (int hired = 0; hired < k; ++hired) {
      auto [cost, index] = *ms.cbegin();
      ms.erase(ms.cbegin());
      total_cost += cost;

      if (left <= right) {
        if (index < right) {
          ms.emplace(costs[left], left);
          ++left;
        } else {
          ms.emplace(costs[right], right);
          --right;
        }
      }
    }

    return total_cost;
  }
};
