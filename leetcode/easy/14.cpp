#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Longest Common Prefix
// Time complexity: O(s); s : sum of all characters in all strings
// Memory complexity: O(1)
class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    const int max_length = 200;
    
    int index = -1;
    bool running = true;
    for (int i = 0; i < max_length && running; i++) {
      char current_char;
      if (!strs[0].empty() && i < (int) strs[0].size())
        current_char = strs[0][i];
      else
        break;
      
      for (auto str : strs) {
        if (str.empty()) {
          running = false;
          break;
        }
          
        if (current_char != str[i]) {
          running = false;
          break;
        }
      }

      if (running)
        index = i;
    }

    if (index >= 0)
      return strs[0].substr(0, index + 1);
    else
      return "";
  }
};

int main() {
  class Solution solution;

  vector<string> strs_1{"flower", "flow", "flew"};
  vector<string> strs_2{"aa", "aa", ""};
  vector<string> strs_3{"aaab", "aaab"};

  std::cout << solution.longestCommonPrefix(strs_1) << std::endl; // ok
  std::cout << solution.longestCommonPrefix(strs_2) << std::endl; // ok
  std::cout << solution.longestCommonPrefix(strs_3) << std::endl; // ok
  return 0;
}