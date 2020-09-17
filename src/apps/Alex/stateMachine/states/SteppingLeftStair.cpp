#include "SteppingLeftStair.h"

void SteppingLeftStair::entry(void) {
    std::cout
        << "==================" << endl
        << " Stepping Left Stair" << endl
        << "==================" << endl;
    trajectoryGenerator->initialiseTrajectory(RobotMode::UPSTAIR, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::StepL);
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
}
void SteppingLeftStair::during(void) {
    robot->moveThroughTraj();
}
void SteppingLeftStair::exit(void) {
    DEBUG_OUT("EXITING STEPPING LEFT STAIR")
}
