/*
 * TCPMSNServerTest.cpp
 *
 *  Created on: Jul 9, 2017
 *      Author: user
 */

#include "TCPMSNServerTest.h"

using namespace std;
namespace networking {

TCPMSNServerTest::TCPMSNServerTest(){
	server = NULL;
//	handler1 =new CLIHandler();
//	handler2 =new CLIHandler();
//	client1 = new TCPMSNClient(&handler1);
//	client2 = new TCPMSNClient(&handler2);
}

void TCPMSNServerTest::run() {
	server = new TCPMSNServer();
	server->start();
	CLIHandler handler1;
	CLIHandler handler2;
	TCPMSNClient client1(&handler1);
		client1.start();

	int success = 0;

	do
	{
		success = client1.connect(MSNGR_IP);
		if (success==0)
			cout<<"client1 didn't connect!"<<endl;
		sleep(2);
//		delete(this);
	} while(success==0);
//	waitForThread();

	TCPMSNClient client2(&handler2);
		client2.start();
	success = 0;
	do
	{
		success = client2.connect(MSNGR_IP);
		if (success==0)
			cout<<"client2 didn't connect!"<<endl;
		sleep(2);
//		delete(this);
	} while(success==0);

	sleep(2);

	cout<<"Testing open session: Port: "<<client1.getPort()<<" is opening session with port: "<<client2.getPort()<<endl;
	do {
		success = client1.openSession(MSNGR_IP,client2.getPort());
		sleep(2);
	} while (success==0);
//	}
//	{
//		cout<<"client1 didn't open session!"<<endl;
////		delete(this);
//	};

//	sleep(1);
	client1.sendMessage("message from 1 to 2");
	sleep(3);
	cout<<"lastRcvdMsg of 2: "<<handler2.lastRcvdMsg<<endl;

	client2.sendMessage("message from 2 to 1");
	sleep(3);
	cout<<"lastRcvdMsg of 1: "<<handler1.lastRcvdMsg<<endl;

	cout<<"Closing session & disconnecting clients..."<<endl;

	client1.closeSession();
//	sleep(2);
//	client1.disconnect();
//	sleep(2);
//	client2.disconnect();
//	sleep(2);
//	server->close();
}

bool TCPMSNServerTest::testTCPMSNServer() {
	cout<<"Testing Server..."<<endl<<flush;
	MThread::start();
	waitForThread();
//	cout<<"End of the test"<<endl;
	return true;
}

TCPMSNServerTest::~TCPMSNServerTest() {
	delete(server);
	cout<<"TCPMSNServerTEST closed!"<<endl;
}

} /* namespace networking */
