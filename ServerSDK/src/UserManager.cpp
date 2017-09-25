/*
 * UserManager.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: eontorch
 */

#include "UserManager.h"

namespace std {

UserManager::UserManager(FileManager* fm) {
	fileManager = fm;
	listener = new MTCPListener();
}

UserManager::~UserManager() {
	// TODO Auto-generated destructor stub
}

MTCPListener* UserManager::getListener() const {
	return listener;
}

void UserManager::setListener (MTCPListener* listener) {
	this->listener = listener;
}

vector<User*> UserManager::getLoggedUsers() {
	return loggedUsers;
}

void UserManager::setLoggedUsers(const vector<User*>& loggedUsers) {
	this->loggedUsers = loggedUsers;
}

vector<User*> UserManager::getUnknownUsers() {
	return unknownUsers;
}

void UserManager::setUnknownUsers(const vector<User*>& unknownUsers) {
	this->unknownUsers = unknownUsers;
}

uMap* UserManager::getUsers() {
	return fileManager->getUsersMap();
}

int UserManager::loginUser(string name, string pass) {
	User* user = fileManager->getUserFromMap(name);
	if (user != NULL) {
		if (pass==user->getPass()) {
			loggedUsers.push_back(user);
			return 0;
		}
		else {
			cerr<<"Wrong password!"<<endl;
			return -2;
		}
	}
	else {
		cerr<<"Didn't find the name: "<<name<<endl;
		return -1;
	}
}

void UserManager::registerUser(string name,string pass) {
	fileManager->readUsers();
	User* user = new User(name, pass);
	uMap::iterator iter;
	uMap* map = getUsers();
	iter = map->find(name);
	if(iter != map->end()) {
		cerr<<"The user already exists!"<<endl;
	}
	else {
//		cout<<"Writing: "<<name<<endl;
		fileManager->writeUser(*user);
		uMap* map = fileManager->getUsersMap();
		uMap::iterator pos;
		for (pos = (*map).begin(); pos != (*map).end(); ++pos) {
			cout << "key: " << pos->first << " values: pass: " << pos->second.first << " score: " <<pos->second.second << endl;
		}
	}
}


} /* namespace std */
