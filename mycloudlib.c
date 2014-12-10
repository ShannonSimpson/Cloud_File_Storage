#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdio.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#include <string.h>
#include "reqresp.h"
#include "mycloudlib.h"
#define MAX_PENDING 5
#define GOOD 0
#define BAD 1

storage files[MAX_NUM_FILES];


void printOut(ReqResp * rq)
{
        printf("Secret Key = %d\n", rq->key);
        printf("Request Type = %s\n", name_rq(rq->type));
        if(rq->type != LIST)
        {
                printf("Filename = %s\n", rq->filename);
        }
        else
        {
                printf("Filename = NONE\n");
        }
}



void executeReq(char* port, int key, int connfd)
{
        bool complete = false;
        ReqResp rq;
        ReqResp rp;
	if(key == rq.key)
	{
	        rp.status = GOOD;
		rp.size = 0;
       		size_t recieved;
       		if((recieved = recv(connfd, &rq, sizeof(ReqResp), 0)) != 0)
                {
			if(rq.type == GET)
                	{
                        	if(mycloud_getfile(rq.filename, &rp) == 0)
                        	{
                                	complete = true;
                        	}
                	}
                	else if(rq.type == STORE)
                	{	
                        	if(mycloud_putfile(port, key, rq.filename, rq.soul, rq.size) == 0)
                        	{
                                	complete = true;
                        	}
                	}
                	else if(rq.type == DELETE)
                	{
                        	complete = true;
                	}
                	else if(rq.type == LIST)
                	{
                        	complete = true;
                	}
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
                send(connfd, &rp, size_of_ReqResp(&rp), 0);
        }
        printf("------------------------------------\n");


}


int send_request(ReqResp * rq, char* host, char* port, int key, ReqResp *rp)
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


//      printf("here1\n");
                if(connect(sock, p->ai_addr, p->ai_addrlen) == -1)
                {
                        close(sock);
                        fprintf(stderr, "Server connection failed.\n");
                        continue;
                }
        }

	send(sock, rq, size_of_ReqResp(rq), 0);

//	executeReq(&host, port, connfd, key);
/*      send(sock, rq, size_of_ReqResp(rq), 0);
        if(read(sock, rp, MAX_SIZE) < 0) {
                close(sock);
                return -4;
        }
*/
        //handle_response(rp);

/*      if(rp->status == 1)
        {
                close(sock);
                printf("error\n");
        }
        if(rp->size > 0)
        {
                printf("%s\n", rp->returns);
        }
*/      close(sock);
        freeaddrinfo(serverInfo);
        printf("request sent successfully\n");
        return 0;
}
                

void create_storage()
{
	int i;
	for(i = 0; i < MAX_NUM_FILES; i++)
	{
		files[i].empty = true;
	}
}

int get_pos(char *filename)
{
	int i;
	for(i = 0; i < MAX_NUM_FILES; i++)
	{
		if((files[i].empty == false) && (strcmp(files[i].filename, filename) == 0))
		{
			return i;
		}
	}
	return -1;
}

int next_pos()
{
	int i;
	for(i = 0; i < MAX_NUM_FILES; i++)
	{
		if(files[i].empty == true)
		{
			return i;
		}
	}
	return -1;
}

int mycloud_getfile(char *filename, ReqResp *rp)
{
	int i = get_pos(filename);
	if(i >= 0)
	{
		rp->size = files[i].size;
		memcpy(rp->soul, files[i].soul, files[i].size);
		return 0;
	}
	return -1;
}

int mycloud_putfile(char *port, int key, char *filename, char *soul, size_t soul_size)
{
//	send(sock, rq, size_of_ReqResp(rq), 0);
        /*if(read(sock, rp, MAX_SIZE) < 0) {
                close(sock);
                return -4;
        }*/

	int i = get_pos(filename);
	if(i < 0)
	{
		i = next_pos();

		if(i < 0)
		{
			return -1;
		}		
	}
	files[i].empty = false;
	files[i].size = soul_size;
	strncpy(files[i].filename, filename, MAX_FILENAME);
	memcpy(files[i].soul, soul, soul_size);
	return 0;
}

int delete_file(char* filename) {
	int i = get_pos(filename);
	if(i == -1) {
		return -1;
	}
	else {
		files[i].empty = -1;
		return 1;
	}
}

