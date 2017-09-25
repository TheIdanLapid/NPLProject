/*
 * GameManager.h
 *
 *  Created on: Sep 25, 2017
 *      Author: eontorch
 */

#ifndef SRC_GAMEMANAGER_H_
#define SRC_GAMEMANAGER_H_

#include "User.h"
#include "Game.h"

namespace std {

class GameManager {
public:
	GameManager();
	int openGameSession(User* user1, User* user2);
	virtual ~GameManager();
};

} /* namespace std */

#endif /* SRC_GAMEMANAGER_H_ */
