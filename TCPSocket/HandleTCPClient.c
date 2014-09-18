#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#define RCVBUFSIZE 32

void HandleTCPClient(int clntSocket){
	char echoBuffer[RCVBUFSIZE];	// buffer for echo string
	int recvMsgSize;				// size of received message

	//recieve message from client
	if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0))<0)
		DieWithError("recv() failed");
	// send recieved string and receive again until end of transmission
	while(recvMsgSize > 0){
		//echo message back to client
		if(send(clntSocket,echoBuffer,recvMsgSize,0)!= recvMsgSize)
			DieWithError("send() failed");

		// see if there is more data to receive
		if((recvMsgSize = recv(clntSocket,echoBuffer,RCVBUFSIZE,0))<0)
			DieWithError("recv() failed");
	}
	close(clntSocket);
}