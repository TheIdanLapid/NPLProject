/*
 * TCPP2PMSN.cpp
 *
 *  Created on: May 21, 2017
 *      Author: user
 */

#include "TCPP2PMSN.h"
#define PORT 1234
using namespace networking;

P2PServer * TCPP2PMSN::p2pserver;
P2PClient * TCPP2PMSN::p2pclient;

TCPP2PMSN::TCPP2PMSN() {

}
void TCPP2PMSN::init(int port){
	p2pserver = new P2PServer(port);
	sleep(2);
	p2pclient = NULL;
}

bool TCPP2PMSN::open(string ip, int port){
	if(p2pclient!=NULL)
	{
		delete(p2pclient);
	}
		p2pclient = new P2PClient(ip,port);
		bool isOpen = p2pclient->open(ip,port);
		if(!isOpen)
		{
			delete p2pclient;
			return false;
		}

	return true;
}

void TCPP2PMSN::send(const string& msg){
	sleep(3);
	if (p2pclient!=NULL)
	{
		if(isActiveClientSession()){
			p2pclient->send(msg);
		}
		else
			cout<<"TCPP2PMSN: client not connected"<<endl;
	}
}

void TCPP2PMSN::reply(const string& msg){
	sleep(5);
	if (p2pserver!=NULL)
	{
		if(isActiveClientSession()){
			p2pserver->reply(msg);
		}
		else
			cout<<"TCPP2PMSN: peer not connected"<<endl;
	}
}
void TCPP2PMSN::close(){
	if (p2pserver!=NULL)
		delete(p2pserver);
	if (p2pclient!=NULL)
		delete(p2pclient);
}

bool TCPP2PMSN::isActivePeerSession(){
	return ((p2pserver->getSession()->getSocketFd())>0);
}

bool TCPP2PMSN::isActiveClientSession(){
	return ((p2pclient->getClient()->getSocketFd())>0);
}

TCPP2PMSN::~TCPP2PMSN() {
	if (p2pserver!=NULL)
		delete(p2pserver);
	if (p2pclient!=NULL)
		delete(p2pclient);
}

