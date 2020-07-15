#include "turn_handler.h"

TurnHandler *TurnHandler::instance = nullptr;

TurnHandler::TurnHandler(): current(Shape::circle), previous{Shape::cross}
{
}

TurnHandler::~TurnHandler()
{
}

TurnHandler *TurnHandler::get_instance()
{
  if(instance == nullptr){
    instance = new TurnHandler();
  }
  return instance;
}

char TurnHandler::getCurrent() const {
  return this->current;
}
void TurnHandler::setCurrent(char shape) {
  this->previous = this->current;
  this->current = shape;
}

char TurnHandler::getPrevious() const {
  return this->previous;
}

void TurnHandler::next() {
  if (this->current == Shape::cross) {
    this->setCurrent(Shape::circle);
  } else {
    this->setCurrent(Shape::cross);
  }
}
