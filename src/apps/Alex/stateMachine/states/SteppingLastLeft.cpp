#include "SteppingLastLeft.h"

void SteppingLastLeft::entry(void) {
    std::cout
        << "==================" << endl
        << " Stepping Last Left" << endl
        << "==================" << endl;
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
    trajectoryGenerator->initialiseTrajectory(RobotMode::FTTG, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::StepLastL);
}
void SteppingLastLeft::during(void) {
    robot->moveThroughTraj();
}
void SteppingLastLeft::exit(void) {
    DEBUG_OUT("EXITING STEPPING LAST LEFT")
}
