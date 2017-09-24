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

void ServerSDK::handlePeer(TCPSocket* peer) {

}

int ServerSDK::openGameSession(User* user1, User* user2) {
	return 0;
}

DispatcherHandler::~DispatcherHandler() {
	// TODO Auto-generated destructor stub
}

AcceptorHandler::~AcceptorHandler() {
	// TODO Auto-generated destructor stub
}

ServerSDK::~ServerSDK() {
	// TODO Auto-generated destructor stub
}

