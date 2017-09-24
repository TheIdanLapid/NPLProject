/*
 * main.cpp
 *
 *  Created on: May 8, 2017
 *      Author: 5Shdema & Idan
 */
#include "TCPSocketTest.h"
#include "UDPSocketTest.h"
#include "TCPMSNServerTest.h"

using namespace std;
using namespace networking;

int main(int argc, char **argv) {
//	TCPSocketTest tcpTest;
//	UDPSocketTest udpTest;
	TCPMSNServerTest serverTest;

//	if(udpTest.testUDPSocket())
//	{
//		cout<<"UDP TEST OK"<<endl;
//	}
//	else
//		cout<<"UDP TEST FAIL"<<endl;
//
//	if(tcpTest.testTCPSocket())
//	{
//		cout<<"TCP TEST OK"<<endl;
//	}
//	else
//		cout<<"TCP TEST FAIL"<<endl;
	if(serverTest.testTCPMSNServer())
	{
		cout<<"SERVER TEST OK"<<endl;
	}
	else
		cout<<"SERVER TEST FAILED"<<endl;

	return 0;

}
