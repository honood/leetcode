// HoNooD <honood@gmail.com>
// 2024.06.12 18:04

// 155. Min Stack
// https://leetcode.com/problems/min-stack/description/?envType=study-plan-v2&envId=top-interview-150

// Note: You must implement a solution with O(1) time complexity for each
// function.

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

class MinStack {
public:
  MinStack() {
    minStack_.emplace(numeric_limits<int>::max());
  }

  void push(int val) {
    stack_.emplace(val);

    if (val <= minStack_.top()) {
      minStack_.emplace(val);
    }
  }

  void pop() {
    if (minStack_.top() == stack_.top()) {
      minStack_.pop();
    }

    stack_.pop();
  }

  int top() {
    return stack_.top();
  }

  int getMin() {
    return minStack_.top();
  }

private:
  stack<int> stack_{};
  stack<int> minStack_{};
};

// Better space complexity
class MinStack_2 {
public:
 MinStack() {}

 void push(int val) {
   if (stack_.empty() || val <= stack_.top().second) {
     stack_.emplace(val, val);
     return;
   }

   stack_.emplace(val, stack_.top().second);
 }

 void pop() {
   stack_.pop();
 }

 int top() {
   return stack_.top().first;
 }

 int getMin() {
   return stack_.top().second;
 }

private:
  stack<pair<int, int>> stack_{};
};
