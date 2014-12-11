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


int main(int argc, char **argv)
{
	char *port;
	char *host;
	ReqResp rq;
	ReqResp rp;
	
	//handle arguments
	if(argc < 5) 
	{
		fprintf(stderr, "usage: %s <request> <host> <port> <secret_key> (<file>)\n", argv[1]);
		exit(0);
	}
	rq.size = 0;
	
	host = argv[2];
	port = argv[3];
	rq.key = atoi(argv[4]);
	rq.type = get_rq(argv[1]);
	
	if(rq.type == LIST)
	{
		if(argc != 5)
		{
			fprintf(stderr, "usage: %s <request> <host> <port> <secret_key> \n", argv[1]);
	        	exit(0);

		}
	}
	else
	{
		if(argc != 6)
		{
			fprintf(stderr, "usage: %s <request> <host> <port> <secret_key> <file>\n", argv[1]);
                        exit(0);
		}
		strncpy(rq.filename, argv[5], MAX_FILENAME);
	}


	if(rq.type == STORE)
	{
		//get size of request
		rq.size = fread(rq.soul, sizeof(char), MAX_SIZE, stdin);
		// empty soul
		rq.soul[rq.size] = 0;
		//add null terminator	
		rq.size = rq.size + 1;
	}

	//check validity of send_request to server
	if (send_request(&rq, host, port, rq.key, &rp) < 0) 
	{
		exit(-1);
	
	}
	//handle printing on client side for list and get
	if(rq.type == LIST || rq.type == GET)
	{
		if(rp.size > 0)
		{
			printf("%s\n", rp.soul);
		}
	}
	exit(0);
}
	
