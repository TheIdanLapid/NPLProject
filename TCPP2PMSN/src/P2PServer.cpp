/*
 * P2PServer.cpp
 *
 *  Created on: May 21, 2017
 *      Author: user
 */

#include "P2PServer.h"
#define PORT 1234
using namespace networking;

P2PServer::P2PServer(int port) {
	server = new TCPSocket(port);
//	sleep(1);
	init(port);
	session = NULL;
//	cliserver = new Handler();
	flag = false;
}

void P2PServer::init(int port){
	if(server!=NULL){
		MThread::start();
	}
}

void P2PServer::reply(const string& msg){
	if(session)
		session->send(msg);
	else
		cout<<"P2PServer: no server"<<endl;
}

void P2PServer::run(){
	char buffer[100];

	while (!flag)
	{
		session = server->listenAndAccept();
		session->getSocketFd();
		int buffsize = session->recv(buffer,100);
		buffer[buffsize] = '\0';
		cout<<"P2PServer: handle server:";
		waitForThread();
		cliserver->handle(buffer);
	}
}

P2PServer::~P2PServer() {
		flag=true;
		close();
		delete(server);
		delete(session);
		delete(cliserver);
}

const TCPSocket* P2PServer::getServer() const {
	return server;
}

const TCPSocket* P2PServer::getSession() const {
	return session;
}

void P2PServer::close(){
	flag = true;

	if(session!=NULL)
		session->close();
	if(server!=NULL)
		server->close();
}
