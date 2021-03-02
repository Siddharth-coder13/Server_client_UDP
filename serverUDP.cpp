#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){

	if(argc != 2){

		cout<< "Missing port number "<<argc<<endl;
		exit(0);

	}

	int port = atoi(argv[1]);
	char msg[1500];

	//create sockaddr_in structure
	sockaddr_in serverSocket;
	serverSocket.sin_family = AF_INET;
	serverSocket.sin_port = htons(port);
	serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

	//initalize socket
	int serverSocketID = socket(AF_INET, SOCK_DGRAM, 0);
	if(serverSocketID < 0){

		cout<<"error initalizing socket\n";
		exit(0);

	}

	//bind the socket to server
	int bindport = bind(serverSocketID, (struct sockaddr*)&serverSocket, sizeof(serverSocket));
	if(bindport < 0){

		cout<<"error binding\n";
		exit(0);

	}


	//client socket structure
	sockaddr_in clientSocket;
	socklen_t len = sizeof(clientSocket);

	cout<<"waiting for message from client...\n";

	while(1){

		recvfrom(serverSocketID, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&clientSocket, &len);
		if(!strcmp(msg, "exit")){

        	cout<<"Session terminated...\n";
        	break;
        }
        cout<<msg<<endl;

        string data;
        cin>>data;
        strcpy(msg, data.c_str());
        if(data == "exit"){

        	cout<<"Session terminated...\n";
        	break;
        }
        sendto(serverSocketID, (char*)&msg, sizeof(msg), 0, (sockaddr*)&clientSocket, len);


	}

	//close the socket
	close(serverSocketID);


	return 0;
}