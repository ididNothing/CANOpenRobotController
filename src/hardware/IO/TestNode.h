/*
 * 
 * test node to test out CAN operations
 * 
 * */
 
 
 #ifndef TESTNODE_H 
 #define TESTNODE_H
 
 #include <CANopen.h>
 #include <CO_command.h>
 
 #include "RPDO.h"
 #include "TPDO.h"
 #include "logging.h"
 
/*
	enum OD_Entry_t {
    STATUS_WORD = 0,
    ACTUAL_POS = 1,
    ACTUAL_VEL = 2,
    ACTUAL_TOR = 3,
    ERROR_WORD = 4,
    CONTROL_WORD = 10,
    TARGET_POS = 11,
    TARGET_VEL = 12,
    TARGET_TOR = 13
};
	
    std::map<OD_Entry_t, void *> OD_MappedObjectAddresses = {
        {STATUS_WORD, (void *)&statusWord},
        {ERROR_WORD, (void *)&errorWord},
        {ACTUAL_POS, (void *)&actualPos},
        {ACTUAL_VEL, (void *)&actualVel},
        {ACTUAL_TOR, (void *)&actualTor},
        {CONTROL_WORD, (void *)&controlWord},
        {TARGET_POS, (void *)&targetPos},
        {TARGET_VEL, (void *)&targetVel},
        {TARGET_TOR, (void *)&targetTor}};
	*/
	
	
	
class TestNode{
	private:
	
	int commandID; //The COB-ID used to send messages to this device
	
	TPDO *tpdo1;
	RPDO *rpdo1;
	
	
	
	 
	
	public: 
	INTEGER32 rawData[2] = {0};
	TestNode(int commandId);  //constructor
	
	bool configureMasterPDOs(); //setup the receiving PDOs
	
	INTEGER32 GetRawData();

	
	
};
#endif
