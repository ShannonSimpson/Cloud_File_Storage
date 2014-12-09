#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h> // needed for memcpy and strncpy?
#include "reqresp.h"
#include "mycloudlib.h"

storage files[MAX_NUM_FILES];

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

int mycloud_putfile(char *filename, char *soul, size_t soul_size)
{
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


