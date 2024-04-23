#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"
#include "GameState.h"
#include "IntroCutscene.h" 

class GameManager {
public:
    GameManager(N5110& display, Joystick& joystick, DigitalIn& button);
    void startGame();
    void update();
    void render();
    void switchState(GameState newState);

private:
    N5110& display;
    Joystick& joystick;
    DigitalIn& button;
    GameState currentState;
    IntroCutscene introCutscene;  
};

#endif 
