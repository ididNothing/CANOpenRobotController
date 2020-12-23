#include "BackStepLeft.h"

void BackStepLeft::entry(void)
{
    std::cout
        << "==================" << endl
        << " Back Stepping Left" << endl
        << "==================" << endl;
#ifdef VIRTUAL
    std::cout
        << "==================" << endl
        << " W ->> Complete trajectory" << endl
        << "==================" << endl;
#endif
    trajectoryGenerator->initialiseTrajectory(RobotMode::BKSTEP, robot->getJointStates());
    robot->startNewTraj();
    robot->setCurrentState(AlexState::BackStepL);
}
void BackStepLeft::during(void)
{
    robot->moveThroughTraj();
}
void BackStepLeft::exit(void)
{
    DEBUG_OUT("EXITING STEPPING LEFT")
}
