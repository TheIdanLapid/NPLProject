/*
 * Server.h
 *
 *  Created on: Jul 3, 2017
 *      Author: user
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "TCPSocket.h"
#include "MThread.h"
#include "TCPMessengerProtocol.h"
using namespace std;
namespace networking {
//Listenes on tcp socket, whenever a peer is ready
class ServerHandler {
public:
	virtual void handlePeer(TCPSocket* peer) = 0;
	virtual ~ServerHandler();
};

class Server : public MThread {
	ServerHandler* handler;
	TCPSocket* socket;
	bool exitFromServer;
public:
	Server(ServerHandler* handler);
	virtual void run();
	void exit();
	virtual ~Server();
};

} /* namespace networking */

#endif /* SERVER_H_ */
