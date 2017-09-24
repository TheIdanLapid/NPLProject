/*
 * P2PClient.h
 *
 *  Created on: May 21, 2017
 *      Author: user
 */

#ifndef P2PCLIENT_H_
#define P2PCLIENT_H_
#include <iostream>
#include "TCPSocket.h"
#include "MThread.h"
#include "Handler.h"

using namespace std;
namespace networking {

class P2PClient:public MThread {
private:
	Handler* cliclient;
	TCPSocket * client;
	bool gotMsg;
public:
	P2PClient(string ip, int port);
	bool open(string ip, int port);

	void send(const string& msg);

	virtual ~P2PClient();

	void close();

	void run();

	const TCPSocket* getClient() const;

	bool isGotMsg() const;
};

} /* namespace networking */

#endif /* P2PCLIENT_H_ */
