#include <string>
#include <array>
#include <cassert>

/* 
  Current solution: O(n) in memory and O(n) in time.
  Optimal solution modifies the string argument instead of using an additional "url" string variable.
  This would give us an O(1) memory complexity.  
*/
std::string Urlify(const std::string &string, std::string::size_type length) {
  std::string url;
  std::string::size_type current_length = 0;
  for (const auto character : string) {
    if (current_length >= length) {
      break;
    }
    if (character == ' ') {
      url.insert(url.end(), '%');
      url.insert(url.end(), '2');
      url.insert(url.end(), '0');  
    }
    else {
      url.insert(url.end(), character);
    }
    ++current_length;
  }
  return url;
}

int main() {
  std::array<std::string, 5> names{"Mr John Smith      ",
                                   "Mr Dinossaur   ",
                                   "Mr John Doe   ",
                                   "    ",
                                   "Generic person name   "};
  std::array<int, 5> lengths {13, 12, 11, 0, 19};
  std::array<std::string, 5> answers{"Mr%20John%20Smith",
                                     "Mr%20Dinossaur", 
                                     "Mr%20John%20Doe",
                                     "",
                                     "Generic%20person%20name"};
  int length_index = 0;
  for (const auto name : names) {
    assert(Urlify(name, lengths[length_index]) == answers[length_index]);
    ++length_index;
  }
  return 0;
}