#include <string>
#include <sstream>
#include <array>
#include <cassert>

// ASCII alphabet size
const int CHAR_RANGE = 128;

std::string CompressString(const std::string &string) {
  if (string.size() == 0) { // Edge case
    return string;
  }
  int num_repetition = 0;
  std::stringstream string_stream;
  char last_character = string[0];
  for (const auto character : string) {
    if (last_character == character) {
      ++num_repetition;
    }
    else {  
      string_stream << last_character << num_repetition;  
      num_repetition = 1;
    }
    last_character = character;
  }
  string_stream << last_character << num_repetition;
  if (string_stream.str().size() > string.size()) {
    return string;   
  }
  return string_stream.str();
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