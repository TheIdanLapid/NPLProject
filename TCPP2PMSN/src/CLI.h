/*
 * CLI.h
 *
 *  Created on: May 22, 2017
 *      Author: user
 */

#ifndef CLI_H_
#define CLI_H_

#include <stdlib.h>
#include <stdio.h>
#include "TCPP2PMSN.h"
namespace networking {

class CLI {

	int port;
	TCPP2PMSN * msn;
	bool exit;

public:
	CLI();

	//open server
	void init();

	//open client
	void open();

	/*sends the message from the client to the server*/
	void send();

	/*the server reply with his message to the client */
	void reply();

	/*close the session*/
	void close();

	void setExit(bool toExit);

	bool isExit();

	virtual ~CLI();

	const TCPP2PMSN* getMsn() const {
		return msn;
	}
};

} /* namespace networking */

#endif /* CLI_H_ */
