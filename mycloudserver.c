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

#define MAX_PENDING 5

void serve(int, int);

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

	memset(&severaddr, 0, sizeof(serveraddr));
	//ALL THE SINS
	serveraddr.sin_family = AF_INET;	
	serveraddr.sin_addr.s_addr = htonl(INADDDR_ANY);
	serveraddr.sin_port = htons(port);

	if(bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
		printf(stderr, ("Listening(...) Call failed. Hanging up now.\n");
		exit(-4);
	}
	
	init_storage();

	// Begin the WHILE loop here
	clientlen = sizeof(clientaddr);

	//wait for the connection request
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,

	sizeof(clientaddr.sin_addr.s_addr), AF_INET);

	haddrp = inet_ntoa(clientaddr.sin_addr);  //determining the IP Address?
	client_port = ntohs(clientaddr.sin_port);  //determining the Port?
	printf("server connected to %s (%s), port %u\n",

	hp->(h_name, haddrp, client_port);

	// read and reach input lines from client until the EOF
	echo(connfd);

	// close the connection
	Close(connfd);
	
	//end the WHILE loop here
} 
