#ifndef TURN_HANDLER_H_
#define TURN_HANDLER_H_

#include "shape.h"

class TurnHandler
{
private:
  static TurnHandler *instance;
  char current;
  char previous;
  TurnHandler(); // Constructor? (the {} brackets) are needed here.

public:
  ~TurnHandler();
  TurnHandler(TurnHandler &other) = delete; // remove copy constructor. Singleton should not be clonable
  void operator=(const TurnHandler &) = delete; // remove assign operator
  static TurnHandler *get_instance();

  char getCurrent() const;
  void setCurrent(char shape);
  char getPrevious() const;
  void next();
};

#endif // !TURN_HANDLER_H_
