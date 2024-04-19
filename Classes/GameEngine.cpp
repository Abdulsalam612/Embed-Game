#include "GameEngine.h"

GameEngine::GameEngine(N5110& lcd, Adafruit_ST7735& tft, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2)
    : lcd(lcd), tft(tft), joystick1(joystick1), joystick2(joystick2), button1(button1), button2(button2),
      y_pos(24), x_pos(42), y_pos2(15), x_pos2(20), groundLevel(40), velocity_y(0.0), gravity(0.5), buttonReleased(true)
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

        if (button2 == 1) {  // Assuming button2 is active low
            updateShootingDirection(joystick2);
        }

        handleProjectiles();

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
    float dx = 0, dy = 0;
    Direction dir = joystick.get_direction();

    // Define the starting point for projectiles
    float startX = x_pos + 2;  // Horizontal center of the character
    float startY = y_pos + 3.5;  // Vertical center of the character

    // Adjust start position based on the direction
    if (dir == N) {
        dy = -1;
        startY = y_pos;  // Start at the top of the character
    } else if (dir == S) {
        dy = 1;
        startY = y_pos + 7;  // Start at the bottom of the character
    } else if (dir == E) {
        dx = 1;
        startX = x_pos + 4;  // Start at the right side of the character
    } else if (dir == W) {
        dx = -1;
        startX = x_pos;  // Start at the left side of the character
    } else if (dir == NE) {
        dx = 1;
        dy = -1;
        startX = x_pos + 4;  // Start at the top-right corner
        startY = y_pos;
    } else if (dir == NW) {
        dx = -1;
        dy = -1;
        startX = x_pos;  // Start at the top-left corner
        startY = y_pos;
    } else if (dir == SE) {
        dx = 1;
        dy = 1;
        startX = x_pos + 4;  // Start at the bottom-right corner
        startY = y_pos + 7;
    } else if (dir == SW) {
        dx = -1;
        dy = 1;
        startX = x_pos;  // Start at the bottom-left corner
        startY = y_pos + 7;
    }

    // Create a projectile at the adjusted starting position with the direction of the joystick
    projectiles.push_back(Projectile(startX, startY, dx, dy));
}
void GameEngine::handleProjectiles() {
    for (auto& p : projectiles) {
        p.update();
        lcd.setPixel(round(p.x), round(p.y), 1); // Example method, adjust to your LCD's API
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
    lcd.drawRect(x_pos, y_pos, 4, 7, FILL_BLACK);
}