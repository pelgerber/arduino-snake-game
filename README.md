# arduino-snake-game
Snake game for the Arduino Uno R4 WiFi, to play on the LED matrix with controls via serial input (not possible via Arduino Serial monitor).

## Dependencies
- (optional) ArduinoGraphics library (if you want to display scrolling text on LED matrix)

## How to Play
1. Clone this repository and open the sketch (snakeGame.ino) in your Arduino IDE
2. (optional) If not installed, install Arduino Graphics library
2. Upload sketch on your Arduino Uno R4 WiFi
3. Open a serial terminal (e.g. picocom or PuTTY) and connect to Arduino serial line (e.g. /dev/ttyACM0) with rate 9600
4. Reset Arduino
5. You should now see the controllers printed on serial terminal ('a'for left, 'd' for right, 'w' for up and 's' for down)
6. While in the serial terminal, you should be able to play by pressing the corresponding keys
