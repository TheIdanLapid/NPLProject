/*
 * ServerSDK.h
 *
 *  Created on: Sep 24, 2017
 *      Author: user
 */

#ifndef SERVERSDK_H_
#define SERVERSDK_H_
#include "FileManager.h"
#include "Dispatcher.h"
#include "Acceptor.h"

using namespace std;

class ServerSDK : public AcceptorHandler {
	Acceptor* acceptor;
	Dispatcher* dispacher;
//	GameManager* gameManager;
public:
	ServerSDK();
	void handlePeer(TCPSocket* peer);
	void printUsers(TCPSocket* peer);
	virtual ~ServerSDK();
};

#endif /* SERVERSDK_H_ */
