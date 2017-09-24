/*
 * Broker.cpp
 *
 *  Created on: Jul 3, 2017
 *      Author: user
 */

#include "Broker.h"
#include "BrokerManager.h"
using namespace std;
namespace networking {

Broker::Broker(TCPSocket* peer1, TCPSocket* peer2, BrokerManager* parent){
	this->parent = parent;
	this->peers = new MTCPListener();
	this->peers->sockets.push_back(peer1);
	this->peers->sockets.push_back(peer2);
	brokerOn = true;
	to = NULL;
	from = NULL;

}

int Broker::sendMessage(TCPSocket* to,int len, const char* buff){

	if (buff != NULL)
	{
		int cmd = 4;
		int res = to->write((char*)&cmd,sizeof(cmd)); //the command '4'
		if (res!=4)
			return -1;
//		cout<<"Broker: cmd size: "<<res<<endl;
		res = to->write((char*)&len,4); //the length of the message
//		cout<<"Broker: int size: "<<res<<endl;
		if (res<4)
			return -1;
		res = to->write(buff,len); //the message
//		cout<<"Broker: message size: "<<res<<endl;
		if (res<4)
			return -1;
	}
	return 0;
}

int Broker::readMessage(TCPSocket* from){
	memset(msg,0,1024);
	int rcvCmd = 0;
	int rc = from->recv((char*)&rcvCmd,4);
	if(rc!=4){
		cerr<<"Broker: fail to read command from socket"<<endl;
		return -1;
	}
	int command = ntohl(rcvCmd);
//	cout<<"Broker: command: "<<command<<endl;
	int len = 0;
	char buff[1024];
	int sumRc=0;
	rc = 0;
	switch(command){
		case SEND_MSG_TO_PEER:
//			cout<<"BROKER: send msg to peer is recevied (4)"<<endl;
			rc = from->recv((char*)&len,4);
//			cout<<"Broker: rc: "<<rc<<endl;
			if(rc<0){
				cerr<<"Broker: Fail to read command from socket"<<endl;
			}
			len = ntohl(len);
//			cout<<"Broker: len: "<<len<<endl;

			rc = from->recv((char*)&buff[sumRc],len-sumRc);
//			cout<<"Broker: again rc: "<<rc<<endl;

			if(rc<0){
				cerr<<"Broker: Fail to read command from socket"<<endl;
			}
			else {
				for (int i=0;i<len;i++) {
					msg[i]=buff[i];
				}
				msg[len]='\0';
				cout<<"Broker: MESSAGE RECEIVED: "<<msg<<endl;
			}
			break;

		case EXIT:
			cout<<"Broker: EXIT COMMAND RECIEVED"<<endl;
			parent->handler->handleReturnedPeer(to);
			brokerOn = false;
			break;

		case CLOSE_SESSION_WITH_PEER:
			parent->handler->handleReturnedPeer(from);
			parent->handler->handleReturnedPeer(to);
//			brokerOn = false;
			break;
	}
	return 0;
}


void Broker::run(){
	while(brokerOn){
		cout<<"Broker: Broker is on! with "<<peers->sockets.size()<<" peers"<<endl;

		from = this->peers->listen(3);
		while (from==NULL)
			this->peers->listen(3);
		cout<<"Broker: "<<from->getPort()<<" (is from)"<<endl;
		if(peers->sockets[0]->getIP()==from->getIP() && peers->sockets[0]->getPort()==from->getPort()){
			to = this->peers->sockets[1];
		}
		else{
			to = this->peers->sockets[0];
		}
		cout<<"Broker: From port: "<<from->getPort()<<endl;
		cout<<"Broker: To port: "<<to->getPort()<<endl;
		int result = readMessage(from);
		sleep(2);
		if(result == -1){
			cout<<"Broker: sorry, couldn't read the message - please try again"<<endl;
		}
		else{
			char c = 'a';
			unsigned int len = 0;
			while(c!='\0' && len<sizeof(msg))
			{
				c=msg[len];
				len++;
			}
			result = sendMessage(to,len-1,msg);
			if(result == -1){
				cout<<"Broker: sorry, couldn't send the message - please try again"<<endl;
			}
		}
	}
	peers->sockets.clear();
//	parent->deleteBroker(this);
//	delete this;
//	cout<<"Broker is closed"<<endl;
}

Broker::~Broker() {
	cout<<"Broker: Broker closed!"<<endl;
	peers->sockets.clear();
	parent->deleteBroker(this);
}
} /* namespace networking */
