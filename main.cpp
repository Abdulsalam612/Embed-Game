#include "mbed.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Joystick.h"
#include "Adafruit_ST7735.h"
#include "N5110.h"

//Pin assignment:  (MOSI, MISO, SCK,  TCS,   DC,  RST)
Adafruit_ST7735 tft(PA_7, PA_6, PA_5, PB_6, PC_10, PA_3);

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

// Joystick pins   y     x
Joystick joystick1(PC_1, PC_0);
Joystick joystick2(PC_2, PC_3);

DigitalIn button1(PB_0);
DigitalIn button2(PA_8);

int main() {
    GameEngine game(lcd, tft, joystick1, joystick2, button1, button2);
    game.run(); 
    return 0;
}
