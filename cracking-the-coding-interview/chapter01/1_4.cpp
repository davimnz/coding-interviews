#include <string>
#include <algorithm>
#include <array>
#include <cassert>

// Extended ASCII alphabet size
const int CHAR_RANGE = 256;

// O(n) in memory, O(n) in time
bool IsPalindromePermutation(const std::string &string) {
  std::array<int, CHAR_RANGE> hashtable{0};
  for (const auto character : string) {
    if (character != ' ') {
      int index = static_cast<int>(std::tolower(character));
      ++hashtable[index];
    }
  }
  int number_of_odd_values = 0;
  for (const auto value : hashtable) {
    if (value % 2 != 0) {
      ++number_of_odd_values;  
    }
    if (number_of_odd_values > 1) {
      return false;  
    }
  }
  return true;
}

int main() {
  std::array<std::string, 9> tests{"Tact coa",
                                   "Arraa",
                                   "bar rab",
                                   "",
                                   "aa",
                                   "b",
                                   "cd f e",
                                   "bar",
                                   "    "};
  std::array<bool, 9> answers{true, true, true, true, true, true, false, false, true};
  int current_index = 0;
  for (const auto test : tests) {
    assert(IsPalindromePermutation(test) == answers[current_index]);
    ++current_index;
  }
  return 0;
}