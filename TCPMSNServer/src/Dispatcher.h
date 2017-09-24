/*
 * Dispatcher.h
 *
 *  Created on: Jul 3, 2017
 *      Author: user
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_
#include "MThread.h"
#include "TCPSocket.h"
#include "Guard.h"
#include "MTCPListener.h"
#include "TCPMessengerProtocol.h"
#include <string>
#include <strings.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
namespace networking {

class DispatcherHandler{
public:
	virtual int managePeerSession(TCPSocket* peer1, TCPSocket* peer2) = 0;
	virtual ~DispatcherHandler();
};

class Dispatcher: public MThread {
	typedef vector<TCPSocket*> tSockets;
	MTCPListener* waitingPeers;
	MTCPListener* peers;
	DispatcherHandler* handler;
	bool peersOn,closed;
	pthread_mutex_t mutex;
	bool peeread;
public:
	Dispatcher(DispatcherHandler* handler);
	void addPeer(TCPSocket* peer);
	bool removePeer(TCPSocket* peer);
	int sendFeedback(TCPSocket* peer, int command);
	int readCommand(TCPSocket* peer);
	int getPeerIndex(string ip,int port);
	virtual void run();
	void close();
	virtual ~Dispatcher();
};

} /* namespace networking */

#endif /* DISPATCHER_H_ */
