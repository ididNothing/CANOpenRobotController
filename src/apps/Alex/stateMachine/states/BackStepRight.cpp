#include "BackStepRight.h"

void BackStepRight::entry(void) {
    std::cout
        << "==================" << endl
        << " Back Stepping RIGHT" << endl
        << "==================" << endl;

    trajectoryGenerator->initialiseTrajectory(RobotMode::BKSTEP, Foot::Left, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::BackStepR);
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
}
void BackStepRight::during(void) {
    robot->moveThroughTraj();
}
void BackStepRight::exit(void) {
    DEBUG_OUT("EXITING Back step RIGHT")
}
