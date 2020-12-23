////////// STATE ////////////////////
//-------  Sitting Down ------------/////
////////////////////////////////////
#include "SittingDwn.h"
void SittingDwn::entry(void) {
    std::cout << "Sitting Down State Entered " << endl
              << "===================" << endl
              << " TRIGGER ->> SIT DOWN " << endl
              << "===================" << endl;
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
    trajectoryGenerator->initialiseTrajectory(RobotMode::SITDWN, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::SittingDown);
}
void SittingDwn::during(void) {
    // w/o crutch Go button
    //robot->pb.updateGO(true);
    robot->moveThroughTraj();
}
void SittingDwn::exit(void) {
    // w/o crutch Go button
    //robot->pb.updateGO(false);
    DEBUG_OUT("EXIT SITTING DOWN POS:")
    robot->printStatus();
    std::cout
        << "Sitting Down State Exited " << endl;
}