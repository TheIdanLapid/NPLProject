/*
 * TCPMSNClient.h
 *
 *  Created on: Jun 18, 2017
 *      Author: user
 */

#ifndef TCPMSNCLIENT_H_
#define TCPMSNCLIENT_H_
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include "TCPMessengerProtocol.h"
#include <stdio.h>
#include "TCPSocket.h"
#include "MThread.h"

using namespace std;
namespace networking {

class TCPMSNClientHandler{
public:
	virtual void onMessageRecieved(char* message) = 0;
	virtual void onOpenSession(string ip, int port) = 0;
	virtual void onClosedSession() = 0;
	virtual ~TCPMSNClientHandler();
};

class TCPMSNClient: public MThread {
private:
	TCPMSNClientHandler* handler;
	TCPSocket* socket;
	bool connected,closed;
	int readcommand(char* data);
	int sendCommand(int command,const char* buff);

public:
	TCPMSNClient(TCPMSNClientHandler* handler);
	//connect the client to the remote server on the given ip the server port is read from the protocol
	//@param ip - the ip of the server to connect to
	//@return - true on success, otherwise false
	bool connect(string ip);
	//open session with another peer, the request is passed through the server
	bool openSession(string ip, int port);

	void sendMessage(string msg);

	void closeSession();

	void disconnect();

	void exit();

	int getPort();

	virtual void run();

	virtual ~TCPMSNClient();
};

} /* namespace networking */

#endif /* TCPMSNCLIENT_H_ */
