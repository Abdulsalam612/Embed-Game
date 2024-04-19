#include "GameEngine.h"

GameEngine::GameEngine(N5110& lcd, Adafruit_ST7735& tft, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2)
    : lcd(lcd), tft(tft), joystick1(joystick1), joystick2(joystick2), button1(button1), button2(button2),
      y_pos(24), x_pos(42), y_pos2(15), x_pos2(20), groundLevel(45), velocity_y(0.0), gravity(0.5), buttonReleased(true)
{
}

void GameEngine::init() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.6);
    lcd.setBrightness(0.6);
    joystick1.init();
    joystick2.init();
    button1.mode(PullUp);

    // Initialize Adafruit TFT
    tft.initR(INITR_GREENTAB2);
    tft.fillScreen(ST7735_BLACK);
}

void GameEngine::run() {
    init();

    const float jumpHeight = 5; // How high the character jumps
    bool isJumping = false;
    float jumpPeak = y_pos - jumpHeight; // Highest point of the jump

    while (true) {
        refreshDisplay();
        updateCharacterPosition(joystick1);
        updateShootingDirection(joystick2);

        // Handle jumping logic
        if (button1 == 0 && buttonReleased) {
            velocity_y = -5; // Start jump with initial upward velocity
            buttonReleased = false;
        } else if (button1 != 0) {
            buttonReleased = true; // Button released, ready for next jump
        }

        // Apply gravity
        velocity_y += gravity;
        y_pos += velocity_y;
        y_pos = std::min(y_pos, groundLevel);

        if (y_pos >= groundLevel) {
            y_pos = groundLevel; // Ensure character is on the ground
            velocity_y = 0; // Stop moving when on ground
        }

        boundary(x_pos, y_pos);
        boundary(x_pos2, y_pos2);
            
        lcd.refresh();
        ThisThread::sleep_for(30ms);
    }
}

void GameEngine::updateCharacterPosition(Joystick& joystick) {
    Direction dir = joystick.get_direction();
    if (dir == N) {
        y_pos--;
    } else if (dir == S) {
        y_pos++;
    } else if (dir == E) {
        x_pos++;
    } else if (dir == W) {
        x_pos--;
    } else if (dir == NE) {
        y_pos--;
        x_pos++;
    } else if (dir == NW) {
        y_pos--;
        x_pos--;
    } else if (dir == SE) {
        y_pos++;
        x_pos++;
    } else if (dir == SW) {
        y_pos++;
        x_pos--;
    }
}

void GameEngine::updateShootingDirection(Joystick& joystick) {
    Direction dir = joystick.get_direction();
    if (dir == N) {
        y_pos2--;
    } else if (dir == S) {
        y_pos2++;
    } else if (dir == E) {
        x_pos2++;
    } else if (dir == W) {
        x_pos2--;
    } else if (dir == NE) {
        y_pos2--;
        x_pos2++;
    } else if (dir == NW) {
        y_pos2--;
        x_pos2--;
    } else if (dir == SE) {
        y_pos2++;
        x_pos2++;
    } else if (dir == SW) {
        y_pos2++;
        x_pos2--;
    }
}

void GameEngine::boundary(float& x, float& y) {
    // Handle horizontal boundaries
    if (x < 1) x = 1;  // Left boundary
    else if (x > 81) x = 81;  // Right boundary

    // Handle vertical boundaries
    if (y < 1) y = 1;  // Top boundary
    else if (y > groundLevel) y = groundLevel;  // Bottom boundary (ground level)
}

void GameEngine::refreshDisplay() {
    lcd.clear();
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    lcd.drawRect(x_pos, y_pos, 2, 2, FILL_BLACK);
    lcd.drawCircle(x_pos2, y_pos2, 3, FILL_BLACK);
}