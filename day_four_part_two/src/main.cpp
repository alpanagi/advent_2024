#include <cstring>
#include <fstream>
#include <iostream>

const int SIZE = 140;
char data[SIZE][SIZE];

bool is_correct_word(char *word) {
  return (std::strncmp(word, "MAS", 3) == 0) ||
         (std::strncmp(word, "SAM", 3) == 0);
}

int search(int x, int y) {
  if (x > SIZE - 3 || y > SIZE - 3) {
    return 0;
  }

  int acc = 0;

  char diagonal_1[3] = {
      data[y][x],
      data[y + 1][x + 1],
      data[y + 2][x + 2],
  };

  char diagonal_2[3] = {
      data[y][x + 2],
      data[y + 1][x + 1],
      data[y + 2][x],
  };

  if (is_correct_word(diagonal_1) && is_correct_word(diagonal_2)) {
    return true;
  }

  return false;
}

int main() {
  std::string line;
  std::ifstream input_file("../input");

  int row = 0;
  while (std::getline(input_file, line)) {
    line.copy(data[row], SIZE);
    row++;
  }

  int acc = 0;
  for (int y = 0; y < SIZE; y++) {
    for (int x = 0; x < SIZE; x++) {
      acc += search(x, y);
    }
  }

  std::cout << acc << std::endl;
}
