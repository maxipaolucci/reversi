#ifndef HELPER_H_
#define HELPER_H_

#include <string>
#include <vector>

#include "shape.h"
#include "move.h"

struct Helper
{ 
  enum compass {NW, N, NE, E, SE, S, SW, W};
  static char get_oponent_shape(char shape) {
    if (shape == Shape::circle) {
      return Shape::cross;
    } else {
      return Shape::circle;
    }
  }

  static Move next(compass direction, Move move) {
    
    switch (direction)
    {
    case NW:
      return Move{move.x - 1, move.y - 1, move.shape};
      break;
    
    case N:
      return Move{move.x, move.y - 1, move.shape};
      break;
    
    case NE:
      return Move{move.x + 1, move.y - 1, move.shape};
      break;
    
    case E:
      return Move{move.x + 1, move.y, move.shape};
      break;
    
    case SE:
      return Move{move.x + 1, move.y + 1, move.shape};
      break;
    
    case S:
      return Move{move.x, move.y + 1, move.shape};
      break;
    
    case SW:
      return Move{move.x - 1, move.y + 1, move.shape};
      break;
    
    case W:
      return Move{move.x - 1, move.y, move.shape};
      break;
    }
  }
};


#endif // HELPER_H_
