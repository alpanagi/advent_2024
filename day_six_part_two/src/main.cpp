#include <fstream>
#include <iostream>

const int SIMULATION_LIMIT = 100000;
const int MAP_WIDTH = 130;
const int MAP_HEIGHT = 130;
char map[MAP_HEIGHT][MAP_WIDTH];

enum class Direction { Up, Down, Left, Right };
struct GuardTransform {
  int row;
  int col;
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
  for (int row = 0; row < MAP_HEIGHT; row++) {
    for (int col = 0; col < MAP_WIDTH; col++) {
      switch (map[row][col]) {
      case '^':
        return GuardTransform{row, col, Direction::Up};
      case '<':
        return GuardTransform{row, col, Direction::Left};
      case '>':
        return GuardTransform{row, col, Direction::Right};
      case 'v':
        return GuardTransform{row, col, Direction::Down};
      }
    }
  }

  throw "Guard not found";
}

GuardTransform calculate_next_transform(GuardTransform tran) {
  GuardTransform next_tran = tran;
  switch (tran.direction) {
  case Direction::Up:
    next_tran.row = tran.row - 1;
    next_tran.col = tran.col;
    break;
  case Direction::Down:
    next_tran.row = tran.row + 1;
    next_tran.col = tran.col;
    break;
  case Direction::Left:
    next_tran.row = tran.row;
    next_tran.col = tran.col - 1;
    break;
  case Direction::Right:
    next_tran.row = tran.row;
    next_tran.col = tran.col + 1;
    break;
  }

  return next_tran;
}

bool has_guard_exited(GuardTransform tran) {
  return tran.row < 0 || tran.row == MAP_HEIGHT || tran.col < 0 ||
         tran.col == MAP_WIDTH;
}

GuardTransform move_guard(GuardTransform tran) {
  GuardTransform next_tran = calculate_next_transform(tran);
  if (has_guard_exited(next_tran)) {
    return next_tran;
  }

  while (map[next_tran.row][next_tran.col] == '#') {
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
  auto start_tran = find_guard_transform();

  int count = 0;
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (map[i][j] == '#') {
        continue;
      }

      map[i][j] = '#';

      int steps = 0;
      auto simulation_tran = start_tran;
      while (steps < SIMULATION_LIMIT) {
        if (has_guard_exited(simulation_tran)) {
          break;
        }

        simulation_tran = move_guard(simulation_tran);
        steps++;
      }

      if (steps == SIMULATION_LIMIT) {
        count++;
      }

      map[i][j] = '.';
    }
  }

  std::cout << count << std::endl;
}
