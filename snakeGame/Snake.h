#include "Arduino.h"
#include <vector>

class SnakePoint {
  public:
  SnakePoint(uint32_t x, uint32_t y) : x(x), y(y) {}
  uint32_t x;
  uint32_t y;
};

class Snake {
  public:
    Snake(uint32_t gridHeight, uint32_t gridWidth, uint32_t start_x = 0, uint32_t start_y = 0);

    enum class Direction {
      UP = 0,
      LEFT = 1,
      RIGHT = 2,
      DOWN = 3
    };

    
    //SnakePoint getHead(void);
    void turn(Direction dir);
    void move(void);
    SnakePoint getHead(void);

  private:
    std::vector<SnakePoint> body;
    uint32_t gridHeight, gridWidth;
    Direction snakeDir;

};