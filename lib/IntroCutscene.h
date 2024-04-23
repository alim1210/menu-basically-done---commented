#ifndef INTRO_CUTSCENE_H
#define INTRO_CUTSCENE_H

#include "N5110.h"
#include "DigitalIn.h"

class IntroCutscene {
public:
    IntroCutscene(N5110& display, DigitalIn& button);
    void nextScreen();
    void renderCurrentScreen();
    bool isComplete() const;

private:
    N5110& display;
    DigitalIn& buttonA;
    int currentScreenIndex;
    bool complete;
};

#endif 