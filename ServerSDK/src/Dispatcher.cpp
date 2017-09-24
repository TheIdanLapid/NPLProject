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
	this->peers = new MultipleTCPSocketsListener();
	this->peersOn = false;
	this->closed = false;
	this->waitingPeers = new MultipleTCPSocketsListener();
	mutex = PTHREAD_MUTEX_INITIALIZER;
	peeread = false;

	fm = new FileManager();
	um = new UserManager(fm);
}

bool Dispatcher::removePeer(TCPSocket* peer){
	if (peer==NULL)
	{
		cout<<"Dispatcher: PEER IS NULL!"<<endl;
		return false;
	}
	int i = 0;
	tSockets::iterator iter = peers->sockets.begin();
	for(;iter!= peers->sockets.end();iter++)
	{
		if (*iter!=NULL)
		{
			TCPSocket* curr = *iter;
//			cout<<curr<<"Dispatcher: is the current socket with port: "<<curr->getPort()<<endl;
			if(curr->getIP()==peer->getIP() && curr->getPort()==peer->getPort()){
//				cout<<"Dispatcher: Peer index to delete: "<<i<<endl;
				cout<<"Dispatcher: Peer to delete: "<<peers->sockets[i]->getPort()<<endl;
				Guard guard(&mutex);
				peers->sockets.erase(peers->sockets.begin()+i);
				if(peers->sockets.size()==0){
					peersOn = false;
				}
				return true;
			}
			i++;
		}
		else
		{
			cout<<"Dispatcher: iter null"<<endl;
		}
	}
	return false;

}


void Dispatcher::addPeer(TCPSocket* sock){
	Guard guard(&mutex);
//	User* user = new User();
//	user->setTcp(sock);
//	um->getUnknownUsers().push_back(user); //Add to waiting users vector
	waitingPeers->addSocket(sock); //Add to waiting sockets vector
//	tcpMap.insert(make_pair(sock,user)); //Add to map
	cout<<"Dispatcher: Added peer to waitingPeers list with port: "<<sock->getPort()<<endl;
}

void Dispatcher::run(){
	while(!closed){
//		cout<<"Dispatcher: size of peers: "<<peers->sockets.size()<<endl;
		MultipleTCPSocketsListener mtcp;

		mtcp.addSockets(peers->sockets);
		mtcp.addSockets(waitingPeers->sockets);

		peers->sockets.clear();
		waitingPeers->sockets.clear();

		peers->sockets = mtcp.sockets; //now we update the original peers list

			TCPSocket* peer = mtcp.listenToSocket(4);

			if(!peer) { //timeout without any peer ready
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

				int success;
				switch(command){

				case REGISTER :
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

				case LOGIN :
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
//					if (success == -2) {
//
//					}
//					else if (success == -1) {
//
//					}
//					else {
//
//					}
					if (success == 0) {
						User* user = new User(name,pass);
						user->setTcp(peer);
						user->setLoggedIn(true);
						tcpMap.insert(make_pair(peer,user));
					}
					break;
				case SHOW_USERS:
					printLoggedUsers(peer);
					break;
//				case OPEN_MATCH_WITH_USER:
//					//CHECK IF LOGGED IN
//
//
//					cout<<"Dispatcher: Got open session command"<<endl;
//					waitForThread();
////					cout<<"Dispatcher: Done waiting!"<<endl;
//					rc = peer->recv((char*)&len,4); //recv msg length
//					if(rc<0){
//						cerr<<"Dispatcher: Fail to read command from socket"<<endl;
//					}
//					len = ntohl(len);
//					rc = peer->recv(buff,len); //recv msg
//					if(rc<0){
//						cerr<<"Dispatcher: Fail to read command from socket"<<endl;
//					}
//					buff[len] = '\0';
//					data = buff;
//
//
//					ip = data.substr(0,data.find_first_of(":"));
//					port = atoi((data.substr(data.find_first_of(":") + 1)).c_str());
//					int index = getPeerIndex(ip,port);
//					if(index!=-1){
//						int com = handler->managePeerSession(peer,peers->sockets[index]);
//						if(com==SESSION_ESTABLISHED){
//							cout<<"Dispatcher: SESSION_ESTABLISHED"<<endl;
//							sendFeedback(peer,6);
//							removePeer(peer); //remove the peer that requested to open session
//							sendFeedback(peers->sockets[index],6);
//							removePeer(peers->sockets[index]);//remove the other peer
//						}
//						else if(com==SESSION_REFUSED){
//							cout<<"Dispatcher: SESSION_REFUSED"<<endl;
//							sendFeedback(peer,5);
//						}
//					}
//					else
//					{
//						cout<<"Dispatcher: Peer not found!"<<endl;
//						sendFeedback(peer,5);
//					}
//					break;
				}
			}
//		}
//		cout<<"Dispatcher: !closed"<<endl;
	}
	cout<<"Dispatcher: End of dispatcher run loop"<<endl;
}

void Dispatcher::printLoggedUsers(TCPSocket* peer) {
	map<TCPSocket*, User>::iterator pos;
	for (pos = tcpMap.begin(); pos != tcpMap.end(); ++pos) {
//		cout << "key: " << pos->first << " values: pass: " << pos->second.first << " score: " <<pos->second.second << endl;
		int res = peer->write((char*)&pos->first+'\n',sizeof(pos->first)+1);

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

Dispatcher::~Dispatcher() {
	cout<<"Dispatcher: Dispatcher closed!"<<endl;
}

*/
