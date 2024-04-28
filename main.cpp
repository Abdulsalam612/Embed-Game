#include "mbed.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Joystick.h"
#include "N5110.h"
#include "MainMenu.h"
#include "IntroAnimation.h"

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

// Joystick pins   y     x
Joystick joystick1(PC_1, PC_0);
Joystick joystick2(PC_2, PC_3);

DigitalIn button1(PB_0);
DigitalIn button2(PA_8);

int main() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.4);
    lcd.setBrightness(0.6);

    joystick1.init();
    button1.mode(PullUp);
    button2.mode(PullDown);

    MainMenu mainMenu(lcd, joystick1, button1);
    GameEngine gameEngine(lcd, joystick1, joystick2, button1, button2);

    IntroAnimation introAnimation(lcd, joystick1, button1);  // Declare the introAnimation object
    while (true) {
        introAnimation.showPressAnyButtonScreen();  // Show the "Press any button to start" screen
        introAnimation.playAnimation();  // Play the intro animation

        while (true) {
            mainMenu.display();
            if (mainMenu.isStartSelected()) {
                bool gameResult = gameEngine.run();
                if (!gameResult) {
                    break;  // Exit the inner loop if the player is dead
                }
            } else {
                // Add a small delay to prevent the button press from being registered for the "Press any button to start" screen
                ThisThread::sleep_for(500ms);
                break;  // Exit the inner loop if the player selects "Quit"
            }
        }

        // If the player selects "Quit", the outer loop will continue and the "Press any button to start" screen will be shown again
    }

    return 0;
}