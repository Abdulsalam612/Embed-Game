// IntroAnimation.h

#ifndef INTRO_ANIMATION_H
#define INTRO_ANIMATION_H

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"

class IntroAnimation {
public:
    IntroAnimation(N5110& lcd, Joystick& joystick, DigitalIn& button);
    void play();

private:
    N5110& lcd;
    Joystick& joystick;
    DigitalIn& button;
};

#endif