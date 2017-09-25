/*
 * Dispatcher.cpp
 *
 *  Created on: Sep 24, 2017
 *      Author: user
 */

#include "Dispatcher.h"
using namespace std;

Dispatcher::Dispatcher(DispatcherHandler* handler) {
	this->handler = handler;
	this->peersOn = false;
	this->closed = false;
	this->peers = new MTCPListener();
	this->waitingPeers = new MTCPListener();
	mutex = PTHREAD_MUTEX_INITIALIZER;
	peeread = false;
	tcpMap = new map<TCPSocket*, User*>();
	fm = new FileManager();
	um = new UserManager(fm);
}

//bool Dispatcher::removePeer(TCPSocket* peer){
//	if (peer==NULL)
//	{
//		cout<<"Dispatcher: PEER IS NULL!"<<endl;
//		return false;
//	}
//	int i = 0;
//	tSockets::iterator iter = peers->sockets.begin();
//	for(;iter!= peers->sockets.end();iter++)
//	{
//		if (*iter!=NULL)
//		{
//			TCPSocket* curr = *iter;
////			cout<<curr<<"Dispatcher: is the current socket with port: "<<curr->getPort()<<endl;
//			if(curr->getIP()==peer->getIP() && curr->getPort()==peer->getPort()){
////				cout<<"Dispatcher: Peer index to delete: "<<i<<endl;
//				cout<<"Dispatcher: Peer to delete: "<<peers->sockets[i]->getPort()<<endl;
//				Guard guard(&mutex);
//				peers->sockets.erase(peers->sockets.begin()+i);
//				if(peers->sockets.size()==0){
//					peersOn = false;
//				}
//				return true;
//			}
//			i++;
//		}
//		else
//		{
//			cout<<"Dispatcher: iter null"<<endl;
//		}
//	}
//	return false;
//
//}


void Dispatcher::addPeer(TCPSocket* sock){
//	waitForThread();
	Guard guard(&mutex);
//	User* user = new User();
//	user->setTcp(sock);
//	um->getUnknownUsers().push_back(user); //Add to waiting users vector
	waitingPeers->add(sock); //Add to waiting sockets vector
//	tcpMap.insert(make_pair(sock,user)); //Add to map
	cout<<"Dispatcher: Added peer to waitingPeers list with port: "<<sock->getPort()<<endl;
}

void Dispatcher::run(){
	while(!closed){
	//		cout<<"Dispatcher: size of peers: "<<peers->sockets.size()<<endl;
			MTCPListener mtcp;

			mtcp.addAll(peers->sockets);
			mtcp.addAll(waitingPeers->sockets);

			peers->sockets.clear();
			waitingPeers->sockets.clear();

			//now we update the original peers list

			peers->sockets = mtcp.sockets;

	//		if (peersOn&& !peeread){
				TCPSocket* peer = mtcp.listen(4);

				if(!peer){ //timeout without any peer ready
	//				cout<<"Dispatcher: there is no ready peer"<<endl;
					continue;
				}
			else
			{
				cout<<"Dispatcher: peer: "<<peer->getPort()<<" is now connected!"<<endl;
				int command = readCommand(peer);
//				cout<<"Dispatcher: COMMAND FROM PEER:"<<command<<endl;
				if(command>0){
//					cout<<"Dispatcher: GOT COMMAND FROM PEER"<<endl;
					peeread = true;
				}
				int len = 0;
				char buff[100];
				int rc = 0;
				string data;

				string name;
				string pass;

				User *user, *user2,*user3,*u,*opp,*opp2;
				Guard guard(&mutex);

				int success;
				switch(command){

				case REGISTER:
					rc = peer->recv((char*)&len,4); //recv msg length
					if(rc<0){
						cerr<<"Dispatcher: Fail to read command from socket"<<endl;
					}
					len = ntohl(len);
					rc = peer->recv(buff,len); //recv msg
					if(rc<0){
						cerr<<"Dispatcher: Fail to read command from socket"<<endl;
					}
					buff[len] = '\0';
					data = buff;

					name = data.substr(0,data.find_first_of(":"));
					pass = data.substr(data.find_first_of(":") + 1);

					um->registerUser(name,pass);
					break;

				case LOGIN:
					rc = peer->recv((char*)&len,4); //recv msg length
					if(rc<0){
						cerr<<"Dispatcher: Fail to read command from socket"<<endl;
					}
					len = ntohl(len);
					rc = peer->recv(buff,len); //recv msg
					if(rc<0){
						cerr<<"Dispatcher: Fail to read command from socket"<<endl;
					}
					buff[len] = '\0';
					data = buff;

					name = data.substr(0,data.find_first_of(":"));
					pass = data.substr(data.find_first_of(":") + 1);

					success = um->loginUser(name,pass);
					if (success == 0) {
						cout<<"LOGIN SUCCESS"<<endl;
						user = new User(name,pass);
						user->setTcp(peer);
						user->setLoggedIn(true);
						tcpMap->insert(make_pair(peer,user));
					}
					break;

				case SHOW_USERS:
					printLoggedUsers(peer);
					break;


				case OPEN_MATCH_RANDOM:
					user2 = getUserFromTCPMap(peer);
					if (user2 != NULL) {
						if (tcpMap->size()==1) {
							cout<<"You're all alone! Wait for more players to join!"<<endl;
							break;
						}

						//If one or more of the players is already in the game
						if (user2->isOnGame() || opp->isOnGame()) {
							cerr<<"You or your opponent are already in a game!!! Exit the game first!"<<endl;
							break;
						}

						opp = tcpMap->begin()->second;
						if (opp->getName()==user2->getName()) { //The same user
							opp = (tcpMap->begin()++)->second;
							user2->setUdp(new UDPSocket());
							opp->setUdp(new UDPSocket(3435)); //Random udp port
							handler->openGameSession(user2,opp);
						}
						else {
							user2->setUdp(new UDPSocket());
							opp->setUdp(new UDPSocket(3435)); //Random udp port
							handler->openGameSession(user2,opp);
						}
					}
					break;

				case OPEN_MATCH_WITH_USER:
					//CHECK IF LOGGED IN
					user3 = getUserFromTCPMap(peer);

					if (user3 != NULL) {
						rc = peer->recv((char*)&len,4); //recv msg length
						if (rc<0){
							cerr<<"Dispatcher: Fail to read command from socket"<<endl;
						}
						len = ntohl(len);
						rc = peer->recv(buff,len); //recv msg
						if (rc<0){
							cerr<<"Dispatcher: Fail to read command from socket"<<endl;
						}
						buff[len] = '\0';
						name = buff;
						//Search the map for the opp's name

						map<TCPSocket*, User*>::iterator pos;
						for (pos = (*tcpMap).begin(); pos != (*tcpMap).end(); ++pos) {
							u = pos->second;
							if(u->getName()==name)
								opp2 = u;
						}
						if (opp2 == NULL) {
							cerr<<"Opponent's name not found!";
							break;
						}

						user3->setUdp(new UDPSocket());
						opp2->setUdp(new UDPSocket(3435));
						handler->openGameSession(user3,opp2);
					} //if
				break;
			} //switch
		} //else
		cout<<"Dispatcher: !closed"<<endl;
	} //while
	cout<<"Dispatcher: End of dispatcher run loop"<<endl;
}

void Dispatcher::printLoggedUsers(TCPSocket* peer) {
	waitForThread();
	cout<<"Printing logged in users: "<<endl;
//	map<TCPSocket*, User*>::iterator pos;
	map<TCPSocket*, User*>::iterator pos;
	cout<<"MAP SIZE: "<<tcpMap->size()<<endl;
	for (pos = (*tcpMap).begin(); pos != (*tcpMap).end(); ++pos) {
		User* user = pos->second;
		cout<<user->getName()+'\n'<<endl;
//		cout << "key: " << pos->first << " values: pass: " << pos->second.first << " score: " <<pos->second.second << endl;
		int res = peer->write((char*)&user->getName()+'\n',sizeof(user->getName())+1);

		if (res<4) {
			cout<<"Dispatcher: Could not print name! "<<endl;
		}
	}
}

int Dispatcher::readCommand(TCPSocket* peer){
	int rcvCmd = 0;
	int rc = peer->recv((char*)&rcvCmd,4);
	if(rc!=4){
		cerr<<"Dispatcher: fail to read command from peer"<<endl;
		return -1;
	}
	return ntohl(rcvCmd);
}

User* Dispatcher::getUserFromTCPMap(TCPSocket* sock) {
	map<TCPSocket*, User*>::iterator iter;
	iter = tcpMap->find(sock);
	if(iter != (*tcpMap).end()) {
		User* user = new User(iter->second);
		return user;
	}
	else {
		cerr<<"getUserFromTCPMap: No such user"<<endl;
		return NULL;
	}
}

Dispatcher::~Dispatcher() {
	// TODO Auto-generated destructor stub
}

/*



void Dispatcher::run(){
	//while(peersOn){
//	bool peeread = false; //make sure the command is read only one time
//	while (peersOn&& !peeread){
	while(!closed){
//		cout<<"Dispatcher: size of peers: "<<peers->sockets.size()<<endl;
		MTCPListener mtcp;

		mtcp.addAll(peers->sockets);
		mtcp.addAll(waitingPeers->sockets);

		peers->sockets.clear();
		waitingPeers->sockets.clear();

		//now we update the original peers list

		peers->sockets = mtcp.sockets;

//		if (peersOn&& !peeread){
			TCPSocket* peer = mtcp.listen(4);

			if(!peer){ //timeout without any peer ready
//				cout<<"Dispatcher: there is no ready peer"<<endl;
				continue;
			}
			else
			{
				cout<<"Dispatcher: peer: "<<peer->getPort()<<" is now connected!"<<endl;
				int command = readCommand(peer);
//				cout<<"Dispatcher: COMMAND FROM PEER:"<<command<<endl;
				if(command>0){
//					cout<<"Dispatcher: GOT COMMAND FROM PEER"<<endl;
					peeread = true;
				}
				int len = 0;
				string ip;
				char buff[100];
				int rc = 0;
				int port = 0;
				string data;
				switch(command){

				case OPEN_SESSION_WITH_PEER:
					cout<<"Dispatcher: Got open session command"<<endl;
					waitForThread();
//					cout<<"Dispatcher: Done waiting!"<<endl;
					rc = peer->recv((char*)&len,4); //recv msg length
					if(rc<0){
						cerr<<"Dispatcher: Fail to read command from socket"<<endl;
					}
					len = ntohl(len);
					rc = peer->recv(buff,len); //recv msg
					if(rc<0){
						cerr<<"Dispatcher: Fail to read command from socket"<<endl;
					}
					buff[len] = '\0';
					data = buff;


					ip = data.substr(0,data.find_first_of(":"));
					port = atoi((data.substr(data.find_first_of(":") + 1)).c_str());
					int index = getPeerIndex(ip,port);
					if(index!=-1){
						int com = handler->managePeerSession(peer,peers->sockets[index]);
						if(com==SESSION_ESTABLISHED){
							cout<<"Dispatcher: SESSION_ESTABLISHED"<<endl;
							sendFeedback(peer,6);
							removePeer(peer); //remove the peer that requested to open session
							sendFeedback(peers->sockets[index],6);
							removePeer(peers->sockets[index]);//remove the other peer
						}
						else if(com==SESSION_REFUSED){
							cout<<"Dispatcher: SESSION_REFUSED"<<endl;
							sendFeedback(peer,5);
						}
					}
					else
					{
						cout<<"Dispatcher: Peer not found!"<<endl;
						sendFeedback(peer,5);
					}
					break;
				}
			}
//		}
//		cout<<"Dispatcher: !closed"<<endl;
	}
	cout<<"Dispatcher: End of dispatcher run loop"<<endl;
}
int Dispatcher::getPeerIndex(string ip,int port){
	return peers->getSocketIndex(ip,port);
}

int Dispatcher::sendFeedback(TCPSocket* peer, int command){
	int cmdNet = htonl(command);
	int res = peer->write((char*)&cmdNet,4); //the command int from the protocol

	if (res<4)
	{
		cout<<"Dispatcher: Could not send feedback! "<<command<<endl;
		return -1;
	}
	return res;
}

int Dispatcher::readCommand(TCPSocket* peer){
	int rcvCmd = 0;
	int rc = peer->recv((char*)&rcvCmd,4);
	if(rc!=4){
		cerr<<"Dispatcher: fail to read command from peer"<<endl;
		return -1;
	}
	return ntohl(rcvCmd);
}

void Dispatcher::close(){
	closed = true;
	Guard guard(&mutex);
	if(!peers->sockets.empty())
		peers->sockets.clear();
}
a
Dispatcher::~Dispatcher() {
	cout<<"Dispatcher: Dispatcher closed!"<<endl;
}

*/
