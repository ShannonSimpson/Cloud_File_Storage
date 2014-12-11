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
}storage;

int response_check(ReqResp * rq, ReqResp * rp);
int send_request(ReqResp * rq, char* host, char* port, int key, ReqResp *rp);
void create_storage();
int get_pos(char *filename);
int next_pos();
int mycloud_getfile(char *filename, ReqResp *rp);
int mycloud_putfile(char* port, int key, char *filename, char *soul, size_t soul_size);
int mycloud_delfile(char * port, int key, char * filename);
int mycloud_listfiles(char *port, int key, ReqResp *rp);

#endif
