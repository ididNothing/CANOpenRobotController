
#include "TestNode.h"

TestNode::TestNode(int _commandID){
	commandID = _commandID;
}


bool TestNode::configureMasterPDOs(){
	spdlog::debug("Test Node configure PDO");
	
	UNSIGNED16 dataSize[2] = {4, 4};
    void *dataEntry[2] = {(void *)&rawData[0],
                           (void *)&rawData[1],};

    rpdo1 = new RPDO(0X210, 0xFF, dataEntry, dataSize, 2); //COB-ID, transmission type, dataEntry, dataSize number of mapped objects

    return true;
}


  INTEGER32 TestNode::GetRawData(){
	  //TODO do counter and print out
	  spdlog::debug("Raw data: {}, {}" , (double) rawData[0], (double)rawData[1]);
	  return 0;
  }
	 
	
	


