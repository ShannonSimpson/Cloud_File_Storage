#ifndef _MYCLOUDLIB_H_
#define _MYCLOUDLIB_H_
#define MAX_NUM_FILES 100
#include "reqresp.h"

typedef struct storage_struct {
	char filename[MAX_FILENAME];
	char soul[MAX_SIZE];
	size_t size;
	bool empty;
} storage;

void create_storage();
int get_pos(char *filename);
int next_pos();
int mycloud_getfile(char *filename, ReqResp *rp);
int mycloud_putfile(char *, char*, size_t);
int mycloud_delfile(char * filename); 
//What Jimmy wants:
//int mycloud_delfile(char *MachineName, int TCPport, int SecretKey, char *Filename)

//int list_files(ReqResp *rp);

#endif
