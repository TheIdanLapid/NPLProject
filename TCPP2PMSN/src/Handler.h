/*
 * Handler.h
 *
 *  Created on: May 23, 2017
 *      Author: user
 */

#ifndef HANDLER_H_
#define HANDLER_H_

#include "MSNListener.h"

namespace networking {

class Handler: public MSNListener {
public:
	Handler();
	void handle(const string & msg);
	virtual ~Handler();
};

} /* namespace networking */

#endif /* HANDLER_H_ */
