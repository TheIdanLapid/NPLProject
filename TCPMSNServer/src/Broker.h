/*
 * Broker.h
 *
 *  Created on: Jul 3, 2017
 *      Author: user
 */

#ifndef BROKER_H_
#define BROKER_H_
#include "MThread.h"
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "MTCPListener.h"
#include <cstring>
#include "BrokerManager.h"
using namespace std;
namespace networking {
class BrokerManager;


class Broker: public MThread {
	BrokerManager* parent;
	MTCPListener* peers;
	TCPSocket* from;
	TCPSocket* to;
//	char[100] msg;
	char msg[1024];
	bool brokerOn;
public:
	Broker(TCPSocket* peer1, TCPSocket* peer2, BrokerManager* parent);
	virtual void run();
	int sendMessage(TCPSocket* toPeer,int len, const char* buff);
	int readMessage(TCPSocket* fromPeer);
	virtual ~Broker();
};

} /* namespace networking */

#endif /* BROKER_H_ */
