#include "mbed.h"


#include "Adafruit_ST7735.h" // Include the Adafruit ST7735 library
//Pin assignment:  (MOSI, MISO, SCK,  TCS,   DC,  RST)
Adafruit_ST7735 tft(PA_7, PA_6, PA_5, PB_6, PC_10, PA_3);

#include "Joystick.h" 
//                  y     x
Joystick joystick(PC_1, PC_0);  //attach and create joystick object
DigitalIn button(PB_0);


#include "N5110.h"
//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);


//set initial position of point to (42,24)
float y_pos = 24;
float x_pos = 42;
float y_pos2 = 15;
float x_pos2 = 20;

void boundary(int x, int y);


int main() {
    // tft display
    tft.initR(INITR_GREENTAB2); // Initialize with screen type, adjust if needed
    tft.fillScreen(ST7735_BLACK); // Clear the display with black

    //joystick
    joystick.init();
    button.mode(PullUp);

    //Nokia screen
    lcd.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)
    

    
    while (true) {

        lcd.clear();
        lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);   //draws screen boarder
        lcd.drawRect(x_pos,y_pos,2,2,FILL_BLACK);   //draws point at position (x,y)
        lcd.drawCircle(x_pos2,y_pos2,3,FILL_BLACK);

  
    if (button.read() == 0){
        if(joystick.get_direction() == N){
            y_pos--;
        }else if(joystick.get_direction() == S){
            y_pos++;
        }else if(joystick.get_direction() == E){
            x_pos++;
        }else if(joystick.get_direction() == W){
            x_pos--;
        }else if(joystick.get_direction() == NE){
            y_pos--;
            x_pos++;
        }else if(joystick.get_direction() == NW){
            y_pos--;
            x_pos--;
        }else if(joystick.get_direction() == SE){
            y_pos++;
            x_pos++;
        }else if(joystick.get_direction() == SW){
            y_pos++;
            x_pos--;
        } else {
        }

    }else if (button.read() == 1){
        if(joystick.get_direction() == N){
        y_pos2--;
        }else if(joystick.get_direction() == S){
            y_pos2++;
        }else if(joystick.get_direction() == E){
            x_pos2++;;
        }else if(joystick.get_direction() == W){
            x_pos2--;
        }else if(joystick.get_direction() == NE){
            y_pos2--;
            x_pos2++;;
        }else if(joystick.get_direction() == NW){
            y_pos2--;
            x_pos2--;
        }else if(joystick.get_direction() == SE){
            y_pos2++;
            x_pos2++;
        }else if(joystick.get_direction() == SW){
            y_pos2++;
            x_pos2--;
        } else {
     }
 }



 boundary(x_pos, y_pos); //pass the new x,y position to function
 boundary(x_pos2, y_pos2); //pass the new x,y position to function
     
 lcd.refresh();
 ThisThread::sleep_for(30ms);

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