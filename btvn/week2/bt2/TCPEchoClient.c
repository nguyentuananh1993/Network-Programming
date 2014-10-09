#include <stdio.h> /* for printf() and fprintf();*/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "DieWithError.c"
#define RCVBUFSIZE 32
#define MAX 6
void DieWithError(char* errorMessage);

int main(int argc, char* argv[]){
	FILE *input,*output;
	int sock;						//socket descriptor
	struct sockaddr_in echoServAddr;	// echo server address
	unsigned short echoServPort;	// echo server port
	char*servIP;	// server ip address
	char*echoString;	// string to send to echo server
	char echoBuffer[RCVBUFSIZE];	// buffer for echo string
	unsigned int echoStringLen;	// length of string to echo
	int bytesRcvd, totalBytesRcvd;	// bytes read in single recv() and total bytes read
	unsigned int counter=0;
	if((argc<4)|| (argc >5)){	// test for correct number of arguments
		fprintf(stderr,"Usage: %s <Server IP> <File Input> <File Output> [<Echo Port>]\n",argv[0]);
		exit(1);
	}
	echoString=(char*)malloc(sizeof(char)*(MAX+1));
	servIP = argv[1]; //first arg server ip address dotted quad
	//echoString = argv[2]; //second arg:string to echo
  	if ((input = fopen (argv[2],"r"))==NULL){
  		DieWithError("Input file error. Can't open to read.");
  	}
  	if ((output = fopen (argv[3],"w"))==NULL){
  		DieWithError("Output file error. Can't open to write.");
  	}
	if(argc == 5)
		echoServPort = atoi(argv[4]); //use given port, if any
	else
		echoServPort = 7; // 7 is the well-known port for the echo service

	//create a reliable, stream socket using TCP
	if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
		DieWithError("socket() failed");
	// construct the server address structure
	memset(&echoServAddr, 0, sizeof(echoServAddr));	// zero out structure
	echoServAddr.sin_family = AF_INET;	// internet address family
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);//server ip address
	echoServAddr.sin_port = htons(echoServPort); //server port

	//establish the connection to the echo server
	if(connect(sock,(struct sockaddr*) &echoServAddr,sizeof(echoServAddr))<0)
		DieWithError("connect() failed");
	while(fgets (echoString, MAX, input)!=NULL){
		
		echoStringLen = strlen(echoString); //determine input length
		// printf("Sent size: %d bytes.\n",echoStringLen);
		//send the string to the server
		if(send(sock, echoString, echoStringLen, 0) != echoStringLen)
			DieWithError("send() sent a different number of byte than expected");

		//receive the same string back from the server
		totalBytesRcvd = 0;
		// printf("Received: ");	// setup to print the echoed string
		while(totalBytesRcvd <echoStringLen){
			/* Receive up to the buffer size(minus 1 to leave space for a null terminator) bytes form the sender */
			if((bytesRcvd = recv(sock, echoBuffer,RCVBUFSIZE -1, 0))<=0)
				DieWithError("recv() failed or connection closed prematurely");
			totalBytesRcvd +=bytesRcvd;	// keep tally of total bytes
			echoBuffer[bytesRcvd] ='\0'; //terminate the string!
			// printf("%s - %d bytes \n",echoBuffer,bytesRcvd);
		}
		fprintf(output,"%s",echoBuffer);
		counter+=totalBytesRcvd;
	}
	printf("Total Bytes Sent (Receive): %d bytes.\n",counter);
	fclose(input);
	fclose(output);
	printf("\n");//print a final linefeed
	close(sock);
	exit(0);
}