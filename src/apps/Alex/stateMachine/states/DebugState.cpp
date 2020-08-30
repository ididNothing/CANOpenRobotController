////////// STATE ////////////////////
//-------  Debug ------------/////
////////////////////////////////////
#include "DebugState.h"

void DebugState::entry(void) {
    std::cout << "Debug State entered" << std::endl
              << "=======================" << std::endl
              << " + ->> Increase input angle" << std::endl
              << " - ->> Decrease input angle" << std::endl
              << " return ->> Send input angle" << std::endl
              << "=======================" << std::endl
              << std::endl;
    std::cout << "========================" << endl
              << " Press S to leave debug state" << endl
              << "========================" << endl;

    robot->setCurrentState(AlexState::Debug);

    // entry flag must be set to true by a green button release
    robot->setResetFlag(false);
}

void DebugState::during(void) {
    if (robot->keyboard.getPlus()) {
        angle = angle + INCREMENT;
        std::cout << "angle is " << angle << std::endl;
    }
    if (robot->keyboard.getMinus()) {
        angle = angle - INCREMENT;
        std::cout << "angle is " << angle << std::endl;
    }
    if (robot->keyboard.getEnter()) {
        std::cout << " I HAVE HIT ENTER" << std::endl;
    }
    updateCrutch();
    updateFlag();
}

void DebugState::exit(void) {
    std::cout
        << "Debug State Exited" << endl;
}
