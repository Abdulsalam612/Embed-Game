#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mbed.h"
#include "Joystick.h"
#include "Bitmap.h"
#include "Projectile.h"
#include "Character.h"
#include <vector>

#include "Adafruit_ST7735.h"
#include "N5110.h"

class GameEngine {
public:
    GameEngine(N5110& lcd, Adafruit_ST7735& tft, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2);
    void run();

private:
    void init();
    void refreshDisplay();
    void handleProjectiles();

    // Hardware components
    N5110& lcd;
    Adafruit_ST7735& tft;
    Joystick& joystick1;
    Joystick& joystick2;
    DigitalIn& button1;
    DigitalIn& button2;

    // Game entities
    Character character;
    std::vector<Projectile> projectiles;
};

#endif
