// MainMenu.cpp
#include "MainMenu.h"

MainMenu::MainMenu(N5110& lcd, Joystick& joystick, DigitalIn& button)
    : lcd(lcd), joystick(joystick), button(button), selectedOption(0) {}

void MainMenu::display() {
    lcd.clear();
    lcd.printString("Main Menu", 14, 0);
    lcd.printString("Start Game", 0, 2);
    lcd.printString("Quit", 0, 3);

    // Draw the rectangle at the current selected option
    if (selectedOption == 0) {
        lcd.drawRect(0, 15, 70, 10, FILL_TRANSPARENT);
    } else if (selectedOption == 1) {
        lcd.drawRect(0, 24, 70, 10, FILL_TRANSPARENT);
    }

    lcd.refresh();
}

bool MainMenu::isStartSelected() {
    while (true) {
        Direction dir = joystick.get_direction();
        if (dir == N && selectedOption > 0) {
            selectedOption--;
            display(); // Redraw the menu with the updated selection
        } else if (dir == S && selectedOption < 1) {
            selectedOption++;
            display(); // Redraw the menu with the updated selection
        }

        if (button == 0 && selectedOption == 0) {
            return true;
        }

        ThisThread::sleep_for(100ms); // Add a small delay to avoid excessive CPU usage
    }
}