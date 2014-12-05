#include "csapp.h"

/* usage: ./MyCloudClient host port */
int main(int argc, char **argv)
{
	int clientfd, port;
	char *host, buf[MAXLINE];
	rio_t rio;

	host = argv[1];
	port = atoi(argv[2]);

	clientfd = Open_clientfd(host,port);
	Fgets(buf, MAXLINE, stdin);
	printf("do stuff\n");
	
	Close(clientfd);
	exit(0);
}
	
