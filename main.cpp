// main.cpp
#include "mbed.h"
#include "Joystick.h"
#include "N5110.h"  
#include "Utils.h"
#include "menu.h" //menu header for the main menu

N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
//joystick joystick2();
//joystick joystick3();
//joystick joystick4();


DigitalIn buttonA(PC_12);

//digitalIn buttonB();
//digitalIn buttonC();
//digitalIn buttonD();


Menu menu;
GameManager gameManager(lcd, joystick, buttonA);  // Include the button in the constructor call

int main() {
    // Initialization
    lcd.init(LPH7366_1);        //initialise for LPH7366-1 LCD
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.2);     //set brightness to 50%
    joystick.init();

    menu.init(lcd, joystick); //initialize the menu with the LCD and joystick objects
    menu.setGameManager(&gameManager);  //link the menu with GameManager

    while (1) {
        menu.update(buttonA);
        menu.draw();

        if (!menu.isActive()) { //when the menu is no longer active, game manager starts
            gameManager.update();
            gameManager.render();
        }
        ThisThread::sleep_for(100ms);
    }


}
