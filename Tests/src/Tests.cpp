
#include <iostream>
using namespace std;
#include "FileManager.h"
#include "User.h"
#include "Protocol.h"
#include <vector>
#include "UserManager.h"
#include "ServerSDK.h"
#include "Dispatcher.h"
#include "Acceptor.h"

using namespace std;

void printMap(FileManager* fm) {
	cout<<"printinggGgggg"<<endl;
	uMap* map = fm->getUsersMap(); //uMap is defined in Protocol.h as: map<string,pair<string,int> >
	uMap::iterator pos;
	for (pos = (*map).begin(); pos != (*map).end(); ++pos) {
		cout << "key: " << pos->first << " values: pass: " << pos->second.first << " score: " <<pos->second.second << endl;
	}
}

int main() {

//	FileManager* fm = new FileManager();
//	fm->clearFile();
//
//	User user;
//	UserManager* um = new UserManager(fm);
//	user.setName("Idan");
//	user.setPass("sisma1");
//	user.setScore(2);
//	fm->writeUser(user);
//	cout<<"Finished writing "<<user.getName()<<endl;
//
//	User shdema;
//	shdema.setName("Shdema");
//	shdema.setPass("sisma2");
//	shdema.setScore(56);
//	fm->writeUser(shdema);
//	cout<<"Finished writing "<<shdema.getName()<<endl;

//	fm->readUsers();
//	printMap(fm);
//	uMap* map = fm->getUsersMap(); //uMap is defined in Protocol.h as: map<string,pair<string,int> >
//	uMap::iterator pos;
//	for (pos = (*map).begin(); pos != (*map).end(); ++pos) {
//		cout << "key: " << pos->first << " values: pass: " << pos->second.first << " score: " <<pos->second.second << endl;
//	}




	ServerSDK* server = new ServerSDK();
	server->start();
	sleep(2);
	TCPSocket* socket = new TCPSocket(IP,SERVER_PORT);
//	server->handlePeer(socket);
//	string name = "Rotem";
//	string pass = "Lapid";
//	server->dispatcher->um->registerUser(name,pass);
//
//	fm->setScore(shdema,7);
//
//	User user4;
//	user4.setName("Oren");
//	user4.setPass("sisma6");
//	user4.setScore(9);
//	fm->writeUser(user4);
//	cout<<"Finished writing "<<user4.getName()<<endl;
//
//	cout<<um->loginUser("Rotem","Lapid")<<endl;
//	cout<<um->loginUser("Rotem","Lapids")<<endl;
//	cout<<um->loginUser("Rostem","Lapid")<<endl;

	int cmdNet = htonl(1);
	int res = socket->write((char*)&cmdNet,4); //the command int from the protocol
	if (res<4)
		return -1;

	int len = strlen("userrrrr:passsss");
	int lenNet = htonl(len);
	res = socket->write((char*)&lenNet,4); //the length of the message
	if (res<4)
		return -1;
	res = socket->write("userrrrr:passsss",len); //the message
	if (res<4)
		return -1;

	sleep(4);
	server->printUsers(socket);

	while (true){}
	cout<<"End of TEST"<<endl;


	return 0;
}
