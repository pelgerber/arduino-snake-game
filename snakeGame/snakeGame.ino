/*
  SnakeGame

  Play Snake Game on Arduino Uno R4 WiFi LED matrix. Controls are via Serial input.
  A serial terminal like PuTTY or picocom can be used to interact with the Arduino.

  The circuit:
  - none

*/

#if __has_include("ArduinoGraphics.h") 
  // To use ArduinoGraphics APIs, please include BEFORE Arduino_LED_Matrix
  #include <ArduinoGraphics.h>
#endif
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

const String gameoverMsg =  "  GAME OVER  ";
const String welcomeMsg =   "  SNAKE GAME  ";
const String scoreMsg =     "  SCORE:  ";


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
  Serial.println(__cplusplus);
}

void displayScrollText(String text) {
  #ifdef _ARDUINO_GRAPHICS_H
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(100);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  // add the text
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
  #endif
}

void setup() {

  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // start LED matrix
  matrix.begin();

  printControls();

  displayScrollText(welcomeMsg);

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

  const uint32_t score = snake.getBodyPoints().size();

  delay(1000);

  // get score (snake lenght)
  Serial.print("Score: ");
  Serial.println(score);

  displayScrollText(gameoverMsg);

  displayScrollText(scoreMsg + String(score));

  delay(1000);
  snake.clear();

}


void loop() {

  key = Serial.read();

  if (key == keyUp) {
    snake.turn(Snake::Direction::LEFT);
  }
  else if (key == keyDown) {
    snake.turn(Snake::Direction::RIGHT);
  }
  else if (key == keyRight) {
    snake.turn(Snake::Direction::UP);
  }
  else if (key == keyLeft) {
    snake.turn(Snake::Direction::DOWN);
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
