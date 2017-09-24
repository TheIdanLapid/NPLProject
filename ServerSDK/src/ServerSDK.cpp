/*
 * ServerSDK.cpp
 *
 *  Created on: Sep 24, 2017
 *      Author: user
 */

#include "ServerSDK.h"

ServerSDK::ServerSDK() {
	acceptor = new Acceptor(this);
	dispacher = new Dispatcher(this);
}

void ServerSDK::printUsers(TCPSocket* peer) {
	dispacher->printLoggedUsers(peer);
}

ServerSDK::~ServerSDK() {
	// TODO Auto-generated destructor stub
}

