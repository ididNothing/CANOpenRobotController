#include "InitialSitting.h"

void InitialSitting::entry(void) {
    DEBUG_OUT("PRESS TRIGGER TO SIT DOWN")
    trajectoryGenerator->initialiseTrajectory(RobotMode::INITIAL, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::InitSitting);
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
}
void InitialSitting::during(void) {
    // w/o crutch Go button
    //robot->pb.updateGO(true);
    robot->moveThroughTraj();
}
void InitialSitting::exit(void) {
    // w/o crutch Go button
    //robot->pb.updateGO(false);
    DEBUG_OUT("Initial SITTING DOWN POS:")
    robot->printStatus();
    std::cout
        << "Initial Sitting State Exited " << endl;
}
