//============================================================================
// Name        : Test.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "UDPSocket.h"
#include "UDPSocketTest.h"

using namespace std;
using namespace networking;

UDPSocketTest::UDPSocketTest() {}

UDPSocketTest::~UDPSocketTest() {}

bool UDPSocketTest::testUDPSocket(){
	//create UDP server
	UDPSocket* server = new UDPSocket(3435);
	//create UDP client
	UDPSocket* client = new UDPSocket();



	//send a message from the client to the server
	string msg = "checking sendto and recv";
	client->connect("127.0.0.1", 3435);
	client->write(msg);

	char buf[100];
	memset((void*)buf,0,100);


	cout<<"UDPSocketTest: the message : "<<msg<<" was sent"<<endl;

	//read the message by the server
	int cc = server->recv(buf, 100);

	if (cc<0)
		{
			perror("UDPSocketTest: error receiving a message");
			return false;
		}
	if (cc != (int)msg.length()){
			perror("UDPSocketTest: wrong size");
			return false;
	}
	//compare the message sent with the message received
	if (msg != buf){
		perror("UDPSocketTest: wrong message");
		return false;
	}
	cout<<"UDPSocketTest: the message : "<<buf<<" received"<< endl;


	//test the reply and fromaddr methods
	server->reply("checking reply");
	memset((void*)buf,0,100);
	client->recv(buf, 100);
	cout<<"UDPSocketTest: the message : "<<buf<<" received"<< endl;

	cout<<"UDPSocketTest: address = "<<server->fromAddr()<<endl;
	cout<<"UDPSocketTest: address = "<<client->fromAddr()<<endl;


	//close all sockets and free memory
	client->close();
	delete(client);
	server->close();
	delete(server);

	return true;
}
