#ifndef SCORE_BOARD_H_
#define SCORE_BOARD_H_

#include <iostream>
#include "shape.h"
#include "player.h"
#include "renderers/console_renderer.h"

class ScoreBoard
{
private:
  static ScoreBoard *instance;
  Player player_one;
  Player player_two;
  int player_one_score;
  int player_two_score;
  ScoreBoard(const Player player_one, const Player player_two); 

public:
  ~ScoreBoard();
  ScoreBoard(ScoreBoard &other) = delete; // remove copy constructor. Singleton should not be clonable
  void operator=(const ScoreBoard &) = delete; // remove assign operator
  static ScoreBoard *get_instance();
  static void create_instance(const Player player_one,const Player player_two);

  void render() const;
  void increment(const char shape,const int points);
  char get_winner() const;
};

#endif // !SCORE_BOARD_H_
