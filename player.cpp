#include "player.h"

Player::Player(string name, char shape, string type) : name{name}, type{type},shape{shape}
{
}

Player::~Player()
{
}

void Player::setName(const string name)
{
  this->name = name;
}

void Player::setShape(char shape)
{
  //this->shape = shape;
}

void Player::setType(const string type)
{
  this->type = type;
}

string Player::getName() const
{
  return this->name;
}

char Player::getShape() const
{
  return this->shape;
}

string Player::getType() const
{
  return this->type;
}