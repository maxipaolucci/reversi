#include "board.h"

Board::Board(/* args */)
{
  this->reset();
}

Board::~Board()
{
}

bool Board::is_full() const {
  for (int row = 0; row < Constants::BOARD_SIZE; row++)
  {
    for (int col = 0; col < Constants::BOARD_SIZE; col++)
    {
      if (this->board[col][row] == Constants::BOARD_EMPTY_CELL) {
        return false;
      }
    }
  }
  
  return true;
}

void Board::reset() {
  for (int row = 0; row < Constants::BOARD_SIZE; row++)
  {
    for (int col = 0; col < Constants::BOARD_SIZE; col++)
    {
      this->board[col][row] = Constants::BOARD_EMPTY_CELL;
    }
  }

  int middle = Constants::BOARD_SIZE / 2;
  
  this->board[middle - 1][middle -1] = Shape::cross;
  this->board[middle][middle - 1] = Shape::circle;
  this->board[middle - 1][middle] = Shape::circle;
  this->board[middle][middle] = Shape::cross;

  this->history.clear();
}

array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> Board::get_board() const {
  return this->board;
}

bool Board::move(const shared_ptr<Move> &move_ptr) {
  if (!this->is_valid(move_ptr)) {
    return false;
  }

  int flip_count = this->ripple(move_ptr, this->board);
  if (flip_count == 0) {
    ConsoleRenderer::get_instance()->print_message("error", "The position choosen is not valid");
    return false;
  } 
  
  ConsoleRenderer::get_instance()->print_message("info", "Flip count = " + to_string(flip_count));
  this->board[(*move_ptr).x][(*move_ptr).y] = (*move_ptr).shape;
  ConsoleRenderer::get_instance()->render_board(this->board);
  this->history.push_back(move_ptr);
  
  ScoreBoard::get_instance()->increment((*move_ptr).shape, ++flip_count);

  return true;
}

bool Board::is_block(char const shape) {
  bool result {true};
  array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> test_board;

  for (int row = 0; row < Constants::BOARD_SIZE; row++) {
    for (int col = 0; col < Constants::BOARD_SIZE; col++) {
      test_board = this->board; //copy the board, we don't want to change it in this test
      
      if (test_board[col][row] == Constants::BOARD_EMPTY_CELL) {
        if (this->ripple(make_shared<Move>(col, row, shape), test_board) > 0) {
          return false;
        }
      }
    } 
  }

  return result;
}

bool Board::is_valid(const shared_ptr<Move> &move_ptr) {
  if (!this->in_bounds((*move_ptr).x, (*move_ptr).y, true)) {
    //out of bound
    return false;
  } else if (this->board[(*move_ptr).x][(*move_ptr).y] != Constants::BOARD_EMPTY_CELL) {
    // the cell is not empty
    ConsoleRenderer::get_instance()->print_message("error", "The position choosen is not empty");
    return false;
  }

  return true;
}

bool Board::in_bounds(int const col, int const row, bool const print_messages) const {
  string message = "";
  bool result = true;
  if (col < 0 || col >= Constants::BOARD_SIZE) {
    // col out of bound
    message = "Column must be between 0 and " + to_string(Constants::BOARD_SIZE);
    result = false;
  } else if (row < 0 || row >= Constants::BOARD_SIZE) {
    // y out of bounds
    message = "Row must be between 0 and " + to_string(Constants::BOARD_SIZE);
    result = false;
  }

  if (message.size() && print_messages) {
    ConsoleRenderer::get_instance()->print_message("error", message);
  }

  return result;
}

int Board::ripple(const shared_ptr<Move> &move, array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> &new_board) {
  int total_count {0};
  array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> test_board = new_board; //copy the board

  for (size_t direction = 0; direction < 8; direction++) {
    int count {0};
    int evaluation_result {0};

    Move eval {*move};
    while (evaluation_result == 0) {
      eval = Helper::next((Helper::compass)direction, eval);
      evaluation_result = this->evaluate_direction(eval.x, eval.y, eval.shape, count, test_board);
    }
    
    if (evaluation_result == -1) {
      // discard direction
      test_board = new_board;
    } else if (evaluation_result == 1){
      // success on this direction
      new_board = test_board;
      total_count += count;
    }
  }

  return total_count;
}

/**
 * Evaluates a direction in the board.
 * 
 * @return int. 1 if finish the evaluation and was a successfull direction with a positive count. 0 if need to continue evaluating the same direction further and -1 if we need to discard
 *    the direction
 */
int Board::evaluate_direction(int const col, int const row, char const shape, int &count, array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> &test_board) {
  if (this->in_bounds(col, row, false)) {
    //if in bounds
    if (test_board[col][row] == Helper::get_oponent_shape(shape)) {
      //if oponent shape
      ++count;
      test_board[col][row] = shape;
      return 0;
    } else if (test_board[col][row] == shape && count > 0){
      // current move shape and oponent shape in between
      return 1;
    }
  }

  return -1;
}