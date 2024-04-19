#include "mbed.h"
#include "Bitmap.h"
#include "Adafruit_ST7735.h"
#include "Joystick.h"
#include "N5110.h"
#include "cuphead.h"


//Pin assignment:  (MOSI, MISO, SCK,  TCS,   DC,  RST)
Adafruit_ST7735 tft(PA_7, PA_6, PA_5, PB_6, PC_10, PA_3);

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

// Joystick pins   y     x
Joystick joystick1(PC_1, PC_0);  //attach and create joystick object
Joystick joystick2(PC_2, PC_3);

DigitalIn button1(PB_0);
DigitalIn button2(PA_8);


void boundary(int x, int y);

// Function Prototypes
void updateCharacterPosition(Joystick& joystick);
void updateShootingDirection(Joystick& joystick);


//set initial position of the points to (42,24) for testing purposes
float y_pos = 24;
float x_pos = 42;
float y_pos2 = 15;
float x_pos2 = 20;


int main() {

  //Nokia screen
    lcd.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.setContrast(0.6);      //set contrast to 55%
    lcd.setBrightness(0.6);     //set brightness to 50% (utilises the PWM)
    joystick1.init();
    joystick2.init();
    button1.mode(PullUp);



    while (true) {
 
        lcd.clear();
        lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);   //draws screen boarder
        lcd.drawRect(x_pos,y_pos,2,2,FILL_BLACK);   //draws point at position (x,y)
        lcd.drawCircle(x_pos2,y_pos2,3,FILL_BLACK);



        updateCharacterPosition(joystick1);
        updateShootingDirection(joystick2);

        boundary(x_pos, y_pos); //pass the new x,y position to function
        boundary(x_pos2, y_pos2); //pass the new x,y position to function
            
        lcd.refresh();
        ThisThread::sleep_for(30ms);

    }
}


void updateCharacterPosition(Joystick& joystick) {
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

void updateShootingDirection(Joystick& joystick) {
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


//check that the point remains on the screen
void boundary(int x, int y){
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