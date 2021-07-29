#include <iostream>
#include <string>

using namespace std;

// Implement strStr()
// Time complexity: O(mn) (brute force)
// Memory complexity: O(1)
class Solution {
 public:
  int strStr(string haystack, string needle) {
    if (needle.empty())
      return 0;
    
    for (size_t i = 0; i < haystack.size(); i++) {
      if (haystack[i] == needle[0]) {
        for (size_t j = i; j < haystack.size(); j++) {
          if (haystack[j] != needle[j - i])
            break;

          if (j == i + needle.size() - 1)
            return i;    
        }   
      }  
    }
    return -1;
  }   
};

int main() {
  class Solution solution;

  string haystack_1("hello");
  string needle_1("ll");

  string haystack_2("");
  string needle_2("arara");

  string haystack_3("araraquara");
  string needle_3("quara");

  std::cout << solution.strStr(haystack_1, needle_1) << std::endl; // ok
  std::cout << solution.strStr(haystack_2, needle_2) << std::endl; // ok
  std::cout << solution.strStr(haystack_3, needle_3) << std::endl; // ok
  return 0; 
}