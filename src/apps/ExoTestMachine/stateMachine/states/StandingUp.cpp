#include "StandingUp.h"

// Negative bending control machine
void StandingUp::entry(void) {
    spdlog::info("Standing Up State Entered");
    std::cout << "===================" << std::endl
              << " GREEN -> STAND UP" << std::endl
              << "===================" << std::endl;
    trajectoryGenerator->initialiseTrajectory(STAND, 5, robot->getPosition());
    currTrajProgress = 0;
    clock_gettime(CLOCK_MONOTONIC, &prevTime);
}

void StandingUp::during(void) {
    timespec currTime;
    clock_gettime(CLOCK_MONOTONIC, &currTime);

    double elapsedSec = currTime.tv_sec - prevTime.tv_sec + (currTime.tv_nsec - prevTime.tv_nsec) / 1e9;
    prevTime = currTime;

    /**
     *  /todo - Check if the GO button on the robot is pressed
     *
     */
    if (robot->keyboard->getA() ) {
        currTrajProgress += elapsedSec;
        Eigen::VectorXd sp = trajectoryGenerator->getSetPoint(currTrajProgress);
        Eigen::VectorXd cp = robot->getPosition();
        spdlog::debug("Elapsed Time: {} {} {} {} ", sp[0], cp[0], sp[1], cp[1]);

        robot->setPosition(trajectoryGenerator->getSetPoint(currTrajProgress));
    }
}
void StandingUp::exit(void) {
    spdlog::info("Standing Up State Exited");
}
