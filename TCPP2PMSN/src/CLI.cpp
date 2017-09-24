/*
 * CLI.cpp
 *
 *  Created on: May 22, 2017
 *      Author: user
 */

#include "CLI.h"

using namespace networking;

CLI::CLI(){
	msn = NULL;
	port=0;
	exit=false;
}


void CLI::init() {
	msn = new TCPP2PMSN();
	cout<<"CLI: Hi, welcome to messenger. Please enter the port of the peer you want to talk to:"<<endl;
	cin >> port;
	if (port>1024)
	{
		msn->init(port);
	}
}

void CLI::open() {
	cout<<"CLI: Please enter his/her ip:"<<endl;
	string ip;
	ip.erase(0,1);
	cin >> ip;
	msn->open(ip,port);
}

void CLI::send() {
	string msg;
	cout<<"CLI: Please enter your message:"<<endl;
	msg.erase(0,1);
//	getline(std::cin,msg);
	cin>>msg;
	if (msg == "close")
	{
		setExit(true);
	}
	else
	{
		msn->send(msg.c_str());
	}
}

void CLI::reply() {
//	if (msn->p2pclient->isGotMsg())
//	{
		string msg1;
		cout<<"CLI: Please reply:"<<endl;
		msg1.erase(0,1);
		cin>>msg1;
		if (msg1 == "close")
		{
			setExit(true);
		}
		else
		{
			msn->reply(msg1.c_str());
		}
//	}
}

void CLI::close() {
	msn->close();
}

void CLI::setExit(bool toExit) {
	exit = toExit;
}

bool CLI::isExit() {
	return exit;
}

CLI::~CLI() {
	// TODO Auto-generated destructor stub
}
