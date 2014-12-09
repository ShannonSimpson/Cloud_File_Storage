/********************************************
* The server loops endlessly		    *
* waiting for a connection request	    *
* It then reads input from the client and   *
* echo the input back to the client.        *
* 					    *
* Mycloud Server:			    *
* A mycloud server that accepts requests to *
* store a file, retrieve a file, delete a   *
* file, and list the files stored on the    *
* server.				    *
********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "reqresp.h"

#define MAX_PENDING 5
#define GOOD 0
#define BAD 1

void printOut(ReqResp * rq)
{
	printf("Secret Key = %d\n", rq->key);
	printf("Request Type = %c\n", get_name(rq->type));
	if(rq->type != LIST)
	{
		printf("Filename = %c\n", rq->filename);
	}
	else
	{
		printf("Filename = NONE\n");
	}
}

void executeReq(int connfd, int key)
{
	bool complete = false;
	ReqResp rq;
	ReqResp rp;

	rp.status = GOOD;
	rp.size = 0; 

	size_t recieved;
	if((recieved = recv(connfd, &rq, sizeof(ReqResp), 0)) != 0)
	{
		if(rq.type == GET)
		{
			complete = TRUE;
			
		}
		else if(rq.type == PUT)
		{
			complete = TRUE;
		}
		else if(rq.type == DELETE)
		{
			complete = TRUE;
		}
		else if(rq.type == LIST)
		{
			complete = TRUE;
		}
	}
	printOut(&rq);
	if(complete == false)
	{
		printf("Operation Status = Error\n");
	}
	else if(complete == true)
	{
		printf("Operation Status = Success\n");
		complete = false;
		send(connfd, &rp, get_size(rp), 0)
	{
	printf("------------------------------------\n")
	
	
}
int main(int argc, char **argv) {
	// create and configure the listening socket
	int listenfd, connfd, port, key;	
	socklen_t client_length;
	struct sockaddr_in clientaddr;
	struct sockaddr_in serveraddr;
	struct hostent *hp;
	char *haddrp;
	unsigned short client_port;

	if(argc != 3) {
		fprintf(stderr, "usage: %s <port> <key>\n", argv[0]);
		exit(0);	
	}

	port = atoi(argv[1]); /* the server listens on a port passed on the command line */
	key = atoi(argv[2]);

	if((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf(stderr, "Nope. No socket obtained.\n");
		exit(-1);
	}
//	listenfd = open_listenfd(port);

	memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	//ALL THE SINS
	serveraddr.sin_family = AF_INET;	
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(port);

	if(bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
		printf("Could not bind to port, sir.\n");
		exit(-2);
	}
	
	if(listen(listenfd, MAX_PENDING) < 0) {
		printf(stderr, "Listening(...) Call failed. Hanging up now.\n");
		exit(-4);
	}

	//init_storage
	// Begin the WHILE loop here
	client_length = sizeof(clientaddr);

	//wait for the connection request
	connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &client_length);
	if(connfd <0) {
		printf(stderr, "Accept(...) call failed.\n");
		exit(-3);
	}
	/* I really don't think there is a point to this chunk.
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
	sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);  //determining the IP Address?
	client_port = ntohs(clientaddr.sin_port);  //determining the Port?
	printf("server connected to %s (%s), port %u\n",
	hp->(h_name, haddrp, client_port);
	// read and reach input lines from client until the EOF
	echo(connfd);
	*/
	
	serve(connfd, key);

	// close the connection
	Close(connfd);
	
	//end the WHILE loop here
		
//	exit(0);
} 
