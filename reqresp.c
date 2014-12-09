#include "reqresp.h"

size_t size_of_ReqResp(ReqResp* r)
{
        return sizeof(r)+MAX_FILENAME*sizeof(char)+sizeof(uint32_t)+sizeof(char)*r->size;
}


int get_rq (char *in)
{
        if(strncmp(in, "get", 3) == 0)
        {       return GET;     }
        else if(strncmp(in, "put", 3) == 0)
        {       return STORE;   }
        else if(strncmp(in, "del", 3) == 0 || strncmp(in, "rm", 2)== 0)
        {       return DELETE;  }
        else if(strncmp(in, "list", 4) == 0)
        {       return LIST;    }
        return -1;
}

char* name_rq (int type)
 {
        switch(type)
        {
                case GET:
                        return "get";
                case STORE:
                        return "put";
                case DELETE:
                        return "delete";
                case LIST:
                        return "list";
                default:
                        return "other";
        }
}

