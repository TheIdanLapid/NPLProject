/*
 * GameManager.cpp
 *
 *  Created on: Sep 25, 2017
 *      Author: eontorch
 */

#include "GameManager.h"

namespace std {

GameManager::GameManager() {
	// TODO Auto-generated constructor stub

}

int GameManager::openGameSession(User* user1, User* user2) {
	Game* game = new Game(user1,user2);
}

GameManager::~GameManager() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
