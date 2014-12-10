#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "mycloudlib.h"
#include "reqresp.h"

/*int send_request(ReqResp * rq, char* host, char *port, int *key, ReqResp *rp)
{
	int sock;
	struct addrinfo socketInfo;
        struct addrinfo *p;
        struct addrinfo *serverInfo;

        memset(&socketInfo, 0, sizeof(struct addrinfo));
 
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "Failed to get socket\n"); 
		return -2;
	}

	socketInfo.ai_family = AF_INET;
	socketInfo.ai_socktype = SOCK_STREAM;
	socketInfo.ai_flags = 0;
	socketInfo.ai_protocol = 0;

	if(getaddrinfo(host, port, &socketInfo, &serverInfo)!= 0){
		fprintf(stderr, "Hostname failed.\n");
		return -4;
	}
	for(p = serverInfo; p!=NULL; p=p->ai_next)
	{
		if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol))== -1)
		{
			perror("server: socket");
			continue;
		}
	
	
//	printf("here1\n");
		if(connect(sock, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sock);
			fprintf(stderr, "Server connection failed.\n");
			continue;	
		}
	}

	if(rq->type == STORE)
	{
		mycloud_putfile(host, port, key, rq->filename, rq->soul, rq->size);
				
	}
*	send(sock, rq, size_of_ReqResp(rq), 0);
	if(read(sock, rp, MAX_SIZE) < 0) {
		close(sock);
		return -4;
	}
*/
	//handle_response(rp);

/*	if(rp->status == 1)
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
}*/
/*int response_check(ReqResp * rq, ReqResp * rp)
{
	
	if(rp->type == GET || rp->type == LIST)
	{
		if(rp->size > 0)
		{
			return 0;	
		}
		return -1;
	}
	if(rp->type == STORE)
	{
		if((rp->size > 0) && (strcmp(rp->soul, rq->soul) == 0));
		{
			return 0;
		}
		return -1;
	}
	if(rp->type == DELETE)
	{
		int i; 
		for(i = 0; i < MAX_NUM_FILES; i++)
		{
			if(files[i].filename == rq->filename);
			{
				return -1;
			}
		}
		return 0; 
	}
}*/


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
	ReqResp rq;
	ReqResp rp;
	rq.size = 0;
	
	host = argv[2];
	port = argv[3];
	rq.key = atoi(argv[4]);
	rq.type = get_rq(argv[1]);
	
	if(rq.type == LIST)
	{
		if(argc != 5)
		{
			fprintf(stderr, "usage: %s <request> <host> <port> <secret_key> (<file>)\n", argv[1]);
	        	exit(0);

		}
	}
	else
	{
		if(argc != 6)
		{
			fprintf(stderr, "usage: %s <request> <host> <port> <secret_key> (<file>)\n", argv[1]);
                        exit(0);
		}
		strncpy(rq.filename, argv[5], MAX_FILENAME);
	}


	if(rq.type == STORE)
	{
		rq.size = fread(rq.soul, sizeof(char), MAX_SIZE, stdin);
		rq.soul[rq.size] = 0;	
		rq.size = rq.size +1;
	}

	
	if (send_request(&rq, host, port, rq.key, &rp) < 0) 
	{
		exit(-1);
	
	}
	if(rp.size > 0)
	{
		printf("%s\n", rp.soul);
	}
	if(rp.type == LIST)
	{
		printf("%s\n", list);
	}
	exit(0);
}
	
