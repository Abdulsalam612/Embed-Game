#include "mbed.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Joystick.h"
#include "N5110.h"
#include "MainMenu.h"

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

// Joystick pins   y     x
Joystick joystick1(PC_1, PC_0);
Joystick joystick2(PC_2, PC_3);

DigitalIn button1(PB_0);
DigitalIn button2(PA_8);

int main() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.6);
    lcd.setBrightness(0.6);
    joystick1.init();
    button1.mode(PullUp);

    MainMenu mainMenu(lcd, joystick1, button1);
    mainMenu.display();
    while (!mainMenu.isStartSelected()) {
        ThisThread::sleep_for(100ms);
    }

    GameEngine game(lcd, joystick1, joystick2, button1, button2);
    game.run(); 
    return 0;
}