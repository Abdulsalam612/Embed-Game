#include "GameEngine.h"

GameEngine::GameEngine(N5110& lcd, Adafruit_ST7735& tft, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2)
    : lcd(lcd), tft(tft), joystick1(joystick1), joystick2(joystick2), button1(button1), button2(button2),
      character(42, 24, 40) // Example initial positions and ground level
{
}

void GameEngine::init() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.6);
    lcd.setBrightness(0.6);
    joystick1.init();
    joystick2.init();
    button1.mode(PullUp);
    tft.initR(INITR_GREENTAB2);
    tft.fillScreen(ST7735_BLACK);
}

void GameEngine::run() {
    init();
    while (true) {
        refreshDisplay();
        character.updatePosition(joystick1);
        if (button2 == 1) {  // Assuming button2 is active low
            character.updateShootingDirection(joystick2, projectiles);
        }

        handleProjectiles();

        character.applyGravity();
        character.jump(button1 == 0);
        character.boundaryCheck();

        lcd.refresh();
        ThisThread::sleep_for(30ms);
    }
}

void GameEngine::handleProjectiles() {
    for (auto& p : projectiles) {
        p.update();
        lcd.setPixel(round(p.x), round(p.y), 1); // Example method, adjust to your LCD's API
    }
}

void GameEngine::refreshDisplay() {
    lcd.clear();
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    lcd.drawRect(character.x_pos, character.y_pos, 4, 7, FILL_BLACK);
}
