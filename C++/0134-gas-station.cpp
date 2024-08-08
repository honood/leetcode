// HoNooD <honood@gmail.com>
// 2024.06.17 13:35

// 134. Gas Station
// https://leetcode.com/problems/gas-station/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    return can_complete_circuit_v2(gas, cost);
  }

private:
  // Brute Force
  // Note: result in Time Limit Exceeded (TLE)
  //
  // Complexity Analysis:
  // - Time complexity: O(n^2)
  // - Space complexity: O(1)
  int can_complete_circuit_v1(vector<int> const& gas, vector<int> const& cost) {
    int n = gas.size();
    assert(n == cost.size());

    for (int i = 0; i < n; ++i) {
      int tank = 0;
      for (int j = i; j < i + n; ++j) {
        int k = j % n;
        tank += gas[k] - cost[k];
        if (tank < 0) {
          break;
        }
      }

      if (tank >= 0) {
        return i;
      }
    }

    return -1;
  }

  // Greedy algorithm
  // https://leetcode.com/tag/greedy/
  //
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int can_complete_circuit_v2(vector<int> const& gas, vector<int> const& cost) {
    int n = gas.size();
    assert(n == cost.size());

    int total_tank = 0; // total net gasoline
    int curr_tank = 0; // current net gasoline
    int start = 0;

    for (int i = 0; i < n; ++i) {
      int net_gas = gas[i] - cost[i];
      total_tank += net_gas;
      curr_tank += net_gas;

      // If `curr_tank` becomes negative after station `i`, it means that the
      // fuel accumulated from the current starting station `start` to `i` is
      // insufficient to reach station `i + 1`.
      //
      // This implies that no station in the range from `start` to `i` can serve
      // as a valid starting point for completing the circuit.
      //
      // Here's a simple proof:
      // Suppose `a`, `b`, `c`, `d`, `e` represent the net fuel from station
      // `station` to station `i`:
      //   a >= 0
      //   a + b >= 0
      //   a + b + c >= 0
      //   a + b + c + d >= 0
      //   a + b + c + d + e < 0
      // Therefore:
      //   b + c + d + e = (a + b + c + d + e) - a < 0
      //   c + d + e = (a + b + c + d + e) - (a + b) < 0
      //   d + e = (a + b + c + d + e) - (a + b + c) < 0
      //   e = (a + b + c + d + e) - (a + b + c + d) < 0
      // Thus, no station from `start` to `i` can reach `i + 1`.
      //
      // Consequently, shift the starting point to `i + 1` and reset `curr_tank`
      // to zero. This indicates that `i + 1` is the next potential candidate
      // for a valid starting point.
      if (curr_tank < 0) {
        start = i + 1;
        curr_tank = 0;
      }
    }

    return total_tank >= 0 ? start : -1;
  }
};
