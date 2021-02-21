#include <string>
#include <array>
#include <cassert>

/* 
  string_1 must be greater than string_2.
  O(n) time complexity.
*/
bool IsSubstring(const std::string &string_1, const std::string &string_2) {
  unsigned int it = 0;
  bool is_substring = false;
  for (const auto character : string_1) {
    if (it == string_2.size()) {
      is_substring = true;  
      break;        
    }
    if (character == string_2[it]) {
      ++it;    
    }
    else {
      it = 0;
      if (character == string_2[it]) {
        ++it;    
      }
    }
  }
  return is_substring;
}

/* 
  string_1 : string without rotation  
*/
bool IsRotation(const std::string &string_1, const std::string &string_2) {
  std::string string_3{string_2 + string_2};
  return IsSubstring(string_3, string_1);        
}

int main() {
  std::string string_1{"bbcccdada"}; 
  std::string string_2{"cda"};
  assert(IsSubstring(string_1, string_2) == true); // ok
  std::array<std::string, 8> test{"waterbottle",
                                   "erbottlewat",
                                   "dinossaur",
                                   "ssaurdino",
                                   "cat",
                                   "tac",
                                   "barkbark",
                                   "arkbarkb"};
  std::array<bool, 4> answer{true, true, false, true};
  int index = 0;
  while (index < 8) {
    assert(IsRotation(test[index], test[index + 1]) == answer[index / 2]);
    index = index + 2;      
  }
}