/*
 * TCPP2PMSN.h
 *
 *  Created on: May 21, 2017
 *      Author: user
 */

#ifndef TCPP2PMSN_H_
#define TCPP2PMSN_H_

#include "P2PServer.h"
#include "P2PClient.h"
//#include "TCPSocket.h"
//#include "MThread.h"

#include <iostream>
#include <unistd.h>
using namespace std;

namespace networking {

class TCPP2PMSN{


public:
	static P2PServer * p2pserver;
	static P2PClient * p2pclient;
	TCPP2PMSN();
	virtual ~TCPP2PMSN();

	/*open the msn server on the given port
	param port - server port number*/
	void init(int port);

	/*open TCP Socket with the other side
	param ip - the client ip
	param poet - the client port*/
	bool open(string ip, int port);

	/*sends the message from the client to the server*/
	static void send(const string& msg);

	/*the server reply with his message to the client */

	static void reply(const string& msg);

	/*close the session*/
	void close();

	/*check if i'm connected as a client*/
	static bool isActiveClientSession();

	/*check if someone is connected to me*/
	static bool isActivePeerSession();

};

} /* namespace networking */

#endif /* TCPP2PMSN_H_ */
