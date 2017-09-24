/*
 * CLIHandler.h
 *
 *  Created on: Jun 19, 2017
 *      Author: user
 */

#ifndef CLIHANDLER_H_
#define CLIHANDLER_H_
#include "TCPMSNClient.h"
#include <iostream>
#include <unistd.h>
using namespace std;
namespace networking {

class CLIHandler : public TCPMSNClientHandler {
public:
	CLIHandler();
	string lastRcvdMsg;
	virtual void onMessageRecieved(char* message);
	virtual void onOpenSession(string ip, int port);
	virtual void onClosedSession();
	virtual ~CLIHandler();
};

} /* namespace networking */

#endif /* CLIHANDLER_H_ */
