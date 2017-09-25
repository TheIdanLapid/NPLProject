/*
 * Game.h
 *
 *  Created on: Sep 25, 2017
 *      Author: eontorch
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "User.h"

namespace std {

class Game {
public:
	Game();
	Game(User* user1, User* user2);
	virtual ~Game();
};

} /* namespace std */

#endif /* SRC_GAME_H_ */
