/*
 * MThread.h
 *
 *  Created on: Feb 13, 2013
 *      Author: efi
 */

#ifndef MTHREAD_H_
#define MTHREAD_H_

#include <pthread.h>

using namespace std;

namespace networking {

class MThread{
public:
	pthread_t threadId;
public:
	void start();
	void waitForThread();
	virtual ~MThread();
	virtual void run() = 0;
};

}

#endif /* MTHREAD_H_ */
