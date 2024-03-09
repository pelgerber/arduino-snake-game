/*
  SerialPen

  Paints on Arduino Uno R4 WiFi LED matrix based on commands from Serial input.
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

int key = -1;
int keyUp = 'w';
int keyDown = 's';
int keyRight = 'd';
int keyLeft = 'a';


int getKey(){
  int userInput = 0;
  //size_t currentPos = snake.getIdx();
  size_t currentPos = 0;

  while (!Serial.available()) {
    // while waiting for input switch on and off pointer LED to make it less bright
    delay(50);
    matrix.on(currentPos);
    delay(50);
    matrix.off(currentPos);
  }

  // use only last char
  while (Serial.available()>0) {
    userInput = Serial.read();
  }

  return userInput;
}


void printConfig(){
  Serial.println("Configuration:");
  Serial.print("key UP: ");
  Serial.println((char)keyUp);
  Serial.print("key DOWN: ");
  Serial.println((char)keyDown);
  Serial.print("key RIGHT: ");
  Serial.println((char)keyRight);
  Serial.print("key LEFT: ");
  Serial.println((char)keyLeft);
  Serial.print("key WRITE mode: ");
}


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // start LED matrix
  matrix.begin();

  snake.turn(Snake::Direction::DOWN); 


  snake.move();
  snake.grow();
  snake.move();
  snake.grow();
  snake.move();
  snake.grow();
  snake.move();
  snake.grow();
  snake.move();

}


void loop() {

  key = Serial.read();

  if (key == keyUp){
    snake.turn(Snake::Direction::UP);
  }
  else if (key == keyDown){
    snake.turn(Snake::Direction::DOWN);
  }
  else if (key == keyRight){
    snake.turn(Snake::Direction::RIGHT);
  }
  else if (key == keyLeft){
    snake.turn(Snake::Direction::LEFT);
  }

  // reset frame
  memset(frame, 0, sizeof(frame[0][0]) * ROWS * COLUMNS);
  

  auto points = snake.getBodyPoints();

  // paint snake on frame
  for (auto &iPoint : points) {
    frame[iPoint.x][iPoint.y] = 1;
  }

  snake.showPoints();

  matrix.renderBitmap(frame, ROWS, COLUMNS);

  delay(200);
  snake.move();

}
