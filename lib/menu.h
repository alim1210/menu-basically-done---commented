//menu.h
#ifndef MENU_H
#define MENU_H

#include "N5110.h"
#include "Joystick.h"
#include "GameManager.h" 

enum class MenuState { //contains the different screens to be shown
    MAIN_MENU,
    HOW_TO_PLAY,
    CREDITS,
    START_GAME
};



class Menu {
public:
    Menu(); // Constructor
    void init(N5110 &lcd, Joystick &joystick); //initialize with LCD and joystick
    void update(DigitalIn &buttonA); //update the menu selection with the joystick and buttonA
    void draw(); //draw the menu
    int getOption() const; //get the currently selected option
    void drawHowToPlay(); //draw the tutorial screen
    void backToMainMenu(); //returning to the main menu
    void drawCredits(); //draw the credits screen
    void setGameManager(GameManager* gm) { gameManager = gm; }
    
    bool isActive() const;  // Declare the isActive method

private:
    N5110 *lcd;
    Joystick *joystick;
    int currentOption;
    static const int maxOptions = 4; //total number of menu options
    MenuState state; //to track the current menu state
    GameManager* gameManager;  // Pointer to the game manager
};

#endif 