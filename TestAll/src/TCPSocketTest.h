/*
 * TCPSocketTest.h
 *
 *  Created on: May 8, 2017
 *      Author: user
 */

#ifndef TCPSOCKETTEST_H_
#define TCPSOCKETTEST_H_
#include "MThread.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"

using namespace std;

namespace networking {
class TCPSocketTest: public MThread {
public:
	TCPSocketTest();
	bool testTCPSocket();
	void run();
	virtual ~TCPSocketTest();
};
}

#endif /* TCPSOCKETTEST_H_ */
