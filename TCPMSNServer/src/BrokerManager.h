/*
 * BrokerManager.h
 *
 *  Created on: Jul 3, 2017
 *      Author: user
 */

#ifndef BROKERMANAGER_H_
#define BROKERMANAGER_H_
#include "TCPSocket.h"
#include "Broker.h"
#include <vector>
#include "Guard.h"
using namespace std;
namespace networking {
class Broker;
class BrokerManagerHandler{
public:
	virtual void handleReturnedPeer(TCPSocket* peer) = 0;
	virtual ~BrokerManagerHandler();
};


class BrokerManager : public MThread {
	pthread_mutex_t mutex;
	vector<Broker*> brokers;
	bool closed;
public:
	BrokerManagerHandler* handler;
	BrokerManager(BrokerManagerHandler* handler);
	bool createBroker(TCPSocket* peer1, TCPSocket* peer2);
	void releasePeer(TCPSocket* peer);
	void deleteBroker(Broker* broker);
	virtual void run();
	void setClosed();
	virtual ~BrokerManager();
};

} /* namespace networking */

#endif /* BROKERMANAGER_H_ */
