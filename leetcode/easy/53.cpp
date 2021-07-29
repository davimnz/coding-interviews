#include <iostream>
#include <vector>

using namespace std;

// Maximum Subarray - DP solution
// Time complexity: O(n)
// Memory complexity: O(n)
class Solution {
 public:
  int maxSubArray(vector<int> &nums) {
    vector<int> sums(nums.size(), 0);
    sums[nums.size() - 1] = nums[nums.size() - 1];
    
    int max_sum = sums[nums.size() - 1];
    for (size_t i = nums.size() - 1; i > 0; i--) {
      sums[i - 1] = max(nums[i - 1], nums[i - 1] + sums[i]);
      
      if (sums[i - 1] > max_sum)
        max_sum = sums[i - 1];
    }
    return max_sum;
  }
};

int main() {
  class Solution solution;

  vector<int> nums_1({-2, 1, -3, 4, -1, 2, 1, -5, 4});
  vector<int> nums_2({5, 4, -1, 7, 8});

  std::cout << solution.maxSubArray(nums_1) << std::endl; // ok
  std::cout << solution.maxSubArray(nums_2) << std::endl; // ok
  return 0;
}