//menu.cpp
#include "menu.h"
#include "mbed.h"

Menu::Menu() : lcd(nullptr), joystick(nullptr), currentOption(0), state(MenuState::MAIN_MENU) {} 
//nullptr is a way to represent pointers


void Menu::init(N5110 &display, Joystick &stick) {
    lcd = &display;
    joystick = &stick;
}

void Menu::update(DigitalIn &buttonA) {
    //get the joystick direction
    Direction dir = joystick->get_direction();
    

    if (dir == N) {
        currentOption = (currentOption + maxOptions - 1) % maxOptions;
    } else if (dir == S) {
        currentOption = (currentOption + 1) % maxOptions;
    }
    //updates the navigation depending on joystick direction

    //check if the button A is pressed
    if (buttonA.read() == 1) {
        if (state == MenuState::MAIN_MENU) {
            if (currentOption == 0) {
                state = MenuState::HOW_TO_PLAY;
            } else if (currentOption == 1) {
                state = MenuState::START_GAME;
                if (gameManager) {
                    gameManager->startGame();  //call the startGame method of GameManager
                }
            } else if (currentOption == 3) {
                state = MenuState::CREDITS;
            }
        } else if (state == MenuState::HOW_TO_PLAY || state == MenuState::CREDITS) {
            backToMainMenu();
        }
    }
}

void Menu::draw() {
    lcd->clear();
    //using lcd->clear(); instead of lcd.clear(); because the object was initiated as a pointer,
    //so it's referring the the screen

    switch (state) {
        case MenuState::MAIN_MENU: {
            //draw main menu
            lcd->printString("CAPTURED!", 20, 0); //title
            const char *options[maxOptions] = {"HOW TO PLAY", "START GAME", "OPTIONS", "CREDITS"}; //menu options
            for (int i = 0; i < maxOptions; ++i) {
                int y_pos = i + 2; //rows start from 2 and go to 5
                lcd->printString(options[i], 5, y_pos); //to print the menu options
                if (i == currentOption) {
                    lcd->drawRect(0, y_pos * 8, 84, 8, FILL_TRANSPARENT); //used to highlight the option
                }
            }
            break;
        }
        case MenuState::HOW_TO_PLAY:
            drawHowToPlay();
            break;
        case MenuState::CREDITS:
            drawCredits();
            break;
    }
    
    lcd->refresh();
}

void Menu::drawHowToPlay() {
    lcd->clear();
    lcd->printString("Be the last", 5, 0);
    lcd->printString("Alive! There", 5, 1);
    lcd->printString("is a guide", 5, 2);
    lcd->printString("before each", 5, 3);
    lcd->printString("game.", 5, 4);
    lcd->printString("Exit", 5, 5); 
    lcd->drawRect(0, 5 * 8, 33, 8, FILL_TRANSPARENT); //rectangle around "Exit" to indicate the player can press to exit
    lcd->refresh();
}

void Menu::drawCredits() {
    lcd->clear();
    lcd->printString("Credits:", 5, 0);
    lcd->printString("201582636", 5, 1);
    lcd->printString("Ali Maarafi", 5, 2);
    lcd->printString("2645 Project", 5, 3);
    lcd->printString("Exit", 5, 5);
    lcd->drawRect(0, 5 * 8, 33, 8, FILL_TRANSPARENT);
    lcd->refresh();
}

void Menu::backToMainMenu() {
    state = MenuState::MAIN_MENU;
}


bool Menu::isActive() const {
    return state == MenuState::MAIN_MENU || state == MenuState::HOW_TO_PLAY || state == MenuState::CREDITS;
}


//function to get the current menu option
int Menu::getOption() const {
    return currentOption;
}