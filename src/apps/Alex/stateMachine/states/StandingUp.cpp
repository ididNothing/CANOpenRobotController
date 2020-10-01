#include "StandingUp.h"

// Negative bending control machine
void StandingUp::entry(void) {
    std::cout << "Standing Up State Entered" << endl
              << "===================" << endl
              << " TRIGGER ->> STAND UP" << endl
              << "===================" << endl;
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
    trajectoryGenerator->initialiseTrajectory(RobotMode::STNDUP, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::StandingUp);
}

void StandingUp::during(void) {
    // update go button do using keyboard d input.-> same as setting nm
    //robot->pb.updateGO(true);
    robot->moveThroughTraj();
}
void StandingUp::exit(void) {
    //robot->pb.updateGO(false);
    robot->printStatus();
    std::cout
        << "Standing up motion State Exited"
        << endl;
}