/*
 * P2PServer.h
 *
 *  Created on: May 21, 2017
 *      Author: user
 */

#ifndef P2PSERVER_H_
#define P2PSERVER_H_
#include <iostream>
#include "TCPSocket.h"
#include "MThread.h"
#include "Handler.h"

using namespace std;

namespace networking {

class P2PServer:public MThread {

private:
	TCPSocket * server;
	Handler* cliserver;
	bool flag;
	TCPSocket * session;

public:
	P2PServer(int port);

	void init(int port);

	void reply(const string& msg);

	void close();

	void run();

	virtual ~P2PServer();

	const TCPSocket* getServer() const;

	const TCPSocket* getSession() const;

};

} /* namespace networking */

#endif /* P2PSERVER_H_ */
