#include <vector>
#include <sys/_stdint.h>
#include "Arduino.h"
#include "Snake.h"

#define DECR_POS(pos, size) ( (pos > 0) ? (pos - 1) : (size - 1) )
#define INCR_POS(pos, size) ( (pos + 1) % size )

#define ARE_DIR_OPPOSITE(dir1, dir2) ((~((uint8_t)dir1) & 3) == (uint8_t)dir2)

Snake::Snake(uint32_t gridHeight, uint32_t gridWidth, uint32_t start_x, uint32_t start_y) {
  this->gridHeight = gridHeight;
  this->gridWidth = gridWidth;

  // Add starting point (head)
  //this->body.push_back(SnakePoint(start_x, start_y));
  this->body.push_back(SnakePoint(0, 0));
  this->body.push_back(SnakePoint(0, 1));
  this->body.push_back(SnakePoint(0, 2));
  this->snakeDir = Direction::RIGHT;

  /*for (const auto &item : body) {
    Serial.println("point: ");
    Serial.println(item.x);
    Serial.println(item.y);
  }*/
};

SnakePoint Snake::getHead(void) {
  return this->body.back();
}


void Snake::move(void){

  // set previous point to the head
  SnakePoint prevPoint = this->body.back();

  // move head first in the right direction
  switch (this->snakeDir) {
    case Snake::Direction::UP:
      this->body.back().y = DECR_POS(this->body.back().y, gridHeight);
      break;
    case Snake::Direction::DOWN:
      this->body.back().y = INCR_POS(this->body.back().y, gridHeight);
      break;
    case Snake::Direction::RIGHT:
      this->body.back().x = INCR_POS(this->body.back().x, gridWidth);
      break;
    case Snake::Direction::LEFT:
      this->body.back().x = DECR_POS(this->body.back().x, gridWidth);
      break;
  }

  for (std::vector<SnakePoint>::reverse_iterator rit = body.rbegin(); rit != body.rend(); ++rit) {
    *rit = prevPoint;
    prevPoint = *rit;
  }

}


void Snake::turn(Snake::Direction dir) {
  // do not allow opposite direction
  if(!ARE_DIR_OPPOSITE(this->snakeDir, dir)) this->snakeDir = dir;

}