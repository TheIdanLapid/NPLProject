/*
 * Server.cpp
 *
 *  Created on: Jul 3, 2017
 *      Author: user
 */

#include "Server.h"
using namespace std;
namespace networking {

Server::Server(ServerHandler* handler) {
	this->handler = handler;
	exitFromServer = false;
	socket = NULL;
}

void Server::run() {
	cout<<"Server: Server is running..."<<endl;
	socket = new TCPSocket(MSNGR_PORT);
	TCPSocket* peer = NULL;
	while (!exitFromServer) {
		peer = socket->listenAndAccept();
		if (peer == NULL) {
			cout<<"Server: can't connect the peer"<<endl;
		}
		else
		{
			cout<<"Server: "<<peer->getPort()<<" REMOTE PEER PORT"<<endl;
			handler->handlePeer(peer);
		}
	}
}

void Server::exit() {
	socket->close();
//	waitForThread();
	delete socket;
}

Server::~Server() {
	cout<<"Server: Server is closed for business!"<<endl;
//	delete(handler); //?
}

} /* namespace networking */
