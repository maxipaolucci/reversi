#include "game.h"

Game::Game()
{
  this->new_game();
}

// Game::Game(const Game &source) : Game{source.board_ptr} {
//   cout << "Game copy constructor called."<< endl;
// }

// Game::Game(Game &&source) : Game{source.board} {
//   source.board = nullptr;
//   cout << "Game move constructor called."<< endl;
// }

Game::~Game()
{
  cout << "Destroying Game object" << endl;
}

unique_ptr<Player> Game::get_player(char shape) {
  if (this->player_one.getShape() == shape) {
    return make_unique<Player>(this->player_one);
  }
  
  return make_unique<Player>(this->player_two);
}

void Game::create_players() {
  vector<Player> players = ConsoleRenderer::get_instance()->create_players();
  this->player_one = players.at(0);
  this->player_two = players.at(1);
}

void Game::create_board() {
  this->board_ptr = make_unique<Board>();
}

void Game::new_game() {
  this->create_players();
  
  ScoreBoard::create_instance(this->player_one, this->player_two);

  if (!this->board_ptr) {
    this->create_board();
  }

  ConsoleRenderer::get_instance()->render_board(this->board_ptr->get_board());
}

unique_ptr<Board> &Game::get_board() {
  return this->board_ptr;
}
