#include "ErrorState.h"

void ErrorState::entry(void) {
    std::cout << "==================" << endl
              << " ERROR STATE !!!!" << endl
              << "==================" << endl
              << "Reset -> R" << endl
              << "==================" << endl;

    robot->disableJoints();
    robot->setCurrentState(AlexState::Error);
}
void ErrorState::during(void) {
}
void ErrorState::exit(void) {
    DEBUG_OUT("EXITING ERROR STATE")
}
