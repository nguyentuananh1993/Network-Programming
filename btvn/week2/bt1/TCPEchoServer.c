#include <stdio.h> // for printf() and fprintf();
#include <sys/socket.h>	// for socket(), bind(), and connect();
#include <arpa/inet.h>	// for sockaddr_in and inet_ntoa();
#include <stdlib.h> // for atoi();
#include <string.h> // for memset();
#include <unistd.h> // for close();
#include "DieWithError.c"
#include "HandleTCPClient.c"
#define MAXPEDING 5 // maximum outstanding connection request;
int check=0; // check value
void HandleTCPClient(int clntSocket);// tcp client handling function

int main(int argc, char * argv[]){
	int servSock;	// socket descriptor for server
	int clntSock;	// socket descriptor for client
	struct sockaddr_in echoServAddr;	// local address
	struct sockaddr_in echoClntAddr;	// client address
	unsigned short echoServPort;		// server port
	unsigned int clntLen;				// length of client address data structure
	if(argc!=2){	//test for correct number of arguments
		fprintf(stderr,"Usage: %s <ServerPort> \n",argv[0]);
		exit(1);
	}	

	echoServPort = atoi(argv[1]);	//first arg: local port

	/*create socket for incomming connections*/
	if((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
		DieWithError("Socket() failed");

	/*Construct local address structure*/
	memset(&echoServAddr,0,sizeof(echoServAddr)); // zero out structure
	echoServAddr.sin_family = AF_INET; // internet address family
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); //any incomming interface
	echoServAddr.sin_port = htons(echoServPort);	// local port

	if(bind(servSock,(struct sockaddr *) &echoServAddr,sizeof(echoServAddr))<0)
		DieWithError("bind() failed");

	/*Mark the socket so it will listen for incomming connections */
	if(listen(servSock,MAXPEDING)<0)
		DieWithError("listen() failed");
	for(;;){// run forever
		/*set the size of the in-out parameter*/
		clntLen = sizeof(echoClntAddr);
		/* wait for a client to connect */
		printf("Session: %d.\n",check++);
		if((clntSock = accept(servSock,(struct sockaddr *) &echoClntAddr,&clntLen))<0)
			DieWithError("accept() failed");
		/* clntSock is connected to a cdlient! */
		printf("Handling client %s\n",inet_ntoa(echoClntAddr.sin_addr));

		HandleTCPClient(clntSock);
	}
}