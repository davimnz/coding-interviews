#include <string>
#include <array>
#include <cassert>

// ASCII alphabet size
const int CHAR_RANGE = 128;

/*
  Fast solution: allocate extra memory to provide O(1) insertion time.
  Note: avoid using stringstream to string concatenation. It provides higher time complexity
        than other techniques. 
*/
std::string CompressString(const std::string &string) {
  if (string.size() == 0) { // Edge case
    return string;
  }
  std::string compressed;
  compressed.reserve(2 * string.size()); // If "string" only has unique characters
  int num_repetition = 0;
  char last_character = string[0];
  for (const auto character : string) {
    if (last_character == character) {
      ++num_repetition;
    }
    else {
      compressed.push_back(last_character);
      for (const auto num_char : std::to_string(num_repetition)) {
        compressed.push_back(num_char);
      }
      num_repetition = 1;
    }
    last_character = character;
  }
  compressed.push_back(last_character);
  for (const auto num_char : std::to_string(num_repetition)) {
    compressed.push_back(num_char);
  }
  if (compressed.size() > string.size()) {
    return string;
  }
  return compressed;
}

int main() {
  std::array<std::string, 8> tests{"aabcccccaaa", 
                                   "Aa", 
                                   "", 
                                   "AAAAAbbbb", 
                                   "ccdde", 
                                   "aaEEaBBBaaa",
                                   "aaaaaaaaaaaaCCCCCCCDDD",
                                   "foobar"};
  std::array<std::string, 8> answers{"a2b1c5a3", 
                                     "Aa" , 
                                     "", 
                                     "A5b4", 
                                     "ccdde", 
                                     "a2E2a1B3a3",
                                     "a12C7D3",
                                     "foobar"};
  int index = 0;
  while (index < 8) {
    assert(CompressString(tests[index]) == answers[index]);
    ++index;
  }
}