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

time_t timer;

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

    // Create csv file (not using spdlog)
    // std::ofstream myLog("my_app_log.csv");

    // Record start time
    // time_t timer;
    // time_t start_tm = time(&timer);
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

    // My logger test
    std::ofstream myLog("my_app_log.csv", std::ios::app);

    uint32_t motorpos[4];
    uint16_t motorTor[4];

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
#endif

    int testInts[4] = {1, 2, 3, 4};

    // Time
    time_t curr_tm = time(NULL);
    // double curr_tm = difftime(time(&timer), start_tm);
    myLog << asctime(localtime(&curr_tm)) << ",";  // Need to remove \n

    myLog << motorpos[0] << ",";
    myLog << motorpos[1] << ",";
    myLog << motorpos[2] << ",";
    myLog << motorpos[3] << "\n";

    myLog.close();
}

//creating a logger at a designated fileLocation.
std::shared_ptr<spdlog::logger> createLogger(std::string logID, std::string fileLocation) {
    try {
        auto logger = spdlog::basic_logger_mt(logID, fileLocation);
        // setLoggerStyle(logger);
        // logger->set_pattern("%v");
        logger->set_pattern("%H:%M:%S, %v, %v, %v, %v");
        return logger;
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Failed to create log: " << ex.what() << std::endl;
    }
}

void fileLoggerBinary(std::shared_ptr<spdlog::logger> logger) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint32_t motorpos[4];
    uint16_t motorTor[4];

    // motorpos[0] = CO_OD_RAM.actualMotorPositions.motor1;
    // motorpos[1] = CO_OD_RAM.actualMotorPositions.motor2;
    // motorpos[2] = CO_OD_RAM.actualMotorPositions.motor3;
    // motorpos[3] = CO_OD_RAM.actualMotorPositions.motor4;

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
#endif

    motorTor[0] = CO_OD_RAM.statusWords.motor1;
    motorTor[1] = CO_OD_RAM.statusWords.motor2;
    motorTor[2] = CO_OD_RAM.statusWords.motor3;
    motorTor[3] = CO_OD_RAM.statusWords.motor4;

    // Create test array
    int testInts[4] = {1, 2, 3, 4};

    long long timesec = tv.tv_sec;
    long timeusec = tv.tv_usec;

    // logger->info("{}", timesec, timeusec, motorpos[0], motorpos[1], motorpos[2], motorpos[3]);
    logger->info("{}", timesec, timeusec, testInts[0], testInts[1], testInts[2], testInts[3]);
    logger->info("{}", testInts[2]);

    // logger->info("{}", timesec);
    // logger->info("{}", timeusec);

    // for (int i = 0; i < 4; i++) {
    //     mainLogger->info("{}", motorpos[i]);
    //     mainLogger->info("{}", motorTor[i]);
    //     // mainLogger->info("{}", testInts[i]);
    // }
}