#ifndef _MYCLOUDLIB_H_
#define _MYCLOUDLIB_H_
#define MAX_NUM_FILES 100
#include "reqresp.h"
#include<stdbool.h>

typedef struct storage_struct {
	char filename[MAX_FILENAME];
	char soul[MAX_SIZE];
	size_t size;
	bool empty;
} storage;

int send_request(ReqResp * rq, char* host, char *port, int *key, ReqResp *rp);
void create_storage();
int get_pos(char *filename);
int next_pos();
int mycloud_getfile(char *filename, ReqResp *rp);
int mycloud_putfile(char *host, int port, int key, char *filename, char *soul, size_t soul_size);
//bool delete_file(char * filename);
//What Jimmy wants:
//int mycloud_delfile(char *MachineName, int TCPport, int SecretKey, char *Filename)

//int list_files(ReqResp *rp);

#endif
