#include "GameManager.h"

GameManager::GameManager(N5110& display, Joystick& joystick, DigitalIn& button)
    : display(display), joystick(joystick), button(button),
      introCutscene(display, button), //initializing introCutscene with display and button
      currentState(GameState::MENU) {}

void GameManager::startGame() {
    switchState(GameState::INTRO); //once startGame is triggered, it goes straight into the intro cutscene
}

void GameManager::update() {
    if (currentState == GameState::INTRO && !introCutscene.isComplete()) {
        introCutscene.nextScreen(); //once the intro cutscene is complete, it goes into the next game
    } else if (introCutscene.isComplete() && currentState == GameState::INTRO) {
        switchState(GameState::MINI_GAME_1);
    }
    //rest to be added later
}

void GameManager::render() {
    if (currentState == GameState::INTRO) {
        introCutscene.renderCurrentScreen();
    }
}

void GameManager::switchState(GameState newState) {
    currentState = newState;
    //more initialization logic for later states
}
