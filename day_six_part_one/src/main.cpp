#include <fstream>
#include <iostream>

const int MAP_WIDTH = 130;
const int MAP_HEIGHT = 130;
char map[MAP_HEIGHT][MAP_WIDTH];

enum class Direction { Up, Down, Left, Right };
struct GuardTransform {
  int col;
  int row;
  Direction direction;
};

void read_map() {
  std::string line;
  std::ifstream input_file("../input");
  int row = 0;
  while (std::getline(input_file, line)) {
    line.copy(map[row], MAP_WIDTH);
    row++;
  }
}

GuardTransform find_guard_transform() {
  for (int col = 0; col < MAP_HEIGHT; col++) {
    for (int row = 0; row < MAP_WIDTH; row++) {
      switch (map[col][row]) {
      case '^':
        return GuardTransform{col, row, Direction::Up};
      case '<':
        return GuardTransform{col, row, Direction::Left};
      case '>':
        return GuardTransform{col, row, Direction::Right};
      case 'v':
        return GuardTransform{col, row, Direction::Down};
      }
    }
  }

  throw "Guard not found";
}

GuardTransform calculate_next_transform(GuardTransform tran) {
  GuardTransform next_tran = tran;
  switch (tran.direction) {
  case Direction::Up:
    next_tran.col = tran.col - 1;
    next_tran.row = tran.row;
    break;
  case Direction::Down:
    next_tran.col = tran.col + 1;
    next_tran.row = tran.row;
    break;
  case Direction::Left:
    next_tran.col = tran.col;
    next_tran.row = tran.row - 1;
    break;
  case Direction::Right:
    next_tran.col = tran.col;
    next_tran.row = tran.row + 1;
    break;
  }

  return next_tran;
}

bool has_guard_exited(GuardTransform tran) {
  return tran.row < 0 || tran.row == MAP_WIDTH || tran.col < 0 ||
         tran.col == MAP_HEIGHT;
}

GuardTransform move_guard(GuardTransform tran) {
  GuardTransform next_tran = calculate_next_transform(tran);
  if (has_guard_exited(next_tran)) {
    return next_tran;
  }

  while (map[next_tran.col][next_tran.row] == '#') {
    switch (next_tran.direction) {
    case Direction::Up:
      tran.direction = Direction::Right;
      next_tran = calculate_next_transform(tran);
      break;
    case Direction::Down:
      tran.direction = Direction::Left;
      next_tran = calculate_next_transform(tran);
      break;
    case Direction::Left:
      tran.direction = Direction::Up;
      next_tran = calculate_next_transform(tran);
      break;
    case Direction::Right:
      tran.direction = Direction::Down;
      next_tran = calculate_next_transform(tran);
      break;
    }
  }

  return next_tran;
}

int main() {
  read_map();
  auto tran = find_guard_transform();

  while (!has_guard_exited(tran)) {
    map[tran.col][tran.row] = 'X';
    tran = move_guard(tran);
  }

  int count = 0;
  for (int col = 0; col < MAP_HEIGHT; col++) {
    for (int row = 0; row < MAP_HEIGHT; row++) {
      if (map[col][row] == 'X') {
        count++;
      }
    }
  }

  std::cout << count << std::endl;
}
