#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mbed.h"
#include "Joystick.h"
#include "Bitmap.h"

#include "Adafruit_ST7735.h"
#include "N5110.h"

#include "Character.h" // Include the Character header

class GameEngine {
public:
    GameEngine();
    void run();

private:
    void updateCharacterPosition(Joystick& joystick);
    void updateShootingDirection(Joystick& joystick);
    void boundary(float& x, float& y);
    void init();
    void refreshDisplay();

    // Hardware components
    N5110 lcd;
    Adafruit_ST7735 tft;
    Joystick joystick1;
    Joystick joystick2;
    DigitalIn button1;
    DigitalIn button2;

     // Game state
    float y_pos, x_pos, y_pos2, x_pos2;
    float groundLevel;
    float velocity_y, gravity;
    bool buttonReleased; // To manage jump button state
};

#endif
