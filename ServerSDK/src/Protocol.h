/*
 * Protocol.h
 *
 *  Created on: Sep 4, 2017
 *      Author: idan
 */
#include <map>
#include <string>


#ifndef PROTOCOL_H_
#define PROTOCOL_H_

/**
 * Game Protocol:
 * all messages are of the format [Command 4 byte int]
 * and optionally data follows in the format [Data length 4 byte int][ Data ]
 */
using namespace std;

#define SERVER_PORT 3346
#define IP "127.0.0.1"

typedef map<string,pair<string,int> > uMap;

#define REGISTER				1	//Followed by user:pass
#define LOGIN					2	//Followed by user:pass
#define SHOW_USERS				3
#define OPEN_MATCH_WITH_USER 	4	//Followed by user
#define ACCEPT_MATCH			5
#define DECLINE_MATCH			6
#define EXIT_MATCH				7
#define EXIT_SERVER				8

#define PATH "src/users.txt"

#endif /* PROTOCOL_H_ */
