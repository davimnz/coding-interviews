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
  Assuming a NxN matrix as input.
  In place solution with O(n) memory complexity (used by auxiliary vector) and
  O(n*n) time complexity.
  This problem could be solved using O(1) memory complexity.
*/
void RotateMatrix(std::vector<std::vector<int>> &matrix) {
  int lower_bound = 0;
  int upper_bound = matrix.size() - 1;
  while (upper_bound > lower_bound) {
    std::vector<int> first_row;
    for (int index = lower_bound; index <= upper_bound; ++index) {
      first_row.push_back(matrix[lower_bound][index]);            
    }
    int j = upper_bound;
    int i = lower_bound;
    // Change first row to first column
    while (j >= lower_bound && i <= upper_bound) {
      matrix[lower_bound][j] = matrix[i][lower_bound];
      --j;
      ++i;
    }
    j = lower_bound;
    i = lower_bound;
    // Change first column to last row
    while (i <= upper_bound) {
      matrix[i][lower_bound] = matrix[upper_bound][i];
      ++i;
    }
    i = upper_bound;
    // Change last row to last column
    while (j <= upper_bound && i >= lower_bound) {
      matrix[upper_bound][j] = matrix[i][upper_bound];
      ++j;
      --i;
    }
    i = lower_bound;
    // Assign last column to first row
    for (const auto element : first_row) {
      matrix[i][upper_bound] = element;
      ++i;
    }
    ++lower_bound;
    --upper_bound;
  }
}

int main() {
  std::vector<std::vector<int>> matrix_1{{1}};
  std::vector<std::vector<int>> matrix_2{{1, 2}, 
                                         {3, 4}};
  std::vector<std::vector<int>> matrix_3{{1, 2, 3}, 
                                         {4, 5, 6},
                                         {7, 8, 9}};
  std::vector<std::vector<int>> matrix_4{{1, 2, 3, 4}, 
                                         {5, 6, 7, 8}, 
                                         {9, 10, 11, 12},
                                         {13, 14, 15, 16}};
  std::vector<std::vector<int>> matrix_5{{1, 2, 3, 4, 5},
                                         {6, 7, 8, 9, 10},
                                         {11, 12, 13, 14, 15},
                                         {16, 17, 18, 19, 20},
                                         {21, 22, 23, 24, 25}};
  std::vector<std::vector<int>> matrix_6{{1, 2, 3, 4, 5, 6},
                                         {7, 8, 9, 10, 11, 12},
                                         {13, 14, 15, 16, 17, 18},
                                         {19, 20, 21, 22, 23, 24},
                                         {25, 26, 27, 28, 29, 30},
                                         {31, 32, 33, 34, 35, 36}};                                       
  RotateMatrix(matrix_1);
  RotateMatrix(matrix_2);
  RotateMatrix(matrix_3);
  RotateMatrix(matrix_4);
  RotateMatrix(matrix_5);
  RotateMatrix(matrix_6);
  PrintMatrix(matrix_1); // ok
  PrintMatrix(matrix_2); // ok
  PrintMatrix(matrix_3); // ok
  PrintMatrix(matrix_4); // ok
  PrintMatrix(matrix_5); // ok
  PrintMatrix(matrix_6); // ok
  return 0;
}