/*
 * TCPMSNServerTest.h
 *
 *  Created on: Jul 9, 2017
 *      Author: user
 */

#ifndef TCPMSNSERVERTEST_H_
#define TCPMSNSERVERTEST_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include "MThread.h"
#include "TCPMSNClient.h"
#include "TCPMSNServer.h"
#include "CLIHandler.h"

using namespace std;
namespace networking {

class TCPMSNServerTest : MThread{
	TCPMSNServer* server;
//	CLIHandler handler1;
//	CLIHandler handler2;
//	TCPMSNClient client1;
//	TCPMSNClient client2;
public:
	TCPMSNServerTest();
	bool testTCPMSNServer();
	void run();
	virtual ~TCPMSNServerTest();
};

} /* namespace networking */

#endif /* TCPMSNSERVERTEST_H_ */
