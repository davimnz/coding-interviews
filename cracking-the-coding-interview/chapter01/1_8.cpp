#include <vector>
#include <iostream>

void PrintMatrix(const std::vector<std::vector<int>> &matrix) {
  std::cout << "--- New matrix ---" << std::endl;
  for (const auto row : matrix) {
    for (const auto element : row) {
      std::cout << element << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << "------------------" << std::endl;
}

/*
  O(m + n) memory complexity. Optimal solution has O(1).
  O(m*n) time complexity.
*/
void ZeroMatrix(std::vector<std::vector<int>> &matrix) {
  std::vector<bool> row(matrix.size(), false);
  std::vector<bool> column(matrix[0].size(), false);
  for (unsigned int i = 0; i != matrix.size(); ++i) {
    for (unsigned int j = 0; j != matrix[i].size(); ++j) {
      if (matrix[i][j] == 0) {
        row[i] = true;
        column[j] = true;
      }
    }
  }
  for (unsigned int i = 0; i != matrix.size(); ++i) {
    if (row[i] == true) {
      for (unsigned int j = 0; j != matrix[i].size(); ++j) {
        matrix[i][j] = 0;  
      }
    }
  }
  for (unsigned int j = 0; j != matrix[0].size(); ++j) {
    if (column[j] == true) {
      for (unsigned int i = 0; i != matrix.size(); ++i) {
        matrix[i][j] = 0;  
      }
    }    
  }
}

int main() {
  std::vector<std::vector<int>> matrix_1{{1, 2, 3, 0},
                                        {4, 5, 6, 7},
                                        {8, 0, 9, 10}},
                                matrix_2{{1, 1, 0},
                                         {1, 1, 1},
                                         {1, 1, 1}},
                                matrix_3{{1, 1, 1, 1, 1},
                                         {1, 1, 0, 1, 0},
                                         {1, 0, 1, 1, 1}},
                                matrix_4{{9, 0, 4},
                                         {3, 5, 3},
                                         {3, 0, 3}},
                                matrix_5{{}};
  ZeroMatrix(matrix_1);
  ZeroMatrix(matrix_2);
  ZeroMatrix(matrix_3);
  ZeroMatrix(matrix_4);
  ZeroMatrix(matrix_5);
  PrintMatrix(matrix_1); // ok
  PrintMatrix(matrix_2); // ok
  PrintMatrix(matrix_3); // ok
  PrintMatrix(matrix_4); // ok
  PrintMatrix(matrix_5); // ok                               
  return 0;
}