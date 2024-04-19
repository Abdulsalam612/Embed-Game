#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mbed.h"
#include "Joystick.h"
#include "Bitmap.h"

#include "Adafruit_ST7735.h"
#include "N5110.h"

class GameEngine {
public:
    GameEngine();
    void run();

private:
    void updateCharacterPosition(Joystick& joystick);
    void updateShootingDirection(Joystick& joystick);
    void boundary(int x, int y);
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
    float y_pos;
    float x_pos;
    float y_pos2;
    float x_pos2;
};

#endif
