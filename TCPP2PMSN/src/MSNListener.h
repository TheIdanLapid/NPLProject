/*
 * MSNListener.h
 *
 *  Created on: May 22, 2017
 *      Author: user
 */

#ifndef MSNLISTENER_H_
#define MSNLISTENER_H_
#include <stdio.h>
#include <iostream>

using namespace std;

namespace networking {

class MSNListener {
public:
	virtual void handle(const char * msg, string ip, int port) = 0;
};

} /* namespace networking */

#endif /* MSNLISTENER_H_ */
