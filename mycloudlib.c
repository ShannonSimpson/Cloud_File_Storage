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

//create storage struct
storage files[MAX_NUM_FILES];

//check that the response is valid
int response_check(ReqResp * rq, ReqResp * rp)
{

        if(rp->type == GET)
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
		if(rp->status == 0)
		{
			return 0;
		}
		return -1;
        }
	if(rp->type == LIST)
	{
		if(rp->status == 0)
		{
			return 0;
		}
		return -1;
	}
}

//server console printing and sending of info back to client on success
void printOut(ReqResp * rp, int connfd)
{
        printf("Secret Key = %d\n", rp->key);
        printf("Request Type = %s\n", name_rq(rp->type));
        if(rp->type != LIST)
        {
                printf("Filename = %s\n", rp->filename);
        }
        else
        {
                printf("Filename = NONE\n");
        }
	if(rp->status == 0)
	{
		printf("Operation Status = Success\n");
		send(connfd, rp, size_of_ReqResp(rp), 0);
	}
	else if(rp->status == -1)
	{
		printf("Operation Status = Error\n");
	}
	printf("-----------------------------------\n");
		
}



void executeReq(char* port, int key, int connfd)
{
	ReqResp list;
        ReqResp rq;
        ReqResp rp;
	rp.status = -1;
	rp.size = 0;
	rp.key = key;

       	size_t recieved;

       	if((recieved = recv(connfd, &rq, sizeof(ReqResp), 0)) != 0)
        {
		rp.type = rq.type;
		strncpy(rp.filename, rq.filename, MAX_FILENAME);
		//check for equal key
		if(rq.key == rp.key)
		{
			if(rq.type == GET)
               		{
               		     	if(mycloud_getfile(rq.filename, &rp) == 0)
        	               	{
					rp.status = 0;
                       		}
                	}
             	   	else if(rq.type == STORE)
               		{
                       		if(mycloud_putfile(port, key, rq.filename, rq.soul, rq.size) == 0)
                       		{
					rp.status = 0;
                       		}
               		}
              		else if(rq.type == DELETE)
               		{
               	        	if(mycloud_delfile(port, key, rq.filename) == 0)
				{
					rp.status = 0;
               			}
			}
        	        else if(rq.type == LIST)
	                {
	                       	if(mycloud_listfiles(port,key, &rp) == 0)
				{
					rp.status = 0;
                		}
			}
		}
		//else rp status will be bad
        }
	//print server info 
        printOut(&rp, connfd);
}


//handles the sending of requests to the server
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
		//create socket
                if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol))== -1)
                {
                        perror("server: socket");
                        continue;
                }

		//connect to server
                if(connect(sock, p->ai_addr, p->ai_addrlen) == -1)
                {
                        close(sock);
                        fprintf(stderr, "Server connection failed.\n");
                        continue;
                }
        }
	//send and wait for recieve
	send(sock, rq, size_of_ReqResp(rq), 0);
	
        if(read(sock, rp, MAX_SIZE) < 0) {
                close(sock);
                return -4;
        }
	//check response if bad print error
	if(response_check(rq, rp) != 0)
	{
		if(rq->type == LIST)
		{
			printf("no files found\n");
		}
		if(rq->type == GET)
		{
			printf("file not found\n");
		}
		else
		{
			printf("something went wrong\n");
		}
		printf("error\n");
	}
	//cleanup connection
        close(sock);
        freeaddrinfo(serverInfo);
        return 0;
}
                
//initialize file storage : called in server
void create_storage()
{
	int i;
	for(i = 0; i < MAX_NUM_FILES; i++)
	{
		files[i].empty = true;
	}
}

//get position of file in storage
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
//get position of next open position in storage
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
// function for getting file info from storage
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
//fucntion for placing file in storage
int mycloud_putfile(char *port, int key, char *filename, char *soul, size_t soul_size)
{

	int i = get_pos(filename);
	if(i == -1)
	{
		i = next_pos();

		if(i == -1)
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
//function for deleting file
int mycloud_delfile(char *port, int key, char* filename)
{
	int i = get_pos(filename);
	if(i == -1) 
	{
		return -1;
	}
	else 
	{
		files[i].empty = true;
		return 0;
	}
}
//function for passing files stored to client side
int mycloud_listfiles(char *port, int key, ReqResp *rp)
{
	int i;
	bool hasfiles = false;
	char * tempbuffer;
	char * tempbuffer2; 
	int numfiles = 0;
	tempbuffer = malloc(1024);
	tempbuffer2 = malloc(80000);
	for(i = 0; i < MAX_NUM_FILES; i++)
	{
		if(!files[i].empty)
		{
			numfiles = numfiles +1;
			strncpy(tempbuffer, files[i].filename, sizeof(files[i].filename));
			strncat(tempbuffer, "\n", 1);
			strncat(tempbuffer2, tempbuffer, sizeof(tempbuffer+1));
			hasfiles = true;
		}
	}
	int size = numfiles * MAX_FILENAME * sizeof(char);
	memcpy(rp->soul, tempbuffer2, MAX_SIZE);
	rp->size= size_of_ReqResp(rp);
	
	if(hasfiles == true)
	{
		return 0;
	}
	return -1;
		
}
