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

  Serial.println("Starting pen..\n");

  Snake snake(ROWS, COLUMNS);

  snake.turn(Snake::Direction::RIGHT); 

  snake.showPoints();
  snake.move();
  snake.showPoints();
  snake.grow();
  snake.move();
  snake.showPoints();
  snake.grow();
  snake.move();
  snake.showPoints();
  snake.grow();
  snake.move();
  snake.showPoints();
  snake.turn(Snake::Direction::UP);
  snake.move();
  snake.showPoints();
  snake.turn(Snake::Direction::LEFT);
  snake.move();
  snake.showPoints();
  snake.turn(Snake::Direction::DOWN);
  Serial.println("Now sanke should die..");
  snake.move();
  snake.showPoints();
  snake.move();
  snake.showPoints();
  snake.move();
  snake.showPoints();




}


void loop() {


}
