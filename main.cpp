#include <iostream>
#include <memory>

#include "game.h"
#include "move.h"
#include "shape.h"
#include "turn_handler.h"
#include "score_board.h"

using namespace std;

int main() {
  unique_ptr<Game> game_ptr = make_unique<Game>();
  unique_ptr<Player> current_player_ptr;

  int col {0};
  int row {0};
  while(!game_ptr->get_board()->is_full() && col != 999) {
    current_player_ptr = game_ptr->get_player(TurnHandler::get_instance()->getCurrent());
    
    if (!game_ptr->get_board()->is_block(current_player_ptr->getShape())) {
      ConsoleRenderer::get_instance()->print_message("game", current_player_ptr->getName() + "'s (" + current_player_ptr->getShape() + ") turn...");
      ConsoleRenderer::get_instance()->print_message("input", "Select a cell (col, row) separated by space: ", false);
      cin >> col >> row;
      
      bool is_valid_move = game_ptr->get_board()->move(make_shared<Move>(col, row, current_player_ptr->getShape()));

      if (is_valid_move) {
        ScoreBoard::get_instance()->render();
        TurnHandler::get_instance()->next();
      }
    } else {
      ConsoleRenderer::get_instance()->print_message("game", current_player_ptr->getName() + " (" + current_player_ptr->getShape() + ") is blocked to do any moves, next player moves...");
      TurnHandler::get_instance()->next();
    }
  }

  if (game_ptr->get_board()->is_full()) {
    char winnerShape = ScoreBoard::get_instance()->get_winner();
    if (winnerShape == '=') {
      ConsoleRenderer::get_instance()->print_message("game", "Congratulations was a tie!");
    } else {
      unique_ptr<Player> winner = game_ptr->get_player(winnerShape);
      ConsoleRenderer::get_instance()->print_message("game", winner->getName() + " (" + winner->getShape() + ") won. Well done!");
    }
    
  }

  ConsoleRenderer::get_instance()->print_message("game", "Ta luego!");

  return 0;
}