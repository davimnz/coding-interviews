#include <string>
#include <algorithm>
#include <array>
#include <cassert>

// ASCII alphabet size
const int CHAR_RANGE = 256;

// O(1) in memory, O(n) in time
bool CheckPermutation(const std::string &first_string, const std::string &second_string) {
  // Strings' length must be equal
  if (first_string.size() != second_string.size()) {
    return false;      
  }
  std::array<int, CHAR_RANGE> hashtable {0};
  for (auto character : first_string) {
    int index = static_cast<int>(character);
    ++hashtable[index];
  }
  for (auto character : second_string) {
    int index = static_cast<int>(character);
    --hashtable[index];
  }
  // Hashtable should have only zero values if one string is a permutation of the other
  return std::all_of(hashtable.begin(), hashtable.end(), [](int value){ return value == 0; });
}

int main() {
  std::array<std::string, 20> tests{"abba", "baba",
                                   "", "",
                                   "b", "",
                                   "hello", "ello", 
                                   "", "b",
                                   "cat", "dinossaur",
                                   "bbae", "baeb",
                                   "arara", "aarar",
                                   "d!n0", "0dn!",
                                   "foo", "bar"};
  std::array<bool, 10> answers{true, true, false, false, false, false, true, true, true, false};
  int current_index = 0;
  while (current_index < 20) {
    std::string first_string = tests[current_index];
    std::string second_string = tests[current_index + 1];
    assert(CheckPermutation(first_string, second_string) == answers[current_index / 2]);
    current_index = current_index + 2;
  }
  return 0;
}