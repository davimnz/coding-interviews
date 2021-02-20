#include <string>
#include <array>
#include <cassert>

// Extended ASCII alphabet size 
const int CHAR_RANGE = 256;

// O(1) in memory, O(n) in time
bool HasAllUniqueCharacters(const std::string &string) {
  std::array<bool, CHAR_RANGE> char_hash {false};
  for (const auto character : string) {
    int index = static_cast<int>(character);
    if (char_hash[index] == true) {
      return false;
    }
    else {
      char_hash[index] = true;
    }
  }
  return true;
}

int main() {
  std::array<std::string, 8> tests{"abba", "foo", "bar", "", " ", "  ", "cat", "dinossaur"};
  std::array<bool, 8> answers{false, false, true, true, true, false, true, false};
  int current_index = 0;
  for (auto string : tests) {
    assert(HasAllUniqueCharacters(string) == answers[current_index]);
    ++current_index;
  } 
  return 0;    
}