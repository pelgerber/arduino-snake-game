/*
  SnakeGame

  Play Snake Game on Arduino Uno R4 WiFi LED matrix. Controls are via Serial input.
  A serial terminal like PuTTY or picocom can be used to interact with the Arduino.

  The circuit:
  - none

*/
#include <Arduino_LED_Matrix.h>
#include "Snake.h"

#define ROWS 8
#define COLUMNS 12

ArduinoLEDMatrix matrix;

Snake snake(ROWS, COLUMNS);
Snake::SnakePoint food;

byte frame[ROWS][COLUMNS] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte dead[ROWS][COLUMNS] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0 },
  { 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1 },
  { 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
  { 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1 },
  { 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte gameover[ROWS][COLUMNS] = {
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 }
};

int key = -1;
int keyUp = 'w';
int keyDown = 's';
int keyRight = 'd';
int keyLeft = 'a';


void printControls(){
  Serial.println("Controllers:");
  Serial.print("key UP: ");
  Serial.println((char)keyUp);
  Serial.print("key DOWN: ");
  Serial.println((char)keyDown);
  Serial.print("key RIGHT: ");
  Serial.println((char)keyRight);
  Serial.print("key LEFT: ");
  Serial.println((char)keyLeft);
}

void setup() {

  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // start LED matrix
  matrix.begin();

  printControls();

  placeFood();

}

void renderSnake(void) {
  // reset frame
  memset(frame, 0, sizeof(frame[0][0]) * ROWS * COLUMNS);
  

  auto points = snake.getBodyPoints();

  // paint snake on frame
  for (auto &iPoint : points) {
    frame[iPoint.x][iPoint.y] = 1;
  }

  // log points
  //snake.showPoints();

  // render snake
  matrix.renderBitmap(frame, ROWS, COLUMNS);
}


void placeFood() {

  bool err = false;

  do{
    err = false;

    food.x = (uint32_t)random(ROWS);
    food.y = (uint32_t)random(COLUMNS);

    for (auto &iPoint : snake.getBodyPoints()) {
      if (iPoint == food) {
        err = true;
        break;
      }
    }

  }while(err);

}

void renderFood(void) {

  frame[food.x][food.y] = 1;
  matrix.renderBitmap(frame, ROWS, COLUMNS);

}

void gameOver(void) {

  // get score (snake lenght)
  Serial.print("Score: ");
  Serial.println(snake.getBodyPoints().size());

  matrix.renderBitmap(dead, ROWS, COLUMNS);
  delay(1000);
  matrix.renderBitmap(gameover, ROWS, COLUMNS);
  delay(1000);
  snake.clear();

}


void loop() {

  key = Serial.read();

  if (key == keyUp) {
    snake.turn(Snake::Direction::UP);
  }
  else if (key == keyDown) {
    snake.turn(Snake::Direction::DOWN);
  }
  else if (key == keyRight) {
    snake.turn(Snake::Direction::RIGHT);
  }
  else if (key == keyLeft) {
    snake.turn(Snake::Direction::LEFT);
  }

  if (snake.getHead() == food) {
    snake.grow();
    placeFood();
  }

  renderSnake();
  delay(100);
  renderFood();
  delay(100);
  snake.move();

  if(snake.isDead()) {
    gameOver();
  }

}
