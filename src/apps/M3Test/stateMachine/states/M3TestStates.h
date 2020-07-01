/**
 * /file M3TestState.h
 * \author Vincent Crocher
 * \version 0.1
 * \date 2020-06-16
 * \copyright Copyright (c) 2020
 *
 *
 */

#ifndef M3TESTSTATE_H_DEF
#define M3TESTSTATE_H_DEF

#include <time.h>

#include <iostream>

#include "DebugMacro.h"
#include "RobotM3.h"
#include "State.h"

using namespace std;

/**
 * \brief Conversion from a timespec structure to seconds (double)
 *
 */
double timeval_to_sec(struct timespec *ts);

/**
 * \brief Generic state type for used with M3TestMachine, providing running time and iterations number.
 *
 */
class M3TimedState : public State {
   protected:
    /**
    *  \todo Might be good to make these Const
    *
    */
    RobotM3 *robot;                               /*<!Pointer to state machines robot object*/

    M3TimedState(StateMachine *m, RobotM3 *M3, const char *name = NULL): State(m, name), robot(M3){};
   private:
    void entry(void) final {
        std::cout
        << "==================================" << std::endl
        << " STARTING  " << getName() << std::endl
        << "==================================" << std::endl
        << std::endl;

        //Timing
        clock_gettime(CLOCK_REALTIME, &initTime);
        lastTime = timeval_to_sec(&initTime);

        iterations=0;

        //Actual state entry
        entryCode();
    };
    void during(void) final {
        //Compute some basic time values
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);

        double now = timeval_to_sec(&ts);
        elapsedTime = (now-timeval_to_sec(&initTime));
        dt = now - lastTime;
        lastTime = now;

        iterations++;

        //Actual state during
        duringCode();
    };
    void exit(void) final {
        exitCode();
        std::cout
        << "==================================" << std::endl
        << "EXIT "<< getName() << std::endl
        << "==================================" << std::endl
        << std::endl;
    };

   public:
    virtual void entryCode(){};
    virtual void duringCode(){};
    virtual void exitCode(){};


   protected:
    struct timespec initTime;   /*<! Time of state init */
    double lastTime;            /*<! Time of last during() call (in seconds since state init())*/
    double elapsedTime;         /*<! Time since state init() in seconds*/
    double dt;                  /*<! Time between last two during() calls (in seconds)*/
    long int iterations;
};


class M3TestState : public M3TimedState {

   public:
    M3TestState(StateMachine *m, RobotM3 *M3, const char *name = "M3 Test State"):M3TimedState(m, M3, name){};

    void entryCode(void);
    void duringCode(void);
    void exitCode(void);
};



/**
 * \brief Position calibration of M3. Go to the bottom left stops of robot at constant torque for absolute position calibration.
 *
 */
class M3CalibState : public M3TimedState {

   public:
    M3CalibState(StateMachine *m, RobotM3 *M3, const char *name = "M3 Calib State"):M3TimedState(m, M3, name){};

    void entryCode(void);
    void duringCode(void);
    void exitCode(void);

    bool isCalibDone() {return calibDone;}

   private:
     Eigen::Vector3d stop_reached_time;
     bool at_stop[3];
     bool calibDone=false;

};


/**
 * \brief Provide end-effector mass compensation on M3. Mass is controllable through keyboard inputs.
 *
 */
class M3MassCompensation : public M3TimedState {

   public:
    M3MassCompensation(StateMachine *m, RobotM3 *M3, const char *name = "M3 Mass Compensation"):M3TimedState(m, M3, name){};

    void entryCode(void);
    void duringCode(void);
    void exitCode(void);

   private:
     double mass = 0;

};


/**
 * \brief End-effector velocity control through keyboard input.
 *
 */
class M3EndEffDemo : public M3TimedState {

   public:
    M3EndEffDemo(StateMachine *m, RobotM3 *M3, const char *name = "M3 Velocity Control Demo"):M3TimedState(m, M3, name){};

    void entryCode(void);
    void duringCode(void);
    void exitCode(void);

   private:
    double vel_input = 0.1; //in m.s-1
};


#endif
