#include "IntroCutscene.h"
#include "mbed.h"

IntroCutscene::IntroCutscene(N5110& display, DigitalIn& button)
    : display(display), buttonA(button), currentScreenIndex(0), complete(false) {}

void IntroCutscene::nextScreen() {
    static bool buttonPreviouslyPressed = false;  // To detect changes in button state
    static Timer debounceTimer;  // Timer to control screen change rate

    bool buttonPressed = (buttonA.read() == 1);

    // Start the debounce timer after the button is first pressed
    if (buttonPressed && !buttonPreviouslyPressed) {
        debounceTimer.start();
        buttonPreviouslyPressed = true;
    }

    // Check if the button was pressed and debounce time has elapsed
    if (buttonPressed && buttonPreviouslyPressed && debounceTimer.read_ms() > 150) {
        debounceTimer.stop();
        debounceTimer.reset();

        currentScreenIndex++;  // Increment screen index
        if (currentScreenIndex > 3) {
            currentScreenIndex = 3;  // Loop back or set to last screen
            complete = true;
        }

        buttonPreviouslyPressed = false;  // Reset button press state
    }

    // If button is released, reset everything
    if (!buttonPressed) {
        debounceTimer.stop();
        debounceTimer.reset();
        buttonPreviouslyPressed = false;
    }
}

void IntroCutscene::renderCurrentScreen() {
    display.clear();
    switch (currentScreenIndex) {
        case 0:
            // First screen content, formatted as specified
            display.printString("This is", 5, 0);
            display.printString("a test,", 5, 1);
            display.printString("screen 1", 5, 2);
            break;
        case 1:
            // Second screen content, formatted as specified
            display.printString("this should", 5, 1);
            display.printString("be the", 5, 2);
            display.printString("2nd screen", 5, 3);
            break;
        case 2:
            // Third screen placeholder
            display.printString("Placeholder", 5, 0);
            display.printString("for third", 5, 1);
            display.printString("screen", 5, 2);
            break;
        case 3:
            // Fourth screen placeholder
            display.printString("Final placeholder", 5, 1);
            display.printString("before game starts", 5, 2);
            display.printString("Start Game", 5, 5);
            display.drawRect(0, 5 * 8, 84, 8, FILL_TRANSPARENT); // Highlight the "Start Game"
            break;
    }
    display.refresh();
}


bool IntroCutscene::isComplete() const {
    return complete;
}

