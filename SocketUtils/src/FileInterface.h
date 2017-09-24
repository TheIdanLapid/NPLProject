/*
 * FileInterface.h
 *
 *  Created on: Jun 14, 2017
 *      Author: user
 */

#ifndef FILEINTERFACE_H_
#define FILEINTERFACE_H_
#include "MThread.h"
#include "FileInterface.h"
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

namespace networking {

class FileInterface {
	virtual void close() = 0;
	virtual int read(char* buff, int size) = 0;
	virtual int write(const string& msg) = 0;
	};
}


#endif /* FILEINTERFACE_H_ */
