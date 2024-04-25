// IntroAnimation.cpp

#include "IntroAnimation.h"
#include "intro1.h"  // Add your sprite header files here

IntroAnimation::IntroAnimation(N5110& lcd, Joystick& joystick, DigitalIn& button)
    : lcd(lcd), joystick(joystick), button(button) {}

void IntroAnimation::play() {
    lcd.clear();
    lcd.printString("Press any button", 0, 0);
    lcd.printString("to start", 0, 1);
    lcd.refresh();

    while (button == 1) {
        // Wait for button press
    }

    // Display the animation sequence
    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite1);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite2);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite3);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite4);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite5);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite6);
    lcd.refresh();
    ThisThread::sleep_for(1s);

     lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite7);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite8);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite9);
    lcd.refresh();
    ThisThread::sleep_for(1s);

      lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite10);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite11);
    lcd.refresh();
    ThisThread::sleep_for(2s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite12);
    lcd.refresh();
    ThisThread::sleep_for(2s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite13);
    lcd.refresh();
    ThisThread::sleep_for(4s);
}