/*
 * TCPSocketTest.cpp
 *
 *  Created on: May 8, 2017
 *      Author: user
 */

#include "TCPSocketTest.h"
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
using namespace networking;
TCPSocketTest::TCPSocketTest() {
	// TODO Auto-generated constructor stub

}

bool TCPSocketTest::testTCPSocket(){
	cout<<"TCPSocketTest: testing tcp..."<<endl<<flush;
	MThread::start();
	sleep(3);
	TCPSocket* cliSocket = new TCPSocket("127.0.0.1",MSNGR_PORT);
	cout<<"TCPSocketTest: client connected, the port is:"<<cliSocket->getPort()<<endl;

	string msg = "Hello";
	cliSocket->write(msg);
	char buffer1[100];
//	sleep(5);
	int checkRecv = cliSocket->read(buffer1,100);
	buffer1[checkRecv] = '\0';
	cliSocket->close();
	delete(cliSocket);


	if(checkRecv<0){
		waitForThread();
		perror("TCPSocketTest: client: No message received");
		cliSocket->close();
		delete(cliSocket);
		return false;
	}
	if(checkRecv!=2){
		waitForThread();
		perror("TCPSocketTest: client: Wrong size");
		cliSocket->close();
		delete(cliSocket);
		return false;
	}
	if(strcmp("OK",buffer1)!=0)
	{
		waitForThread();
		perror("TCPSocketTest: client: Wrong msg");
		cliSocket->close();
		delete(cliSocket);
		return false;
	}
//	cout<<"The message: '"<< buffer1 <<"' was received at client." << endl;

	waitForThread();
	return true;
}

void TCPSocketTest::run(){
	cout<<"TCPSocketTest: starting server"<<endl;
	TCPSocket* lisSocket = new TCPSocket(MSNGR_PORT);
	TCPSocket* sessionSocket = lisSocket->listenAndAccept();
	cout<<"TCPSocketTest: Server port:"<<lisSocket->getPort()<<endl;
	cout<<"TCPSocketTest: Session port:"<<sessionSocket->getPort()<<endl;
//	cout<<"The sessionSocket_fd: "<< sessionSocket->getSocketFd()<<endl;
//	cout<<"The new socket is opened" <<endl;
	char buffer[100];

//	sleep(2);
	int checkRecv = sessionSocket->recv(buffer,100);
//	buffer[checkRecv] = '\0';

	if(checkRecv<0){
		sessionSocket->close();
		lisSocket->close();
		delete(sessionSocket);
		delete(lisSocket);
		perror("TCPSocketTest: server: No message received");
	}
	if(checkRecv!=5){
		sessionSocket->close();
		lisSocket->close();
		delete(sessionSocket);
		delete(lisSocket);
		perror("TCPSocketTest: server: Wrong size");
	}
	if(strcmp("Hello",buffer)!=0)
	{
		sessionSocket->close();
		lisSocket->close();
		delete(sessionSocket);
		delete(lisSocket);
		perror("TCPSocketTest: server: Wrong msg");
	}

//	cout<<"The message: '"<<buffer<<"' was received at server."<<endl;
	string msg1 = "OK";
//	sleep(2);
	sessionSocket->send(msg1);


	sessionSocket->close();
	lisSocket->close();
	delete(sessionSocket);
	delete(lisSocket);

}

TCPSocketTest::~TCPSocketTest() {
	// TODO Auto-generated destructor stub
}

