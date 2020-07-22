#include "Buttons.h"
#include <iostream>
#include <fstream>

Buttons::Buttons() {
    std::cout << "Button object created" << std::endl;
    errorButton = false;
};
Buttons::~Buttons() {
    // Check if destructor is necessary
};
void Buttons::updateInput() {
    errorButton = checkButton(errorButtonPath);
    std::cout << "Error button value: " << errorButton << std::endl;
};
bool Buttons::checkButton(std::string path) {
    char value;
    std::ifstream stream(path);
    stream >> value;
    stream.close();

    // Button is pressed if value is 0
    if (value == '1') {
        return true;
    } else {
        return false;
    }
};
bool Buttons::getErrorButton() {
    return errorButton;
};