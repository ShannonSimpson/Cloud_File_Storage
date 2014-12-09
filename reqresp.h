#ifndef _REQRESP_H_
#define _REQRESP_H_

#include<stdlib.h>
#include<stdint.h>

#define MAX_FILENAME 80
#define MAX_SIZE 102400
#define GET 0
#define STORE 1
#define DELETE 2
#define LIST 3

typedef struct ReqResp_struct {
        int key;
        int type;
        char filename[MAX_FILENAME];
        char soul[MAX_SIZE];
        uint32_t size;
        uint32_t status;
}ReqResp;

size_t size_of_ReqResp(ReqResp* r);
int get_rq (char *in);
char* name_rq (int type);

#endif
