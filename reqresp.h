#ifndef _REQRESP_H_
#define _REQRESP_H_

#include<stdlib.h>
#include<stdint.h>
//definitions used throughout program
#define MAX_FILENAME 80
#define MAX_SIZE 102400
#define GET 0
#define STORE 1
#define DELETE 2
#define LIST 3
//struct to handle requests and responses
typedef struct ReqResp_struct {
        int key;
        int type;
	int size;
        char filename[MAX_FILENAME];
        char soul[MAX_SIZE];
        uint32_t status;
}ReqResp;
//functions for requests and responses
size_t size_of_ReqResp(ReqResp* r);
int get_rq (char *in);
char* name_rq (int type);

#endif
