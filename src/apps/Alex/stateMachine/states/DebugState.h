/**
 * /file DebugState.h
 * /author Jordan Watkins
 * /version 0.1
 * /date 2020-08-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include "ExoTestState.h"

/**
 * @brief State for the ExoTestMachine (implementing ExoTestState) - representing a simulated change in drive positions when the exo is not connected.
 * This is to be used to test error handling and other debugging processes.
 * 
 * State machine can only enter this state with the keyboard input and when the VIRTUAL flag is defined (see DebugMacro.h)
 */
class DebugState : public ExoTestState {
   public:
    double angle = 0;

    void entry(void);
    void during(void);
    void exit(void);
    Standing(StateMachine *m, AlexRobot *exo, AlexTrajectoryGenerator *tg, const char *name = NULL) : ExoTestState(m, exo, tg, name){};
};

#endif