#include "code.h"
#include <iostream>
#include <istream>
#include <print>
#include <queue>

bool Point::operator<(const Point &rhs) const { return score > rhs.score; }

Map read_map(std::istream &iss) {
  std::pair<int, int> start;
  std::pair<int, int> end;
  std::vector<std::vector<char>> data;

  int row = 0;
  std::string line;
  while (std::getline(iss, line)) {
    data.push_back(std::vector<char>());
    for (int col = 0; col < line.size(); col++) {
      if ('S' == line[col]) {
        start.first = row;
        start.second = col;
      }

      if ('E' == line[col]) {
        end.first = row;
        end.second = col;
      }

      data[row].push_back(line[col]);
    }
    row++;
  }

  // Convert to matrix
  int height = data.size();
  int width = data[0].size();
  char **matrix_data = new char *[height];
  for (int row = 0; row < height; row++) {
    matrix_data[row] = new char[width];
    for (int col = 0; col < width; col++) {
      matrix_data[row][col] = data[row][col];
    }
  }

  return {
      .start =
          {
              .row = start.first,
              .col = start.second,
          },
      .end =
          {
              .row = end.first,
              .col = end.second,
          },
      .data = matrix_data,
  };
}

std::vector<Point> calculate_candidates(const Map &map, const Point &point) {
  std::vector<Point> points;

  switch (point.direction) {
  case Direction::North:
    if (map.data[point.position.row - 1][point.position.col] != '#') {
      points.push_back(Point{
          .position = {.row = point.position.row - 1,
                       .col = point.position.col},
          .direction = Direction::North,
          .score = point.score + 1,
      });
    }

    points.push_back(Point{
        .position = {.row = point.position.row, .col = point.position.col},
        .direction = Direction::West,
        .score = point.score + 1000,
    });
    points.push_back(Point{
        .position = {.row = point.position.row, .col = point.position.col},
        .direction = Direction::East,
        .score = point.score + 1000,
    });
    break;
  case Direction::South:
    if (map.data[point.position.row + 1][point.position.col] != '#') {
      points.push_back(Point{
          .position = {.row = point.position.row + 1,
                       .col = point.position.col},
          .direction = Direction::South,
          .score = point.score + 1,
      });
    }

    points.push_back(Point{
        .position = {.row = point.position.row, .col = point.position.col},
        .direction = Direction::East,
        .score = point.score + 1000,
    });
    points.push_back(Point{
        .position = {.row = point.position.row, .col = point.position.col},
        .direction = Direction::West,
        .score = point.score + 1000,
    });
    break;
  case Direction::West:
    if (map.data[point.position.row][point.position.col - 1] != '#') {
      points.push_back(Point{
          .position = {.row = point.position.row,
                       .col = point.position.col - 1},
          .direction = Direction::West,
          .score = point.score + 1,
      });
    }

    points.push_back(Point{
        .position = {.row = point.position.row, .col = point.position.col},
        .direction = Direction::South,
        .score = point.score + 1000,
    });
    points.push_back(Point{
        .position = {.row = point.position.row, .col = point.position.col},
        .direction = Direction::North,
        .score = point.score + 1000,
    });
    break;
  case Direction::East:
    if (map.data[point.position.row][point.position.col + 1] != '#') {
      points.push_back(Point{
          .position = {.row = point.position.row,
                       .col = point.position.col + 1},
          .direction = Direction::East,
          .score = point.score + 1,
      });
    }

    points.push_back(Point{
        .position = {.row = point.position.row, .col = point.position.col},
        .direction = Direction::North,
        .score = point.score + 1000,
    });
    points.push_back(Point{
        .position = {.row = point.position.row, .col = point.position.col},
        .direction = Direction::South,
        .score = point.score + 1000,
    });
    break;
  }

  return points;
}

State initialize_state(const Map map) {
  std::priority_queue<Point> queue;
  queue.push({.position = map.start, .direction = Direction::East, .score = 0});
  return {
      .map = map,
      .queue = queue,
      .visited = std::set<std::string>(),
  };
}

inline std::optional<Point> step(State &state) {
  Point point = state.queue.top();
  state.queue.pop();

  if (point.position.row == state.map.end.row &&
      point.position.col == state.map.end.col) {
    return std::optional<Point>(point);
  }

  std::string point_hash = hash(point);
  if (state.visited.contains(point_hash)) {
    return std::optional<Point>();
  }
  state.visited.insert(point_hash);

  for (auto el : calculate_candidates(state.map, point)) {
    state.queue.push(el);
  }

  return std::optional<Point>();
}

inline std::string hash(Point &point) {
  std::string direction;
  switch (point.direction) {
  case Direction::North:
    direction = "North";
    break;
  case Direction::South:
    direction = "South";
    break;
  case Direction::West:
    direction = "West";
    break;
  case Direction::East:
    direction = "East";
    break;
  }
  return std::format("{},{}/{}", point.position.row, point.position.col,
                     direction);
}

long find_path(State &state) {
  std::optional<Point> result;
  do {
    result = step(state);
  } while (!result.has_value());

  return result.value().score;
}
