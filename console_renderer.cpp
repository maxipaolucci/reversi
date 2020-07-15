#include "console_renderer.h"

ConsoleRenderer *ConsoleRenderer::instance = nullptr;

ConsoleRenderer::ConsoleRenderer()
{
}

ConsoleRenderer::~ConsoleRenderer()
{
}

ConsoleRenderer *ConsoleRenderer::get_instance()
{
  if(instance == nullptr){
    instance = new ConsoleRenderer();
  }
  return instance;
}

void ConsoleRenderer::render_board(array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> board) const {
  cout << "\n  ";
  for (int col = 0; col < Constants::BOARD_SIZE; col++) {
    cout << col << " ";
  }
  cout << endl;

  for (int row = 0; row < Constants::BOARD_SIZE; row++)
  {
    for (int col = 0; col < Constants::BOARD_SIZE; col++)
    {
      if (col == 0) {
        cout << row << " ";
      }
      cout << board[col][row] << " ";
    }

    cout << row << endl;
  }

  cout << "  ";
  for (int col = 0; col < Constants::BOARD_SIZE; col++) {
    cout << col << " ";
  }
  cout << endl;

  cout << endl;
}

void ConsoleRenderer::render_score_board(Player player_one, Player player_two, int player_one_score, int player_two_score) {
  this->print_message("game", "Scores");
  this->print_message("game", "---------------------");
  this->print_message("game", player_one.getName() + " (" + player_one.getShape() + "): " + to_string(player_one_score));
  this->print_message("game", player_two.getName() + " (" + player_two.getShape() + "): " + to_string(player_two_score));
  cout << endl;
}

vector<Player> ConsoleRenderer::create_players() {
  vector<Player> players;
  string player_name {};
  
  this->print_message("input", "Name player one: ", false);
  cin >> player_name;
  Player *player_one = new Player(player_name, Shape::cross);
  players.push_back(*player_one);

  this->print_message("input", "Name player two: ", false);
  cin >> player_name;
  Player *player_two = new Player(player_name, Shape::circle);
  players.push_back(*player_two);

  this->print_message("info", "Players created!");
  this->print_message("info", "Player one: " + player_one->getName() + " (" + player_one->getShape() + ")");
  this->print_message("info", "Player two: " + player_two->getName() + " (" + player_two->getShape() + ")");
  

  return players;
}

void ConsoleRenderer::print_message(string type, string const message, bool const end_with_new_line) {
  // Convert type to uppercase
  transform(type.begin(), type.end(),type.begin(), [](unsigned char c) -> unsigned char { return toupper(c); });
  
  cout << "[" << type << "] " << message;

  if (end_with_new_line) {
    cout << endl;
  }
}