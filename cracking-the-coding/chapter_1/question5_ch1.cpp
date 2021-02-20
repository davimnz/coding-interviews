#include <string>
#include <array>
#include <cassert>

// Assuming that the first string is greater than the second
bool CheckInsertion(const std::string &first_string, const std::string &second_string) {
  std::string::size_type first_index = 0;
  std::string::size_type second_index = 0;
  bool found_extra_letter = false;
  while (first_index < first_string.size()) {
    if (first_string[first_index] == second_string[second_index]) {
      ++first_index;
      ++second_index;        
    }
    else {
      if (found_extra_letter) {
        return false;          
      }  
      found_extra_letter = true;  
      ++first_index;
    }
  }
  return true;
}

// Assuming that the strings have the same size
bool CheckReplace(const std::string &first_string, const std::string &second_string) {
  std::string::size_type index = 0;
  std::string::size_type strings_size = first_string.size();
  bool found_replace = false;
  while (index < strings_size) {
    if (first_string[index] == second_string[index]) {
      ++index;
    }
    else {
      if (found_replace) {
        return false;     
      }  
      found_replace = true;
      ++index; 
    }
  }
  return true;
}

bool OneAway(const std::string &first_string, const std::string &second_string) {
  if (first_string.size() - second_string.size() == 0) {
    return CheckReplace(first_string, second_string);    
  }
  else if (first_string.size() - second_string.size() == 1) {
    return CheckInsertion(first_string, second_string); 
  }
  else if (static_cast<int>(first_string.size() - second_string.size()) == -1) {
    return CheckInsertion(second_string, first_string);
  }
  return false;
}

int main() {
  std::array<std::string, 18> tests{"pale", "ple",
                                    "pales", "pale",
                                    "pale", "bale",
                                    "pale", "bake",
                                    "a", "",
                                    "", "",
                                    "aa", "aac",
                                    "", "bd",
                                    "ple", "palk"};
  std::array<bool, 9> answers{true, true, true,
                              false, true, true,
                              true, false, false};
  int index = 0;
  while (index < 18) {
    assert(OneAway(tests[index], tests[index + 1]) == answers[index / 2]);
    index = index + 2;      
  }
  return 0;
}