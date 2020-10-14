/*
 * Application interface for Alex Exoskeleton Software
 *
 * @file        application.c
 * @author      William Campbell
 *

 */
#include "application.h"

/*For master-> node SDO message sending*/
#define CO_COMMAND_SDO_BUFFER_SIZE 100000
#define STRING_BUFFER_SIZE (CO_COMMAND_SDO_BUFFER_SIZE * 4 + 100)
char buf[STRING_BUFFER_SIZE];
char ret[STRING_BUFFER_SIZE];
AlexMachine alexM;
/******************************************************************************/
void app_programStart(void) {
    printf("app_Program Start \n");
    alexM.init();
    ((StateMachine)alexM).activate();

    // My logger test
    // remove("app_log_heidelberg.csv");
    std::ofstream myLog("app_log_heidelberg.csv", std::ios::app);
    myLog << "Current state, Motor0 angle, Motor1 angle, Motor2 angle, Motor3 angle, Motor0 velocity, Motor1 velocity, Motor2 velocity, Motor3 velocity, Motor0 torque, Motor1 torque, Motor2 torque, Motor3 torque, System time \n";
    myLog.close();
}
/******************************************************************************/
void app_communicationReset(void) {
}
/******************************************************************************/
void app_programEnd(void) {
    printf("app_programEnd \n");
}
/******************************************************************************/
void app_programAsync(uint16_t timer1msDiffy) {
}

void app_programControlLoop(void) {
    if (alexM.running) {
        alexM.hwStateUpdate();
        alexM.update();

        app_fileLogger();
    }
}

void app_fileLogger(void) {
    // My logger test
    std::ofstream myLog("app_log_heidelberg.csv", std::ios::app);

    uint32_t motorpos[4];
    uint32_t motorvel[4];
    uint32_t motorTor[4];

#ifdef VIRTUAL
    motorpos[0] = CO_OD_RAM.targetMotorPositions.motor1;
    motorpos[1] = CO_OD_RAM.targetMotorPositions.motor2;
    motorpos[2] = CO_OD_RAM.targetMotorPositions.motor3;
    motorpos[3] = CO_OD_RAM.targetMotorPositions.motor4;
#endif

#ifndef VIRTUAL
    motorpos[0] = CO_OD_RAM.actualMotorPositions.motor1;
    motorpos[1] = CO_OD_RAM.actualMotorPositions.motor2;
    motorpos[2] = CO_OD_RAM.actualMotorPositions.motor3;
    motorpos[3] = CO_OD_RAM.actualMotorPositions.motor4;

    motorvel[0] = CO_OD_RAM.actualMotorVelocities.motor1;
    motorvel[1] = CO_OD_RAM.actualMotorVelocities.motor2;
    motorvel[2] = CO_OD_RAM.actualMotorVelocities.motor3;
    motorvel[3] = CO_OD_RAM.actualMotorVelocities.motor4;

    motorTor[0] = CO_OD_RAM.actualMotorTorques.motor1;
    motorTor[1] = CO_OD_RAM.actualMotorTorques.motor2;
    motorTor[2] = CO_OD_RAM.actualMotorTorques.motor3;
    motorTor[3] = CO_OD_RAM.actualMotorTorques.motor4;
#endif

    // Convert joint angle to degrees
    motorpos[0] = alexM.toRobotDriveAngle(motorpos[0]);
    motorpos[1] = alexM.toRobotDriveAngle1(motorpos[1]);
    motorpos[2] = alexM.toRobotDriveAngle(motorpos[2]);
    motorpos[3] = alexM.toRobotDriveAngle1(motorpos[3]);

    // Time
    time_t curr_tm = time(NULL);
    // double curr_tm = difftime(time(&timer), start_tm);

    // Log current state
    myLog << CO_OD_RAM.currentState << ",";
    // Log motor positions
    myLog << motorpos[0] << ",";
    myLog << motorpos[1] << ",";
    myLog << motorpos[2] << ",";
    myLog << motorpos[3] << ",";

#ifndef VIRTUAL
    // Log motor torques
    myLog << motorvel[0] << ",";
    myLog << motorvel[1] << ",";
    myLog << motorvel[2] << ",";
    myLog << motorvel[3] << ",";

    // Log motor torques
    myLog << motorTor[0] << ",";
    myLog << motorTor[1] << ",";
    myLog << motorTor[2] << ",";
    myLog << motorTor[3] << ",";
#endif

    // Log current system time (different to actual time)
    myLog << asctime(localtime(&curr_tm));  // Need to remove \n

    myLog.close();
}