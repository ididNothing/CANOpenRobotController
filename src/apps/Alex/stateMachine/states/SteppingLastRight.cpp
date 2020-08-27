
#include "SteppingLastRight.h"

void SteppingLastRight::entry(void) {
    std::cout
        << "==================" << endl
        << " Stepping Last RIGHT" << endl
        << "==================" << endl;
    trajectoryGenerator->initialiseTrajectory(RobotMode::FTTG, Foot::Left, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::StepLastR);
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
}
void SteppingLastRight::during(void) {
    robot->moveThroughTraj();
}
void SteppingLastRight::exit(void) {
    DEBUG_OUT("EXITING STEPPING LAST RIGHT")
}
