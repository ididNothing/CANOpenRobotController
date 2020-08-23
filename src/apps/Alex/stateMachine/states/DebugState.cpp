////////// STATE ////////////////////
//-------  Standing ------------/////
////////////////////////////////////
#include "Standing.h"

void Standing::entry(void) {
    std::cout << "Debug State entered" << std::endl
              << "=======================" << std::endl
              << " ^ ->> Increase input angle" << std::endl
              << " v ->> Decrease input angle" << std::endl
              << " return ->> Send input angle" << std::endl
              << "=======================" << std::endl
              << std::endl;
    robot->setCurrentState(AlexState::Debug);

    // entry flag must be set to true by a green button release
    robot->setResetFlag(false);
}

void Standing::during(void) {
    updateCrutch();
    updateFlag();
}

void Standing::exit(void) {
    std::cout
        << "Standing State Exited" << endl;
}
