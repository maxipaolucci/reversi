#ifndef MOVE_H_
#define MOVE_H_

class Move
{

public:
  int x;
  int y;
  char shape;

  Move(const int x,const int y,const char shape);
  ~Move();

};

#endif // MOVE_H_
