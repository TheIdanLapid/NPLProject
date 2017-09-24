/*
 * TCPMSNClientCLI.cpp
 *
 *  Created on: Jun 19, 2017
 *      Author: user
 */




/*
 * main.cpp
 *
 *  Created on: Jun 19, 2017
 *      Author: user
 */


#include <iostream>
#include "TCPMSNClient.h"
#include "CLIHandler.h"
using namespace std;
using namespace networking;

int main() {
	CLIHandler* handler = new CLIHandler();
	cout << "TCPMSNClientCLI: Welcome to Messenger!" << endl;
	TCPMSNClient* client = new TCPMSNClient(handler);
	string command;
	client->connect("127.0.0.1");
	cout<<"TCPMSNClientCLI: "<<client->getPort()<<endl;
	while (true){
//		command = "";
		cout << "TCPMSNClientCLI: Please enter a command:" << endl;
		cin >> command;
		if (command == "c") {
			string ip;
			cout << "TCPMSNClientCLI: Enter the server's ip:" << endl;
			cin >> ip;
			client->connect(ip);
//			sleep(2);
//			cout<<"TCPMSNClientCLI: "<<client->getPort()<<" #1"<<endl;

		} else if (command == "o") {
			//TODO:להחזיר את ה3 הערות מתחת שלא יהיו הערות=uncomment 3 lines below
//			cout << "TCPMSNClientCLI: Please enter the peer's ip:" << endl;
//			string ip;
//			cin >> ip;
			cout << "TCPMSNClientCLI: Please enter the peer's port:" << endl;
			int port;
			cin >> port;
			client->openSession("127.0.0.1",port); //put "ip" instead of "127.0.0.1"

		} else if (command == "s") {
			cout << "TCPMSNClientCLI: Please enter a message:" << endl;
			string msg;
			cin >> msg;
			//getline(std::cin, msg);
			client->sendMessage(msg);
		}

		else if (command == "cs") {
			client->closeSession();
		}

		else if (command == "d") {
			client->disconnect();
		}

		else if (command == "x") {
			cout<<"TCPMSNClientCLI: Bye!"<<endl;
			break;
		}
	}
	return 0;

}


