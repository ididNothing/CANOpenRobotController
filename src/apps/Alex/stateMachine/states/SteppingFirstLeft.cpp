#include "SteppingFirstLeft.h"

void SteppingFirstLeft::entry(void) {
    std::cout
        << "==================" << endl
        << " Stepping 1st Left" << endl
        << "==================" << endl;
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
    /*MUST HAVE A CHECK THAT Its the correct motion here as well - or throw an error and don't move!*/
    trajectoryGenerator->initialiseTrajectory(robot->getCurrentMotion(), robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::StepFirstL);
}
void SteppingFirstLeft::during(void) {
    robot->moveThroughTraj();
}
void SteppingFirstLeft::exit(void) {
    DEBUG_OUT("EXITING STEPPING FIRST LEFT")
}
