#ifndef _CODE_H_
#define _CODE_H_

#include <istream>
#include <queue>
#include <set>
#include <vector>

struct Vector {
  int row;
  int col;
};

struct Map {
  Vector start;
  Vector end;
  char **data;
};

enum class Direction { North, South, West, East };

struct Point {
  Vector position;
  Direction direction;
  long score;

  bool operator<(const Point &) const;
};

struct State {
  Map map;
  std::priority_queue<Point> queue;
  std::set<std::string> visited;
};

Map read_map(std::istream &);
std::vector<Point> calculate_candidates(const Map &, const Point &);
State initialize_state(const Map);
std::optional<Point> step(State &);
std::string hash(Point &);
long find_path(State &);

#endif
