#ifndef MAINMENU_H
#define MAINMENU_H

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"

class MainMenu {
public:
    MainMenu(N5110& lcd, Joystick& joystick, DigitalIn& button);
    void display();
    bool isStartSelected();
    void handleOptions();
    void handleAbout();

private:
    N5110& lcd;
    Joystick& joystick;
    DigitalIn& button;
    int selectedOption;
};

#endif