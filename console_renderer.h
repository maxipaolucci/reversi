#ifndef CONSOLE_RENDERER_H_
#define CONSOLE_RENDERER_H_

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include "board.h"
#include "constanst.h"
#include "player.h"
#include "shape.h"


using namespace std;

class ConsoleRenderer
{
  private:
    static ConsoleRenderer *instance;
    ConsoleRenderer(); // Constructor? (the {} brackets) are needed here.
  
  // We can use the better technique of deleting the methods
  // we don't want.
  public:
    ~ConsoleRenderer();
    ConsoleRenderer(ConsoleRenderer &other) = delete; // remove copy constructor. Singleton should not be clonable
    void operator=(const ConsoleRenderer &) = delete; // remove assign operator

    static ConsoleRenderer *get_instance();
    void render_board(array<array<char, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> board) const;
    void render_score_board(Player player_one, Player player_two, int player_one_score, int player_two_score);
    vector<Player> create_players();
    void print_message(string type = "INFO", string const message = "", bool const end_with_new_line = true);
};


#endif // !CONSOLE_RENDERER_H_