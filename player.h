#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "playertype.h"
#include "shape.h"

using namespace std;

class Player
{
  private:
  string name;
  string type;
  char shape;

  public:
  Player(string name = "Noname", char shape = Shape::circle, string type = PlayerType::human);
  ~Player();

  void setName(const string name);
  void setShape(char shape);
  void setType(const string type);

  string getName() const;
  char getShape() const;
  string getType() const;
};

#endif // PLAYER_H_
