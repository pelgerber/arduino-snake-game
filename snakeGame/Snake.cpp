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
  this->body.push_back(SnakePoint(1, 0));
  this->body.push_back(SnakePoint(2, 0));
  this->growing = false;
  this->dead = false;
  this->snakeDir = Direction::RIGHT;

};

SnakePoint Snake::getHead(void) {
  return this->body.back();
}

void Snake::showPoints(void) {
  Serial.print("direction: ");
  Serial.println((uint8_t)this->snakeDir);

  Serial.println("points: ");
  for (const auto &point : body) {
    Serial.print(point.x);
    Serial.print(",");
    Serial.print(point.y);
    Serial.print(" ");
  }
  Serial.println(" ");

  if (this->dead) {
    Serial.println("Snake is dead!!");
  }

}

void Snake::grow() {
  this->growing = true;
}

bool Snake::isDead(void) {
  return this->dead;
}

void Snake::move(void) {

  // set previous point to the head
  SnakePoint prevPoint = this->body.back();
  SnakePoint temp;

  // move head first in the right direction
  switch (this->snakeDir) {
    case Snake::Direction::UP:
      body.back().y = DECR_POS(body.back().y, gridHeight);
      break;
    case Snake::Direction::DOWN:
      body.back().y = INCR_POS(body.back().y, gridHeight);
      break;
    case Snake::Direction::RIGHT:
      body.back().x = INCR_POS(body.back().x, gridWidth);
      break;
    case Snake::Direction::LEFT:
      body.back().x = DECR_POS(body.back().x, gridWidth);
      break;
  }

  if(this->growing) {

    this->growing = false;
    // add point (duplicate head)
    body.push_back(body.back());
    // move the older head to its previous position
    //body[body.size()-2] = prevPoint;
    body.rbegin()[1] = prevPoint;

  } else if (body.size() > 1) {

    // iterate backwards (from the point next to the head)
    for (auto rIt = (body.rbegin()+1); rIt != body.rend(); ++rIt) {

      // move the point to the position of the point before
      temp = *rIt;
      *rIt = prevPoint;
      prevPoint = temp;

    }

  }

  // check if snake is dead
  for (auto iPoint = body.begin(); iPoint != std::prev(body.end()); ++iPoint) {
    if (dead) break; // snake is already dead
    dead = body.back() == *iPoint;
  }

}


void Snake::turn(Snake::Direction dir) {
  // do not allow opposite direction
  if(!ARE_DIR_OPPOSITE(this->snakeDir, dir)) this->snakeDir = dir;

}