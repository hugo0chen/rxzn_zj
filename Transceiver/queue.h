#ifndef QUEUE_H
#define QUEUE_H
#include "msp430f2272.h"
#include "define.h"


#define MAX_NODE_NUM 10
#define MAX_DATA_LEN 14

typedef struct _node
{
    INT8U data[MAX_DATA_LEN];
  	INT8U data_len;
}Rs_485_Node;
  
void  init_485_data_buf(Rs_485_Node*buf);
INT8U enArray(INT8U*data, INT8U dataLen,Rs_485_Node*buf);
INT8U queue_isEmpty(Rs_485_Node*buf); 
void move_data_buf(Rs_485_Node*buf);

#endif
