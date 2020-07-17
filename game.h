#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <vector>
#include <memory>

#include "player.h"
#include "board.h"
#include "console_renderer.h"
#include "turn_handler.h"
#include "score_board.h"

class Game
{
private:
  Player player_one;
  Player player_two;
  unique_ptr<Board> board_ptr;
  
public:
  Game();
  // Game(const Game &source); //copy constructor. Called if move constructor is not provided  (l-values: named values Game game{} )
  // Game(Game &&source); //move constructor . (r-values: temp/unnamed. e.g.: Player *p = *(Game{}).get_player('x'); )
  ~Game();
  
  unique_ptr<Player> get_player(char shape);
  void create_players();
  void create_board();
  void new_game();
  unique_ptr<Board> &get_board(); //as it is a unique_ptr we need to return a reference otherwise it should be a share_ptr to make a copy
};

#endif // GAME_H_
