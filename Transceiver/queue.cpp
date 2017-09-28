#include "queue.h"
#include "define.h"
#include "stdlib.h"
#include "string.h"

#include <stdio.h>
    
Rs_485_Node data_buf_to_transfer[ MAX_NODE_NUM];

void init_485_data_buf(void){
	for(INT8U i = 0; i <  MAX_NODE_NUM; i++){
		memset(data_buf_to_transfer[i].data, 0, MAX_DATA_LEN);
		data_buf_to_transfer[i].data_len     = 0;
	}	
}

INT8U enArray(INT8U*data, INT8U dataLen){
	INT8U i;
	
	if(dataLen > MAX_DATA_LEN)
		return 1;
	for(i = 0; i < MAX_NODE_NUM; i++){
		if(	data_buf_to_transfer[i].data_len == 0){
			memcpy(data_buf_to_transfer[i].data, data, dataLen);
			data_buf_to_transfer[i].data_len     = dataLen;
			break;	
		}
	}
	if(i < MAX_NODE_NUM)
		return 0;
	return 1;
}

INT8U queue_isEmpty(void){
	INT8U i;
	for(i = 0; i < MAX_NODE_NUM; i++){
		if(data_buf_to_transfer[i].data_len != 0)
			break;	
	}
	if(i < MAX_NODE_NUM)
		return 0;
	return 1;	
}
