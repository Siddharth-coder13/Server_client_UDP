#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <bits/stdc++.h>
using namespace std;


int main(int argc, char* argv[]){


	//get the arguements
	if(argc != 3){

		cout<< "Missing hostname and port number\n";
		exit(0);

	}
	char* serverName = argv[1];
	int port = atoi(argv[2]);
	char msg[1500];

	//get host details
	struct hostent* host = gethostbyname(serverName);

	//construct a socket
	sockaddr_in clientSocket;
	clientSocket.sin_family = AF_INET;
	clientSocket.sin_port = htons(port);
	clientSocket.sin_addr = **  (struct in_addr **)host->h_addr_list;

	//initialize client socket
	int clientSocketID = socket(AF_INET, SOCK_STREAM, 0);

	//connect to remote address
	int status = connect(clientSocketID, (sockaddr *) &clientSocket, sizeof(clientSocket));
	if(status < 0){

		cout<< "error connection....\n";
		exit(0);

	}
	cout<<"Successfull connection\n";
 
    //start sending and recieving msg 
	while(1){


		string data;
		cout<<"client: ";
		cin>>data;
		strcpy(msg, data.c_str());
		if(data=="exit"){

			cout<<"Session terminated\n";
			break;

		}
		send(clientSocketID, msg, sizeof(msg), 0);
		cout<<"server: ";
		recv(clientSocketID, msg, sizeof(msg), 0);
		if(!strcmp(msg, "exit")){

			cout<<"Session terminated\n";
			break;

		}
		cout<<msg<<endl;

	}

	//close socket
	close(clientSocketID);



	return 0;
}