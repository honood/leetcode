// HoNooD <honood@gmail.com>
// 2025.02.27 14:25

// 1732. Find the Highest Altitude
// https://leetcode.com/problems/find-the-highest-altitude/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int largestAltitude(vector<int>& gain) {
    return largest_altitude_v1(gain);
  }

private:
  int largest_altitude_v1(vector<int> const& gain) {
    int max_altitude = 0;
    for (int curr_altitude = 0; int g : gain) {
      max_altitude = std::max(max_altitude, curr_altitude += g);
    }
    return max_altitude;
  }

  int largest_altitude_v2(vector<int> const& gain) {
    vector<int> altitudes(gain.size() + 1, 0);
    std::inclusive_scan(gain.cbegin(), gain.cend(), std::next(altitudes.begin()));
    return *std::max_element(altitudes.cbegin(), altitudes.cend());
  }
};
