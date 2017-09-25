/*
 * ServerSDK.h
 *
 *  Created on: Sep 24, 2017
 *      Author: user
 */

#ifndef SERVERSDK_H_
#define SERVERSDK_H_
#include "FileManager.h"
#include "GameManager.h"
#include "Dispatcher.h"
#include "Acceptor.h"

using namespace std;

class ServerSDK : public AcceptorHandler, DispatcherHandler {
	Acceptor* acceptor;
	Dispatcher* dispatcher;
	GameManager* gameManager;
public:
	ServerSDK();
	void start();
	virtual void handlePeer(TCPSocket* peer);
	virtual int openGameSession(User* user1, User* user2);
	void printUsers(TCPSocket* peer);
	virtual ~ServerSDK();
};

#endif /* SERVERSDK_H_ */
