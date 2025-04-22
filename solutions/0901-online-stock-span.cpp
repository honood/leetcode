// HoNooD <honood@gmail.com>
// 2025.04.21 20:30
//
// 901. Online Stock Span
// https://leetcode.com/problems/online-stock-span/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

namespace stock_spanner::v1 {
class StockSpanner;
}

namespace stock_spanner::v2 {
class StockSpanner;
}

namespace stock_spanner::v3 {
class StockSpanner;
}

using namespace stock_spanner::v2;

namespace stock_spanner::v1 {
class StockSpanner {
private:
  vector<int> prices_;

public:
  StockSpanner() {}

  // - Time complexity: O(n) per call, O(n^2) total for n calls
  // - Space complexity: O(n)
  int next(int price) {
    prices_.push_back(price);

    int span = 1;
    int i = prices_.size() - 2;
    while (i >= 0 && prices_[i] <= price) {
      ++span;
      --i;
    }
    return span;
  }
};
} // namespace stock_spanner::v1

namespace stock_spanner::v2 {
class StockSpanner {
private:
  // Pair: {price, span}
  std::stack<std::pair<int, int>> stack_;

public:
  StockSpanner() {}

  // - Time complexity: overall O(n), amortized O(1)
  // - Space complexity: O(n)
  int next(int price) {
    // The span for the current day is at least 1 (itself)
    int curr_span = 1;

    while (!stack_.empty() && stack_.top().first <= price) {
      curr_span += stack_.top().second;
      stack_.pop();
    }

    stack_.emplace(price, curr_span);

    return curr_span;
  }
};
} // namespace stock_spanner::v2

namespace stock_spanner::v3 {
class StockSpanner {
private:
  // Pair: {price, index}
  std::stack<std::pair<int, int>> stack_;
  // Tracks the current day number (0-based index)
  int curr_day_index_;

public:
  StockSpanner() : curr_day_index_{0} {}

  // - Time complexity: overall O(n), amortized O(1)
  // - Space complexity: O(n)
  int next(int price) {
    while (!stack_.empty() && stack_.top().first <= price) {
      stack_.pop();
    }

    int span;
    if (stack_.empty()) {
      // If stack_ is empty, no previous day had a strictly greater price
      // The span covers all days from the beginning up to the current day.
      span = curr_day_index_ - (-1);
    } else {
      span = curr_day_index_ - stack_.top().second;
    }

    stack_.emplace(price, curr_day_index_);
    ++curr_day_index_;

    return span;
  }
};
} // namespace stock_spanner::v3

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
