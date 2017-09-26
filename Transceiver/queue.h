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
  
void  init_485_data_buf(void);
INT8U enArray(INT8U*data, INT8U dataLen);
INT8U queue_isEmpty(void); 
  /*
void InitQueue(Queue*);
 INT8U EnQueue(Queue* queue, INT8U* inData, INT8U dataLen, unsigned int delay_time, INT8U re_times);
 INT8U DeQueue(Queue* queue, Rs_485_Node* outNode);
void PrintQueue(Queue* queue);
INT8U  IsNull(Queue* queue);
void DelQueue(Queue* queue);*/
#endif