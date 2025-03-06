// HoNooD <honood@gmail.com>
// 2024.07.03 14:00

// 295. Find Median from Data Stream
// https://leetcode.com/problems/find-median-from-data-stream/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Median

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Example of maintaining heaps:
// - Insert 10:
//   - Add to max_heap: [10]
//   - Move top to min_heap: max_heap: [], min_heap: [10]
//   - Balance back to max_heap: max_heap: [10], min_heap: []
// - Insert 20:
//   - Add to max_heap: [20, 10]
//   - Move top to min_heap: max_heap: [10], min_heap: [20]
// - Insert 30:
//   - Add to max_heap: [30, 10]
//   - Move top to min_heap: max_heap: [10], min_heap: [20, 30]
//   - Balance back: max_heap: [20, 10], min_heap: [30]
// - Insert 40:
//   - Add to max_heap: [40, 10, 20]
//   - Move top to min_heap: max_heap: [20, 10], min_heap: [30, 40]
// - Insert 50:
//   - Add to max_heap: [50, 10, 20]
//   - Move top to min_heap: max_heap: [20, 10], min_heap: [30, 40, 50]
//   - Balance back: max_heap: [30, 10, 20], min_heap: [40, 50]
class MedianFinder {
public:
  MedianFinder() = default;

  void addNum(int num) {
    max_heap_.emplace(num);

    // ensure `max_heap_` has the smaller half and `min_heap_` the larger half
    min_heap_.emplace(max_heap_.top());
    max_heap_.pop();

    // balance the heaps if `min_heap_` has more elements
    if (min_heap_.size() > max_heap_.size()) {
      max_heap_.emplace(min_heap_.top());
      min_heap_.pop();
    }
  }

  double findMedian() {
    if (max_heap_.size() == min_heap_.size()) {
      return (max_heap_.top() + min_heap_.top()) / 2.0;
    }

    return max_heap_.top();
  }

  // also works as expected:
  /*
  void addNum(int num) {
    min_heap_.emplace(num);

    max_heap_.emplace(min_heap_.top());
    min_heap_.pop();

    if (max_heap_.size() > min_heap_.size()) {
      min_heap_.emplace(max_heap_.top());
      max_heap_.pop();
    }
  }

  double findMedian() {
    if (min_heap_.size() == max_heap_.size()) {
      return (min_heap_.top() + max_heap_.top()) / 2.0;
    }

    return min_heap_.top();
  }
  */
private:
  // store the smaller half of the data
  priority_queue<int> max_heap_{};
  // store the larger half of the datag quig
  priority_queue<int, vector<int>, std::greater<int>> min_heap_{};
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
