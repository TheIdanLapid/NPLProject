/*
 * File.cpp
 *
 *  Created on: Jun 14, 2017
 *      Author: user
 */

#include "File.h"

namespace networking {

File::File(string path) {
	file.open(path.c_str(),ios::in);
}

void File::close() {
	file.close();
}

int File::read(char* buff, int size) {
	file.read(buff,size);
	if (file!=NULL)
		return 1;
	return -1;
}

int File::write(const string& msg) {
	file.write(msg.c_str(),sizeof(msg));
	if (file!=NULL)
		return 1;
	return -1;
}

File::~File() {
	// TODO Auto-generated destructor stub
}

} /* namespace networking */
