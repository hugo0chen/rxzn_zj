#include "queue.h"
#include "define.h"
#include "stdlib.h"
#include "string.h"

#include <stdio.h>
    


void init_485_data_buf(Rs_485_Node*buf){
	for(INT8U i = 0; i <  MAX_NODE_NUM; i++){
		memset(buf[i].data, 0, MAX_DATA_LEN);
		buf[i].data_len     = 0;
	}	
}

INT8U enArray(INT8U*data, INT8U dataLen, Rs_485_Node*buf){
	INT8U i;
	
	if(dataLen > MAX_DATA_LEN)
		return 1;
	for(i = 0; i < MAX_NODE_NUM; i++){
		if(	buf[i].data_len == 0){
			memcpy(buf[i].data, data, dataLen);
			buf[i].data_len = dataLen;
			break;	
		}
	}
	if(i < MAX_NODE_NUM)
		return 0;
	return 1;
}

INT8U queue_isEmpty(Rs_485_Node*buf){
	INT8U i;
	for(i = 0; i < MAX_NODE_NUM; i++){
		if(buf[i].data_len != 0)
			break;	
	}
	if(i < MAX_NODE_NUM)
		return 0;
	return 1;	
}

void move_data_buf(Rs_485_Node*buf)
{
	Rs_485_Node* p1 = buf;
	Rs_485_Node* p2 = buf + 1;
	memmove(p1, p2,  sizeof(Rs_485_Node)*(MAX_NODE_NUM - 1));
	memset(&buf[MAX_NODE_NUM -1], 0, sizeof(Rs_485_Node));
}
