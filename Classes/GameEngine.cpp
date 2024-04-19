#include "GameEngine.h"

GameEngine::GameEngine()
    : lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10),
      tft(PA_7, PA_6, PA_5, PB_6, PC_10, PA_3),
      joystick1(PC_1, PC_0),
      joystick2(PC_2, PC_3),
      button1(PB_0),
      button2(PA_8),
      y_pos(24), x_pos(42), y_pos2(15), x_pos2(20)
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

    while (true) {
        refreshDisplay();
        updateCharacterPosition(joystick1);
        updateShootingDirection(joystick2);

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

void GameEngine::boundary(int x, int y) {
    if (x < 1 ){        //ensure that the point doesnt pass beyond the left hand side of the screen
        x_pos = 1;
        x_pos2 = 1;
    }else if (x > 81){  //ensure that the point doesnt pass beyond the right hand side of the screen-
        x_pos = 81;
        x_pos2 = 81;
    }

    if(y < 1){          //ensure that the point doesnt pass beyond the top of the screen
        y_pos = 1;
        y_pos2 = 1;
    }else if(y > 45){   //ensure that the point doesnt pass beyond the bottom of the screen
        y_pos = 45;
        y_pos2 = 45;
    }
}

void GameEngine::refreshDisplay() {
    lcd.clear();
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    lcd.drawRect(x_pos, y_pos, 2, 2, FILL_BLACK);
    lcd.drawCircle(x_pos2, y_pos2, 3, FILL_BLACK);
}
