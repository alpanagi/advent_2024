#include <cstring>
#include <fstream>
#include <iostream>

const int SIZE = 140;
char data[SIZE][SIZE];

int match_count(char *word) {
  return (std::strncmp(word, "XMAS", 4) == 0) +
         (std::strncmp(word, "SAMX", 4) == 0);
}

int search(int x, int y) {
  int acc = 0;

  // horizontal check
  if (x <= SIZE - 4) {
    acc += match_count(&data[y][x]);
  }

  // vertical check
  if (y <= SIZE - 4) {
    char word[4] = {data[y][x], data[y + 1][x], data[y + 2][x], data[y + 3][x]};
    acc += match_count(word);
  }

  // diagonal 1 check
  if (x <= SIZE - 4 && y <= SIZE - 4) {
    char word[4] = {data[y][x], data[y + 1][x + 1], data[y + 2][x + 2],
                    data[y + 3][x + 3]};
    acc += match_count(word);
  }

  // diagonal 2 check
  if (x >= 3 && y <= SIZE - 4) {
    char word[4] = {data[y][x], data[y + 1][x - 1], data[y + 2][x - 2],
                    data[y + 3][x - 3]};
    acc += match_count(word);
  }

  return acc;
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
