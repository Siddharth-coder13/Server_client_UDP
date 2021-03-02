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

		cerr<< "Missing port number.....\n";
		exit(0);

	}
	int port = atoi(argv[1]);
	char msg[1500];

	//define sockaddr_in for server socket
	sockaddr_in serverSocket;

	serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

    //socket() initializing
    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocketID < 0){

        cerr<< "Not successfull socket...\n";
        exit(0);

    }

    //bind socket to the port
    int bindPort = bind(serverSocketID, (struct sockaddr*) &serverSocket, sizeof(serverSocket));
    if(bindPort < 0){

    	cerr<< "Not successfull bind...\n";
    	exit(0);

    }
    cout<<"Waiting for client to connect...\n";

    //listen to socket
    listen(serverSocketID, 1);

    //define a new socket for connection
    sockaddr_in newSocket;
    socklen_t newsocketLen = sizeof(newSocket);

    //accept request from client
    int newSocketID = accept(serverSocketID, (sockaddr *) &newSocket, &newsocketLen);

    if(newSocketID < 0){

    	cerr<< "Not successfull accept().....\n";
    	exit(0);

    }

    cout<< "client connected successfully...\n";

    //send and receive data
    while(1){

        cout<<"Waiting for message from client...\n";

        recv(newSocketID, (char*)&msg, sizeof(msg), 0);

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
        send(newSocketID, (char*) &msg, sizeof(msg), 0);

    }

    //close the socket
    close(newSocketID);
    close(serverSocketID);
    

    

	return 0;
}