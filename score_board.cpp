#include "score_board.h"


ScoreBoard *ScoreBoard::instance = nullptr;

ScoreBoard::ScoreBoard(const Player player_one, const Player player_two)
    : player_one{player_one}, player_two{player_two}, player_one_score{2}, player_two_score{2}
{
}

ScoreBoard::~ScoreBoard()
{
  delete instance;
}

ScoreBoard *ScoreBoard::get_instance()
{
  if(instance == nullptr){
    cout << "[ERROR] ScoreBoard instance was not created yet. The instance is pointing to nullptr";

    return instance;
  }
  return instance;
}

void ScoreBoard::create_instance(const Player player_one, const Player player_two) {
  delete instance;
  instance = new ScoreBoard(player_one, player_two);
}

void ScoreBoard::increment(const char shape, const int points) {
  if (this->player_one.getShape() == shape) {
    player_one_score += points;
    player_two_score -= (points - 1); // decrement the flipped coins
  } else {
    player_two_score += points;
    player_one_score -= (points - 1); // decrement the flipped coins
  }
}

void ScoreBoard::render() const {
  ConsoleRenderer::get_instance()->render_score_board(player_one, player_two, player_one_score, player_two_score);
}

char ScoreBoard::get_winner() const {
  if (this->player_one_score > this->player_two_score) {
    return this->player_one.getShape();
  } if (this->player_one_score < this->player_two_score) {
    return this->player_two.getShape();
  } else {
    return '=';
  }
}