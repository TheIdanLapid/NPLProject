/*
 * TCPMSNClient.cpp
 *
 *  Created on: Jun 18, 2017
 *      Author: user
 */

#include "TCPMSNClient.h"

namespace networking {
TCPMSNClientHandler::~TCPMSNClientHandler(){}

TCPMSNClient::TCPMSNClient(TCPMSNClientHandler* handler) {
	this->handler = handler;
	socket = NULL;
	connected = false;
	closed = false;
}

void TCPMSNClient::run(){
	while (connected) {
		char* data;
		int read = readcommand(data);
		if (read == -1)
			cerr<<"TCPMSNClient: Can't read command"<<endl;
		//else
		else if (read == 0)
		{
			cout<<"TCPMSNClient: readcommand returned with 0!"<<endl;
		}
//		if(read!=-1)
//		{
//			cout<<"TCPMSNClient: got command "<<data<<endl;
//		}
	}
}

bool TCPMSNClient::connect(string ip) {

	socket = new TCPSocket(ip, MSNGR_PORT);
	if (socket>0)
	{
		connected = true;
		start();
		return true;
	}
	return false;
}

bool TCPMSNClient::openSession(string ip, int port) {
	//send command openSession to the server
	//send data ip:port
	char buff[100];
	sprintf(buff,"%s:%d",ip.c_str(),port);
//	cout<<"TCPMSNClient: data to send:"<<buff<<endl;
	int success = sendCommand(OPEN_SESSION_WITH_PEER,buff);
	if (success == -1)
		return false;
	return true;
}

void TCPMSNClient::sendMessage(string msg) {
	cout<<"Client: sent: "<<msg<<" to other peer"<<endl;
	int success = sendCommand(SEND_MSG_TO_PEER, msg.c_str());
	if (success==-1)
		cerr<<"TCPMSNClient: Couldn't sent msg"<<msg<<endl;
}

void TCPMSNClient::closeSession() {
	cout<<"closing the session"<<endl;
//	sleep(1);
	int success = sendCommand(CLOSE_SESSION_WITH_PEER,NULL);
	if (success==-1)
		cerr<<"TCPMSNClient: Couldn't close session"<<endl;
	else
		closed = true;
}

void TCPMSNClient::disconnect() {
	cout<<"disconnecting peer on port: "<<socket->getPort()<<endl;
	int success = sendCommand(EXIT,NULL);
	if (success==-1)
		cerr<<"TCPMSNClient: Can't disconnect"<<endl;
	if (socket!=NULL) {
		if (!closed)
			closeSession();
		socket->close();
//		this->waitForThread();
		delete socket;
		socket = NULL;
	}
	else
	{
		connected = false;
	}
}

void TCPMSNClient::exit() {
	if (!closed)
		closeSession();
	if (connected)
		disconnect();
}

int TCPMSNClient::sendCommand(int command,const char* buff){
	int cmdNet = htonl(command);
	int res = socket->write((char*)&cmdNet,4); //the command int from the protocol
	if (res<4)
		return -1;
	if (buff != NULL)
	{
		int len = strlen(buff);
		int lenNet = htonl(len);
		res = socket->write((char*)&lenNet,4); //the length of the message
		if (res<4)
			return -1;
		res = socket->write(buff,len); //the message
		if (res<4)
			return -1;
	}
	if(cmdNet==4 ||cmdNet==2)
		cout<<"TCPMSNClient: Sent msg: "<<buff<<endl;
//	sleep(2);
	return res;
}

int TCPMSNClient::readcommand(char* data){
	int rcvCmd = 0;
	int len = 0;
	char buff[1024];
	sleep(1);
	int rc = 0;
	do{
	rc = socket->recv((char*)&rcvCmd,4);
//	cout<<"TCPMSNClient: rcvCmd while rc!=4:"<<rcvCmd<<endl;
	} while(rc!=4);
//	if(rc!=4){
//		cerr<<"fail to read command from socket"<<endl;
//		return -1;
//	}
//	rcvCmd = ntohl(rcvCmd);
	if (rcvCmd<7) {
		data = "";
		cout<<"TCPMSNClient: rcvCmd: "<<rcvCmd<<endl;
		switch(rcvCmd){

		case SESSION_ESTABLISHED:
			//update the lastRcvMsg to "onOpenSession"
			handler->onOpenSession("127.0.0.1",0);
			break;

		case SESSION_REFUSED:
			cerr<<"TCPMSNClient: "<<SESSION_REFUSED_MSG<<endl;
			break;

		case OPEN_SESSION_WITH_PEER:
			rc = socket->recv((char*)&len,4);
			if(rc<0){
				cerr<<"TCPMSNClient: fail to read command from socket"<<endl;
				return -1;
			}
			len = ntohl(len);
			rc = socket->recv(buff,len);
			if(rc<0){
				cerr<<"TCPMSNClient: fail to read command from socket"<<endl;
				return -1;
			}
			buff[len] = '\0';
			data = buff;
			handler->onOpenSession("127.0.0.1", socket->getPort()); //our port or the other peer's port?
			break;

		case SEND_MSG_TO_PEER:
	//		cout<<"Client: send msg to peer is recevied (4)"<<endl;
			rc = socket->recv((char*)&len,4);
	//		cout<<"TCPMSNClient: rc len: "<<rc<<endl;
			if(rc<0){
				cerr<<"TCPMSNClient: fail to read command from socket"<<endl;
				return -1;
			}
	//		len = ntohl(len);
			rc = socket->recv(buff,len);
	//		cout<<"TCPMSNClient: rc buff: "<<rc<<endl;
			if(rc<0){
				cerr<<"TCPMSNClient: fail to read command from socket"<<endl;
				return -1;
			}
			buff[len] = '\0';
			data = buff;
			cout<<"TCPMSNClient: data: "<<data<<endl;
			//update the lastRcvMsg to @data
			handler->onMessageRecieved(data);
			break;

		case CLOSE_SESSION_WITH_PEER:
			//update the lastRcvMsg to "onClosedSession"
			handler->onClosedSession();
			break;
		default:
			cout<<"TCPMSNClient: no command"<<endl;
			break;
		}
	}
	return 0;
}
int TCPMSNClient::getPort(){
	socklen_t addressLength = sizeof(socket->remote);
	getsockname(socket->socket_fd, ((struct sockaddr*)&socket->remote), &addressLength);
	cout<<"TCPMSNClient: "<<(int) ntohs(socket->remote.sin_port)<<endl;
	return ((int) ntohs(socket->remote.sin_port));
}

TCPMSNClient::~TCPMSNClient() {
	if(socket!=NULL)
		delete socket;
//	if(handler!=NULL)
//		delete handler;
}

} /* namespace networking */
