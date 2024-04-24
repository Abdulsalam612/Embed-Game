#include "MainMenu.h"

MainMenu::MainMenu(N5110& lcd, Joystick& joystick, DigitalIn& button)
    : lcd(lcd), joystick(joystick), button(button), selectedOption(0) {}

void MainMenu::display() {
    lcd.clear();
    lcd.printString("Main Menu", 14, 0);
    lcd.printString("Start Game", 14, 2);
    lcd.printString("Options", 21, 3);
    lcd.printString("About", 23, 4);
    lcd.printString("Quit", 24, 5);

    // Draw the rectangle at the current selected option
    if (selectedOption == 0) {
        lcd.drawRect(13, 15, 65, 10, FILL_TRANSPARENT);
    } else if (selectedOption == 1) {
        lcd.drawRect(18, 23, 46, 10, FILL_TRANSPARENT);
    } else if (selectedOption == 2) {
        lcd.drawRect(20, 31, 38, 9, FILL_TRANSPARENT);
    } else if (selectedOption == 3) {
        lcd.drawRect(22, 39, 28, 9, FILL_TRANSPARENT);
    }

    lcd.refresh();
}

bool MainMenu::isStartSelected() {
    while (true) {
        Direction dir = joystick.get_direction();
        if (dir == N && selectedOption > 0) {
            selectedOption--;
            display(); // Redraw the menu with the updated selection
        } else if (dir == S && selectedOption < 3) {
            selectedOption++;
            display(); // Redraw the menu with the updated selection
        }

        if (button == 0) {
            if (selectedOption == 0) {
                return true;
            } else if (selectedOption == 1) {
                handleOptions();
            } else if (selectedOption == 2) {
                handleAbout();
            } else if (selectedOption == 3) {
                return false;
            }
        }

        ThisThread::sleep_for(100ms); // Add a small delay to avoid excessive CPU usage
    }
}

void MainMenu::handleOptions() {
    lcd.clear();
    lcd.printString("Options", 14, 0);
    lcd.printString("Option 1", 0, 2);
    lcd.printString("Option 2", 0, 3);
    lcd.printString("Back", 0, 4);
    lcd.refresh();

    while (true) {
        if (button == 0) {
            break;
        }
        ThisThread::sleep_for(100ms);
    }
}

void MainMenu::handleAbout() {
    lcd.clear();
    lcd.printString("About", 14, 0);
    lcd.printString("Game Version 1.0", 0, 2);
    lcd.printString("Developed by", 0, 3);
    lcd.printString("Abdulsalam", 0, 4);
    lcd.refresh();

    while (true) {
        if (button == 0) {
        break;
         }
    ThisThread::sleep_for(100ms);
    }
}