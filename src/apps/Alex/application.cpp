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

// Create pointer to logger object
std::shared_ptr<spdlog::logger> mainLogger;

/******************************************************************************/
void app_programStart(void) {
    printf("app_Program Start \n");
    alexM.init();
    ((StateMachine)alexM).activate();

    // Create the logger object
    mainLogger = createLogger("parent", "application_log.csv");
    spdlog::set_default_logger(mainLogger);
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
    }

    // Add to the logger
    fileLoggerBinary(mainLogger);
}

//creating a logger at a designated fileLocation.
std::shared_ptr<spdlog::logger> createLogger(std::string logID, std::string fileLocation) {
    try {
        auto logger = spdlog::basic_logger_mt(logID, fileLocation);
        // setLoggerStyle(logger);
        logger->set_pattern("%v");
        return logger;
    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Failed to create log: " << ex.what() << std::endl;
    }
}

void fileLoggerBinary(std::shared_ptr<spdlog::logger> logger) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint32_t motorpos[4];
    uint16_t motorTor[4];

    // Want to change these to getPos() instead, need to check which file that function is in (I think its drive.cpp)

    // motorpos[0] = CO_OD_RAM.actualMotorPositions.motor1;
    // motorpos[1] = CO_OD_RAM.actualMotorPositions.motor2;
    // motorpos[2] = CO_OD_RAM.actualMotorPositions.motor3;
    // motorpos[3] = CO_OD_RAM.actualMotorPositions.motor4;

    motorpos[0] = CO_OD_RAM.actualMotorPositions.motor1;
    motorpos[1] = CO_OD_RAM.actualMotorPositions.motor2;
    motorpos[2] = CO_OD_RAM.actualMotorPositions.motor3;
    motorpos[3] = CO_OD_RAM.actualMotorPositions.motor4;

    motorTor[0] = CO_OD_RAM.statusWords.motor1;
    motorTor[1] = CO_OD_RAM.statusWords.motor2;
    motorTor[2] = CO_OD_RAM.statusWords.motor3;
    motorTor[3] = CO_OD_RAM.statusWords.motor4;

    // Create test array
    int testInts[4] = {1, 2, 3, 4};

    long long timesec = tv.tv_sec;
    long timeusec = tv.tv_usec;

    logger->info("{}", timesec);
    logger->info("{}", timeusec);

    for (int i = 0; i < 4; i++) {
        mainLogger->info("{}", motorpos[i]);
        mainLogger->info("{}", motorTor[i]);
        // mainLogger->info("{}", testInts[i]);
    }
}