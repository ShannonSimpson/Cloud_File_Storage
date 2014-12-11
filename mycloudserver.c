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
#include <stdbool.h>

#include "reqresp.h"
#include "mycloudlib.h"

#define PENDING 5

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
		fprintf(stderr, "Nope. No socket obtained.\n");
		exit(-1);
	}

	memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	//ALL THE SINS
	serveraddr.sin_family = AF_INET;	
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(port);

	create_storage();
	if(bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
		printf("Could not bind to port, sir.\n");
		exit(-1);
	}
	
	if(listen(listenfd, PENDING) < 0) {
		fprintf(stderr, "Listening(...) Call failed. Hanging up now.\n");
		exit(-1);
	}

	while(1)
	{
		client_length = sizeof(clientaddr);

		//wait for the connection request
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &client_length);
		if(connfd <0) 
		{
			fprintf(stderr, "Accept(...) call failed.\n");
			exit(-1);
		}
		//pass required items to execution stage		
		executeReq(port, key, connfd);
		close(connfd);
	}
	
		
	exit(0);
} 
