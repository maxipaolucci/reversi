#include <iostream>

#include "game.h"
#include "move.h"
#include "shape.h"
#include "turn_handler.h"
#include "score_board.h"

using namespace std;

int main() {
  Game *game = new Game();
  Player *currentPlayer {nullptr};

  int col {0};
  int row {0};
  while(!game->get_board()->is_full() && col != 999) {
    currentPlayer = game->get_player(TurnHandler::get_instance()->getCurrent());
    
    if (!game->get_board()->is_block(currentPlayer->getShape())) {
      ConsoleRenderer::get_instance()->print_message("game", currentPlayer->getName() + "'s (" + currentPlayer->getShape() + ") turn...");
      ConsoleRenderer::get_instance()->print_message("input", "Select a cell (col, row) separated by space: ", false);
      cin >> col >> row;
      
      Move *move = new Move(col, row, currentPlayer->getShape());
      bool is_valid_move = game->get_board()->move(*move);

      if (is_valid_move) {
        ScoreBoard::get_instance()->render();
        TurnHandler::get_instance()->next();
      }
      
      delete move;
    } else {
      ConsoleRenderer::get_instance()->print_message("game", currentPlayer->getName() + " (" + currentPlayer->getShape() + ") is blocked to do any moves, next player moves...");
      TurnHandler::get_instance()->next();
    }
  }

  if (game->get_board()->is_full()) {
    char winnerShape = ScoreBoard::get_instance()->get_winner();
    if (winnerShape == '=') {
      ConsoleRenderer::get_instance()->print_message("game", "Congratulations was a tie!");
    } else {
      Player *winner = game->get_player(winnerShape);
      ConsoleRenderer::get_instance()->print_message("game", winner->getName() + " (" + winner->getShape() + ") won. Well done!");
    }
    
  }

  ConsoleRenderer::get_instance()->print_message("game", "Ta luego!");

  delete game;

  return 0;
}