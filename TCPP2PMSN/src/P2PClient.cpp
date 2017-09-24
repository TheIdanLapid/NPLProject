/*
 * P2PClient.cpp
 *
 *  Created on: May 21, 2017
 *      Author: user
 */
#include "P2PClient.h"
#include <unistd.h>
#define PORT 1234
using namespace networking;

P2PClient::P2PClient(string ip, int port) {
	client = new TCPSocket(ip,port);
	cliclient = NULL;
	gotMsg=false;
}

bool P2PClient::isGotMsg() const {
	return gotMsg;
}

bool P2PClient::open(string ip, int port){
	if(client!=NULL){
		sleep(1);
		MThread::start();
		return true;
	}
	else
		return false;
}

void P2PClient::send(const string& msg){
	client->send(msg);
	gotMsg = true;
}

void P2PClient::close(){
	client->close();
}

void P2PClient::run(){
//	sleep(1);

	char buffer1[100];
	int buffsize = client->recv(buffer1,100);
	buffer1[buffsize] = '\0';
//	cout<<"P2PClient: recv:"<<buffer1<<endl;
	cout<<"P2PClient: handle client:";
	waitForThread();
	cliclient->handle(buffer1);
}

const TCPSocket* P2PClient::getClient() const {
	return client;
}

P2PClient::~P2PClient() {
	if(client!=NULL){
		client->close();
		delete(client);
	}
	if(cliclient!=NULL)
		delete(cliclient);
}
