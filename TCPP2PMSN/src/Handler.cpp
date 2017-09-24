/*
 * Handler.cpp
 *
 *  Created on: May 23, 2017
 *      Author: user
 */

#include "Handler.h"

using namespace networking;

Handler::Handler() {
	// TODO Auto-generated constructor stub

}

void Handler::handle(const string & msg){
	cout<<"Handler: "<< msg << endl;
}

Handler::~Handler() {
	// TODO Auto-generated destructor stub
}

