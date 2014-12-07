/*******************************************
* The server loops endlessly		   *
* waiting for a connection request	   *
* It then reads input from the client and *
* echo the input back to the client.      *
*******************************************/
int main(int argc, char **argv) {
	// create and configure the listening socket
	int listenfd, connfd, port, clientlen;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;
	unsigned short client_port;

	port = atoi(argv[1]); /* the server listens on a port passed on the command line */

	listenfd = open_listenfd(port);

	// Begin the WHILE loop here
	clientlen = sizeof(clientaddr);

	//wait for the connection request
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,

	sizeof(clientaddr.sin_addr.s_addr), AF_INET);

	haddrp = inet_ntoa(clientaddr.sin_addr);  //determining the IP Address?
	client_port = ntohs(clientaddr.sin_port);  //determining the Port?
	printf("server connected to %s (%s), port %u\n",

	hp->h_name, haddrp, client_port);

	// read and reach input lines from client until the EOF
	echo(connfd);

	// close the connection
	Close(connfd);
	
	//end the WHILE loop here
} 
