#include "csapp.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_FILENAME 80
#define MAX_SIZE 102400 
#define GET 0
#define PUT 1
#define DELETE 2
#define LIST 3

typedef struct req_struct {
	int key;
	int type;
	char filename[MAX_FILENAME];
	char call[MAX_SIZE];
	uint32_t size;
}req;

typedef struct resp_struct {
	char returns[MAX_SIZE];
	uint32_t status;
	uint32_t size;
}resp;

size_t size_of_req(req* rq)
{
	printf("in size of\n");
	return sizeof(rq)+MAX_FILENAME*sizeof(char)+sizeof(uint32_t)+sizeof(char)*rq->size;
}

int send_request(req * rq, char* host, char *port, resp *rp)
{
	int sock; 
	printf("in send_request\n");
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "Failed to get socket\n"); 
		return -2;
	}
	struct sockaddr *servAddr;
	struct addrinfo socketInfo;
	struct addrinfo *serverInfo;
	memset(&socketInfo, 0, sizeof(socketInfo));

	socketInfo.ai_family = AF_INET;
	socketInfo.ai_socktype = SOCK_STREAM;
	getaddrinfo(host, port, &socketInfo, &serverInfo);
	servAddr = serverInfo->ai_addr;
	printf("here1\n");
	connect(sock, servAddr, sizeof(*servAddr));
	printf("here2\n");
	send(sock, rq, size_of_req(rq), 0);
	printf("here3\n");
	if(read(sock, rp, MAX_SIZE) < 0 )
	{
		printf("Failed to connect\n");
		return -1;
	}	
	printf("made it here\n");

	if(rp->status == 1)
	{
		close(sock);
		printf("error\n");
	}
	if(rp->size > 0)
	{
		printf("%s\n", rp->returns);
	}
	close(sock);
	freeaddrinfo(serverInfo);
	printf("request sent successfully\n");
	return 0;
}

int get_rq (char *in)
{
	if(strncmp(in, "get", 3) == 0)
	{
		printf("in get\n");	
		return GET; 	
	}
	else if(strncmp(in, "put", 3) == 0)
	{	return PUT;	}
	else if(strncmp(in, "del", 3) == 0 || strncmp(in, "rm", 2)== 0)
	{	return DELETE;	}
	else if(strncmp(in, "list", 4) == 0)
	{	return LIST;	}
	return -1;
}


int main(int argc, char **argv)
{
	char *port;
	char *host;
	//rio_t rio;
	
	if(argc < 5) 
	{
		fprintf(stderr, "usage: %s <request> <host> <port> <secret_key> (<file>)\n", argv[1]);
		exit(0);
	}
	req rq;
	resp rp;
	rq.size = 0;
	
	host = argv[2];
	port = argv[3];
	rq.key = atoi(argv[4]);
	rq.type = get_rq(argv[1]);

	send_request(&rq, host, port, &rp);
//	clientfd = Open_clientfd(host,port);
	
	//Rio_readinitb(&rio, clientfd);


	exit(0);
}
	
