#include "Arduino.h"
#include "Snake.h"

#define DECR_POS(pos, size) ( (pos > 0) ? (pos - 1) : (size - 1) )
#define INCR_POS(pos, size) ( (pos + 1) % size )

Snake::Snake(uint32_t gridHeight, uint32_t gridWidth, uint32_t start_x, uint32_t start_y) {
  this->gridHeight = gridHeight;
  this->gridWidth = gridWidth;

  // Add starting point (head)
  body.push_back(SnakePoint(start_x, start_y));

  /*for (const auto &item : body) {
    Serial.println("point: ");
    Serial.println(item.x);
    Serial.println(item.y);
  }*/
};

SnakePoint Snake::getHead(void) {
  return this->body.back();
}

/*size_t Pen::getIdx(){
  return pos_x + (frameWidth * pos_y);
}

void Pen::setMode(eMode_t mode){
  curr_mode = mode;
  this->update();
}

void Pen::clear(){
  for (int r=0; r<frameHeight; r++){
    for (int c=0; c<frameWidth; c++){
      ppFrame[r][c] = 0;
    }
  }
}*/

void Snake::update(void){

  // need to update point by point checking based on next point
  /*for (auto const &point ) {
    
  }

  switch (curr_mode) {
    case WRITING:
      ppFrame[pos_y][pos_x] = 1;
      break;
    case MOVING:
      break;
    case ERASING:
      ppFrame[pos_y][pos_x] = 0;
      break;
  }*/
}


void Snake::turn(Snake::Direction dir) {

  switch (dir) {
    case Snake::Direction::UP:
      head.y = DECR_POS(head.y, gridHeight);
      break;
    case Snake::Direction::DOWN:
      head.y = INCR_POS(head.y, gridHeight);
      break;
    case Snake::Direction::RIGHT:
      head.x = INCR_POS(head.x, gridWidth);
      break;
    case Snake::Direction::LEFT:
      head.x = DECR_POS(head.x, gridWidth);
      break;
  }

  this->update();
}