#include "BackStepRight.h"

void BackStepRight::entry(void) {
    std::cout
        << "==================" << endl
        << " Back Stepping RIGHT" << endl
        << "==================" << endl;
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif

    trajectoryGenerator->initialiseTrajectory(RobotMode::BKSTEP, Foot::Left, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::BackStepR);
}
void BackStepRight::during(void) {
    robot->moveThroughTraj();
}
void BackStepRight::exit(void) {
    DEBUG_OUT("EXITING Back step RIGHT")
}
