/*
 * BrokerManager.cpp
 *
 *  Created on: Jul 3, 2017
 *      Author: user
 */

#include "BrokerManager.h"
using namespace std;
namespace networking {

BrokerManager::BrokerManager(BrokerManagerHandler* handler){
	this->handler = handler;
	closed = false;
	mutex = PTHREAD_MUTEX_INITIALIZER;
	start();
}

void BrokerManager::run() {
	while (!closed)
	{
//		cout<<"BrokerManager: Broker manager running!"<<endl;
	}
}

bool BrokerManager::createBroker(TCPSocket* peer1, TCPSocket* peer2){
//	cout<<"BrokerManager: I AM ALIVEEE"<<endl;
	Broker* broker = new Broker(peer1,peer2,this);
	sleep(2);
	cout<<"BrokerManager: New broker created!"<<endl;
	if(broker!=NULL){
		Guard guard(&mutex);
		brokers.push_back(broker); //add the broker to the brokers list
		broker->start();
		return true;
	}
	return false;
}

void BrokerManager::releasePeer(TCPSocket* peer){
	handler->handleReturnedPeer(peer);
}

void BrokerManager::deleteBroker(Broker* const broker){
	bool found = false;
	for(unsigned int i=0; !found && i<brokers.size();i++){
		Broker* curr = brokers[i];
		if(curr==broker){
			Guard guard(&mutex);
			brokers.erase(brokers.begin()+i);
			found = true;
		}
	}
	//remove the broker from the brokers list
}

void BrokerManager::setClosed() {
	closed = true;
}

BrokerManager::~BrokerManager() {
	cout<<"BrokerManager: BrokerManager closed!"<<endl;
	if(!brokers.empty()) {
		Guard guard(&mutex);
		brokers.clear(); //?
	}
		//	delete(handler); //?
}

} /* namespace networking */

