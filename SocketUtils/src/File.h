/*
 * File.h
 *
 *  Created on: Jun 14, 2017
 *      Author: user
 */

#ifndef FILE_H_
#define FILE_H_

#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include "FileInterface.h"


namespace networking {

class File : public FileInterface {
	fstream file;
public:
	File(string path);
	void close();
	int read(char* buff, int size);
	int write(const string& msg);
	virtual ~File();
};

} /* namespace networking */

#endif /* FILE_H_ */
