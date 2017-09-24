/*
 * TCPMSNServer.cpp
 *
 *  Created on: Jul 3, 2017
 *      Author: user
 */

#include "TCPMSNServer.h"
using namespace std;
namespace networking {

TCPMSNServer::TCPMSNServer(){
	server = new Server(this);
	dispatcher = new Dispatcher(this);
	brokerMng = new BrokerManager(this);
}

void TCPMSNServer::start(){
	cout<<"TCPMSNServer: Started"<<endl;
	sleep(2);
	server->start();
	sleep(2);
	dispatcher->start();
//	cout<<"TCPMSNServer: End of start"<<endl;

}

void TCPMSNServer::handlePeer(TCPSocket* peer){
	dispatcher->addPeer(peer);
}

int TCPMSNServer::managePeerSession(TCPSocket* peer1, TCPSocket* peer2){
	if(this->brokerMng->createBroker(peer1,peer2)){
		return SESSION_ESTABLISHED;
	}
	return SESSION_REFUSED;
}

void TCPMSNServer::handleReturnedPeer(TCPSocket* peer){
	dispatcher->addPeer(peer);
}

BrokerManagerHandler::~BrokerManagerHandler(){}
DispatcherHandler::~DispatcherHandler(){}
ServerHandler::~ServerHandler(){}

bool TCPMSNServer::close(){
	delete(server); //?
	delete(dispatcher); //?
	delete(brokerMng); //?
//	delete(this);
	return true;
}

TCPMSNServer::~TCPMSNServer() {
	cout<<"TCPMSNServer: TCPMSNServer closed!"<<endl;
//	delete(server); //?
//	delete(dispatcher); //?
//	delete(brokerMng); //?
}

} /* namespace networking */
