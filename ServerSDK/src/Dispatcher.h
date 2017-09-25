/*
 * Dispatcher.h
 *
 *  Created on: Sep 24, 2017
 *      Author: user
 */

#include "MThread.h"
#include "TCPSocket.h"
#include "MTCPListener.h"
#include "Guard.h"
#include <string>
#include <strings.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FileManager.h"
#include "UserManager.h"
#include <vector>

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

using namespace std;

class DispatcherHandler{
public:
	virtual int openGameSession(User* user1, User* user2) = 0;
	virtual ~DispatcherHandler();
};

class Dispatcher: public MThread {
	FileManager* fm;
	UserManager* um;
	typedef vector<TCPSocket*> tSockets;
	map<TCPSocket*, User> tcpMap; //Maps a user to it's tcpSocket
	MTCPListener* waitingPeers;
	MTCPListener* peers;
	DispatcherHandler* handler;
	bool peersOn,closed;
	pthread_mutex_t mutex;
	bool peeread;
public:
	Dispatcher(DispatcherHandler* handler);
	void addPeer(TCPSocket* peer);
//	bool removePeer(TCPSocket* peer);
	int sendFeedback(TCPSocket* peer, int command);
	int readCommand(TCPSocket* peer);
//	int getPeerIndex(string ip,int port);
	virtual void run();
//	void close();
	void printLoggedUsers(TCPSocket* peer);
	virtual ~Dispatcher();
};

#endif /* DISPATCHER_H_ */
