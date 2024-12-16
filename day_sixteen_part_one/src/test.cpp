#include "code.h"
#include <cassert>
#include <print>
#include <sstream>

const std::string example_map = "###############\n"
                                "#.......#....E#\n"
                                "#.#.###.#.###.#\n"
                                "#.....#.#...#.#\n"
                                "#.###.#####.#.#\n"
                                "#.#.#.......#.#\n"
                                "#.#.#####.###.#\n"
                                "#...........#.#\n"
                                "###.#.#####.#.#\n"
                                "#...#.....#.#.#\n"
                                "#.#.#.###.#.#.#\n"
                                "#.....#...#.#.#\n"
                                "#.###.#.#.#.#.#\n"
                                "#S..#.....#...#\n"
                                "###############";

const std::string example_map_2 = "#################\n"
                                  "#...#...#...#..E#\n"
                                  "#.#.#.#.#.#.#.#.#\n"
                                  "#.#.#.#...#...#.#\n"
                                  "#.#.#.#.###.#.#.#\n"
                                  "#...#.#.#.....#.#\n"
                                  "#.#.#.#.#.#####.#\n"
                                  "#.#...#.#.#.....#\n"
                                  "#.#.#####.#.###.#\n"
                                  "#.#.#.......#...#\n"
                                  "#.#.###.#####.###\n"
                                  "#.#.#...#.....#.#\n"
                                  "#.#.#.#####.###.#\n"
                                  "#.#.#.........#.#\n"
                                  "#.#.#.#########.#\n"
                                  "#S#.............#\n"
                                  "#################";

void should_correctly_read_input() {
  std::print("should_correctly_read_input\n");
  // Given
  std::string input = example_map;
  std::istringstream iss(input);

  // When
  Map map = read_map(iss);

  // Then
  assert(map.start.row == 13);
  assert(map.start.col == 1);
  assert(map.end.row == 1);
  assert(map.end.col == 13);

  for (int row = 0; row < 14; row++) {
    for (int col = 0; col < 14; col++) {
      assert(map.data[row][col] == input[row * 16 + col]);
    }
  }
}

void should_correctly_read_input_2() {
  std::print("should_correctly_read_input_2\n");
  // Given
  std::string input = example_map_2;
  std::istringstream iss(input);

  // When
  Map map = read_map(iss);

  // Then
  assert(map.start.row == 15);
  assert(map.start.col == 1);
  assert(map.end.row == 1);
  assert(map.end.col == 15);

  for (int row = 0; row < 17; row++) {
    for (int col = 0; col < 17; col++) {
      assert(map.data[row][col] == input[row * 18 + col]);
    }
  }
}

void should_return_correct_candidates() {
  std::print("should_return_correct_candidates\n");
  // Given
  Point point{
      .position = {.row = 1, .col = 1},
      .direction = Direction::East,
      .score = 1,
  };

  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  std::vector<Point> points = calculate_candidates(map, point);

  // Then
  assert(points.size() == 3);

  assert(points[0].position.row == 1);
  assert(points[0].position.col == 2);
  assert(points[0].direction == Direction::East);
  assert(points[0].score == 2);

  assert(points[1].position.row == 1);
  assert(points[1].position.col == 1);
  assert(points[1].direction == Direction::North);
  assert(points[1].score == 1001);

  assert(points[2].position.row == 1);
  assert(points[2].position.col == 1);
  assert(points[2].direction == Direction::South);
  assert(points[2].score == 1001);
}

void should_return_correct_candidates_2() {
  std::print("should_return_correct_candidates_2\n");
  // Given
  Point point{
      .position = {.row = 3, .col = 3},
      .direction = Direction::North,
      .score = 1,
  };

  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  std::vector<Point> points = calculate_candidates(map, point);

  // Then
  assert(points.size() == 3);

  assert(points[0].position.row == 2);
  assert(points[0].position.col == 3);
  assert(points[0].direction == Direction::North);
  assert(points[0].score == 2);

  assert(points[1].position.row == 3);
  assert(points[1].position.col == 3);
  assert(points[1].direction == Direction::West);
  assert(points[1].score == 1001);

  assert(points[2].position.row == 3);
  assert(points[2].position.col == 3);
  assert(points[2].direction == Direction::East);
  assert(points[2].score == 1001);
}

void should_return_correct_candidates_3() {
  std::print("should_return_correct_candidates_3\n");
  // Given
  Point point{
      .position = {.row = 4, .col = 8},
      .direction = Direction::South,
      .score = 12,
  };

  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  std::vector<Point> points = calculate_candidates(map, point);

  // Then
  assert(points.size() == 3);

  assert(points[0].position.row == 5);
  assert(points[0].position.col == 8);
  assert(points[0].direction == Direction::South);
  assert(points[0].score == 13);

  assert(points[1].position.row == 4);
  assert(points[1].position.col == 8);
  assert(points[1].direction == Direction::East);
  assert(points[1].score == 1012);

  assert(points[2].position.row == 4);
  assert(points[2].position.col == 8);
  assert(points[2].direction == Direction::West);
  assert(points[2].score == 1012);
}

void should_return_correct_candidates_4() {
  std::print("should_return_correct_candidates_4\n");
  // Given
  Point point{
      .position = {.row = 9, .col = 18},
      .direction = Direction::West,
      .score = 14,
  };

  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  std::vector<Point> points = calculate_candidates(map, point);

  // Then
  assert(points.size() == 3);

  assert(points[0].position.row == 9);
  assert(points[0].position.col == 17);
  assert(points[0].direction == Direction::West);
  assert(points[0].score == 15);

  assert(points[1].position.row == 9);
  assert(points[1].position.col == 18);
  assert(points[1].direction == Direction::South);
  assert(points[1].score == 1014);

  assert(points[2].position.row == 9);
  assert(points[2].position.col == 18);
  assert(points[2].direction == Direction::North);
  assert(points[2].score == 1014);
}

void should_not_return_move_forward_candidate_if_there_is_a_wall_in_front() {
  std::print(
      "should_not_return_move_forward_candidate_if_there_is_a_wall_in_front\n");
  // Given
  Point point{
      .position = {.row = 3, .col = 4},
      .direction = Direction::North,
      .score = 12,
  };

  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  std::vector<Point> points = calculate_candidates(map, point);

  // Then
  assert(points.size() == 2);

  assert(points[0].position.row == 3);
  assert(points[0].position.col == 4);
  assert(points[0].direction == Direction::West);
  assert(points[0].score == 1012);

  assert(points[1].position.row == 3);
  assert(points[1].position.col == 4);
  assert(points[1].direction == Direction::East);
  assert(points[1].score == 1012);
}

void should_not_return_move_forward_candidate_if_there_is_a_wall_in_front_2() {
  std::print("should_not_return_move_forward_candidate_if_there_is_a_wall_in_"
             "front_2\n");
  // Given
  Point point{
      .position = {.row = 5, .col = 5},
      .direction = Direction::South,
      .score = 3,
  };

  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  std::vector<Point> points = calculate_candidates(map, point);

  // Then
  assert(points.size() == 2);

  assert(points[0].position.row == 5);
  assert(points[0].position.col == 5);
  assert(points[0].direction == Direction::East);
  assert(points[0].score == 1003);

  assert(points[1].position.row == 5);
  assert(points[1].position.col == 5);
  assert(points[1].direction == Direction::West);
  assert(points[1].score == 1003);
}

void should_not_return_move_forward_candidate_if_there_is_a_wall_in_front_3() {
  std::print("should_not_return_move_forward_candidate_if_there_is_a_wall_in_"
             "front_3\n");
  // Given
  Point point{
      .position = {.row = 10, .col = 1},
      .direction = Direction::West,
      .score = 9,
  };

  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  std::vector<Point> points = calculate_candidates(map, point);

  // Then
  assert(points.size() == 2);

  assert(points[0].position.row == 10);
  assert(points[0].position.col == 1);
  assert(points[0].direction == Direction::South);
  assert(points[0].score == 1009);

  assert(points[1].position.row == 10);
  assert(points[1].position.col == 1);
  assert(points[1].direction == Direction::North);
  assert(points[1].score == 1009);
}

void should_not_return_move_forward_candidate_if_there_is_a_wall_in_front_4() {
  std::print("should_not_return_move_forward_candidate_if_there_is_a_wall_in_"
             "front_4\n");
  // Given
  Point point{
      .position = {.row = 3, .col = 13},
      .direction = Direction::East,
      .score = 1,
  };

  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  std::vector<Point> points = calculate_candidates(map, point);

  // Then
  assert(points.size() == 2);

  assert(points[0].position.row == 3);
  assert(points[0].position.col == 13);
  assert(points[0].direction == Direction::North);
  assert(points[0].score == 1001);

  assert(points[1].position.row == 3);
  assert(points[1].position.col == 13);
  assert(points[1].direction == Direction::South);
  assert(points[1].score == 1001);
}

void should_initialize_state_correctly() {
  std::print("should_initialize_state_correctly\n");
  // Given
  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);

  // When
  State state = initialize_state(map);

  // Then
  assert(state.map.start.row == 13);
  assert(state.map.start.col == 1);
  assert(state.map.end.row == 1);
  assert(state.map.end.col == 13);

  for (int row = 0; row < 14; row++) {
    for (int col = 0; col < 14; col++) {
      assert(state.map.data[row][col] == input[row * 16 + col]);
    }
  }

  assert(state.queue.size() == 1);
  assert(state.queue.top().position.row == map.start.row);
  assert(state.queue.top().position.col == map.start.col);
  assert(state.queue.top().direction == Direction::East);
  assert(state.queue.top().score == 0);

  assert(state.visited.size() == 0);
}

void should_hash_point_corectly() {
  // Given
  std::print("should_hash_point_corectly\n");
  Point point{
      .position = {1, 1},
      .direction = Direction::North,
      .score = 12,
  };

  // When
  std::string result = hash(point);

  // Then
  assert(result == "1,1/North");
}

void should_hash_point_corectly_2() {
  // Given
  std::print("should_hash_point_corectly_2\n");
  Point point{
      .position = {2, 5},
      .direction = Direction::South,
      .score = 122,
  };

  // When
  std::string result = hash(point);

  // Then
  assert(result == "2,5/South");
}

void should_hash_point_corectly_3() {
  // Given
  std::print("should_hash_point_corectly_3\n");
  Point point{
      .position = {9, 2},
      .direction = Direction::West,
      .score = 2,
  };

  // When
  std::string result = hash(point);

  // Then
  assert(result == "9,2/West");
}

void should_hash_point_corectly_4() {
  // Given
  std::print("should_hash_point_corectly_4\n");
  Point point{
      .position = {11, 55},
      .direction = Direction::East,
      .score = 555,
  };

  // When
  std::string result = hash(point);

  // Then
  assert(result == "11,55/East");
}

void should_step_correctly() {
  std::print("should_step_correctly\n");
  // Given
  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);
  State state = initialize_state(map);

  // When
  std::optional<Point> result = step(state);

  // Then
  assert(state.queue.size() == 3);

  Point point = state.queue.top();
  assert(point.position.row == map.start.row);
  assert(point.position.col == map.start.col + 1);
  assert(point.direction == Direction::East);
  assert(point.score == 1);

  state.queue.pop();
  point = state.queue.top();
  assert(point.position.row == map.start.row);
  assert(point.position.col == map.start.col);
  assert(point.direction == Direction::North);
  assert(point.score == 1000);

  state.queue.pop();
  point = state.queue.top();
  assert(point.position.row == map.start.row);
  assert(point.position.col == map.start.col);
  assert(point.direction == Direction::South);
  assert(point.score == 1000);

  assert(state.visited.size() == 1);
  auto it = state.visited.begin();
  assert(*it == "13,1/East");

  assert(result.has_value() == false);
}

void should_return_point_if_end_found() {
  std::print("should_return_point_if_end_found\n");
  // Given
  const std::string input = "###############\n"
                            "#.......#...SE#\n"
                            "#.#.###.#.###.#\n"
                            "#.....#.#...#.#\n"
                            "#.###.#####.#.#\n"
                            "#.#.#.......#.#\n"
                            "#.#.#####.###.#\n"
                            "#...........#.#\n"
                            "###.#.#####.#.#\n"
                            "#...#.....#.#.#\n"
                            "#.#.#.###.#.#.#\n"
                            "#.....#...#.#.#\n"
                            "#.###.#.#.#.#.#\n"
                            "#...#.....#...#\n"
                            "###############";
  std::istringstream iss(input);
  Map map = read_map(iss);
  State state = initialize_state(map);

  // When
  step(state);
  std::optional<Point> result = step(state);

  // Then
  assert(state.queue.size() == 2);

  Point point = state.queue.top();
  assert(point.position.row == map.start.row);
  assert(point.position.col == map.start.col);
  assert(point.direction == Direction::North);
  assert(point.score == 1000);

  state.queue.pop();
  point = state.queue.top();
  assert(point.position.row == map.start.row);
  assert(point.position.col == map.start.col);
  assert(point.direction == Direction::South);
  assert(point.score == 1000);

  assert(result.has_value() == true);
  Point result_point = result.value();
  assert(result_point.position.row == 1);
  assert(result_point.position.col == 13);
  assert(result_point.direction == Direction::East);
  assert(result_point.score == 1);
}

void should_find_the_correct_path() {
  std::print("should_find_the_correct_path\n");
  // Given
  std::string input = example_map;
  std::istringstream iss(input);
  Map map = read_map(iss);
  State state = initialize_state(map);

  // When
  long result = find_path(state);

  // Then
  assert(result == 7036);
}

void should_find_the_correct_path_2() {
  std::print("should_find_the_correct_path_2\n");
  // Given
  std::string input = example_map_2;
  std::istringstream iss(input);
  Map map = read_map(iss);
  State state = initialize_state(map);

  // When
  long result = find_path(state);

  // Then
  assert(result == 11048);
}

int main() {
  should_correctly_read_input();
  should_correctly_read_input_2();
  should_return_correct_candidates();
  should_return_correct_candidates_2();
  should_return_correct_candidates_3();
  should_return_correct_candidates_4();
  should_not_return_move_forward_candidate_if_there_is_a_wall_in_front();
  should_not_return_move_forward_candidate_if_there_is_a_wall_in_front_2();
  should_not_return_move_forward_candidate_if_there_is_a_wall_in_front_3();
  should_not_return_move_forward_candidate_if_there_is_a_wall_in_front_4();
  should_initialize_state_correctly();
  should_hash_point_corectly();
  should_hash_point_corectly_2();
  should_hash_point_corectly_3();
  should_hash_point_corectly_4();
  should_step_correctly();
  should_return_point_if_end_found();
  should_find_the_correct_path();
  should_find_the_correct_path_2();
}
