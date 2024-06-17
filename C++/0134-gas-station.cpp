// HoNooD <honood@gmail.com>
// 2024.06.17 13:35

// 134. Gas Station
// https://leetcode.com/problems/gas-station/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Greedy_algorithm
// https://en.wikipedia.org/wiki/Glossary_of_mathematical_symbols

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Do not use, will TLE (Time Limit Exceeded)
class Solution {
public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
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
};

class Solution_2 {
public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size();
    assert(n == cost.size());

    int total_tank = 0; // total surplus/deficit
    int curr_tank = 0; // current surplus/deficit
    int start = 0; // start station

    for (int i = 0; i < n; ++i) {
      int remain = gas[i] - cost[i];
      total_tank += remain;
      curr_tank += remain;

      // If `current_tank` becomes negative after station `i`, it indicates that
      // the fuel accumulated from the current starting point `start` to `i` is
      // insufficient to reach station `i + 1`.
      //
      // This implies that no station in the segment from the current `start` to
      // `i` can be a valid starting point. If you can't reach station `i` from
      // the current `start`, then starting from any station between `start` and
      // `i` will also fail to reach beyond `i`, because those stations have
      // even less fuel (as `current_tank` is already negative at `i`).
      //
      // Consequently, you should move the starting point to `i + 1`, the next
      // station after the failure point, and reset `current_tank` to `0`. This
      // is because `i + 1` is the next candidate for a potential starting point
      // where you hope to accumulate enough fuel to complete the circuit.
      if (curr_tank < 0) {
        start = i + 1;
        curr_tank = 0;
      }
    }

    // `total_tank >= 0` provides a global check ensuring there’s enough overall
    // fuel to cover the entire route, even if local segments failed during
    // traversal.
    //
    // By combining the local segment checks (`current_tank`) with the global
    // sufficiency check (`total_tank`), the algorithm effectively determines a
    // feasible start point for the circular journey.
    return total_tank >= 0 ? start : -1;
  }
};
