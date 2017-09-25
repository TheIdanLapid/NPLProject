/*
 * UserManager.h
 *
 *  Created on: Sep 14, 2017
 *      Author: eontorch
 */

#include "Protocol.h"
#include "User.h"
#include "MTCPListener.h"
#include <vector>
#include <string>
#include "FileManager.h"

#ifndef SRC_USERMANAGER_H_
#define SRC_USERMANAGER_H_

namespace std {

class UserManager {
	vector<User*> unknownUsers;
	vector<User*> loggedUsers;
	FileManager* fileManager; //uMap is defined in Protocol.h as: map<string,pair<string,int> >
	MTCPListener* listener;
public:
	UserManager(FileManager* fm);
	virtual ~UserManager();
	MTCPListener* getListener() const;
	void setListener(MTCPListener* listener);
	vector<User*> getLoggedUsers();
	void setLoggedUsers(const vector<User*>& loggedUsers);
	vector<User*> getUnknownUsers();
	void setUnknownUsers(const vector<User*>& unknownUsers);
	uMap* getUsers();
	void registerUser(string name,string pass);
	int loginUser(string name,string pass);
};

} /* namespace std */

#endif /* SRC_USERMANAGER_H_ */
