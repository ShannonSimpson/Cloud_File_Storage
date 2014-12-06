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
	
	printf("type:");
	fflush(stdout);
	
	Rio_readinitb(&rio, clientfd);

	Fgets(buf, MAXLINE, stdin);
	//printf("do stuff\n");
	Rio_writen(clientfd, buf, strlen(buf));
	Rio_readlineb(&rio, buf, MAXLINE);
	printf("echo:");
	Fputs(buf, stdout);
	printf("type:");
	fflush(stdout);	

	Close(clientfd);
	exit(0);
}
	
