#ifndef Board_H_
#define Board_H_

#include <iostream>
#include <array>
#include <vector>
#include <string>

#include "constanst.h"
#include "shape.h"
#include "move.h"
#include "console_renderer.h"
#include "turn_handler.h"
#include "helper.h"
#include "score_board.h"

using namespace std;

class Board
{
private:
  array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> board {Constants::BOARD_EMPTY_CELL};
  
  vector<Move> history;
  
  bool is_valid(Move move);

  bool in_bounds(int const col, int const row, bool const print_messages = false) const;

  int evaluate_direction(int const col, int const row, char const shape, int &count, array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> &test_board);

  int ripple(const Move move, array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> &new_board);

public:
  Board(/* args */);
  ~Board();

  bool is_full() const;
  
  void reset();
  
  array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> get_board() const;
  
  bool is_block(const char shape);

  bool move(const Move move);
};

#endif // !Board_H_