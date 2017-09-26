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
	
	if(dataLen > MAX_NODE_NUM)
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
		return 1;
	return 0;	
}
/*
void DelQueue(Queue* queue)
{
	 Rs_485_Node* outNode;
	while(queue->head != queue->tail)
	{
	  DeQueue(queue, outNode);
	}
}
//初始化队列
 void InitQueue(Queue* queue)
 {
     queue->tail = (Rs_485_Node*)malloc(sizeof(Rs_485_Node));//warning
     memset(queue->tail->data, 0, MAX_QUEUE_DATA_LEN);
     queue->tail->data_len	   = 0;
     queue->tail->flag_success = 0;
     queue->tail->retry_times  = 0;
     queue->tail->time_delay   = 0;
     queue->head = queue->tail;
     queue->tail->next = NULL;
 }
  //入队
 INT8U EnQueue(Queue* queue, INT8U* inData, INT8U dataLen, unsigned int delay_time, INT8U re_times)
 {
 	if(dataLen > MAX_QUEUE_DATA_LEN){
 		return 1;
 	}
 	
    Rs_485_Node * newNode = (Rs_485_Node*)malloc(sizeof(Rs_485_Node));//warning
    memcpy(newNode->data, inData, dataLen);
    newNode->data_len     = dataLen;
    newNode->flag_success = 0;
    newNode->retry_times  = re_times;
    newNode->time_delay   = delay_time;
    newNode->next 		  = NULL;
    queue->tail->next     = newNode;
    queue->tail = newNode;
 	return 0;
 }
 // 出队
 INT8U DeQueue(Queue* queue, Rs_485_Node* outNode)
 {
     memcpy(outNode->data ,queue->head->data, queue->head->data_len);
     outNode->data_len =  queue->head->data_len;
     outNode->flag_success = queue->head->flag_success;
     outNode->retry_times = queue->head->retry_times;
     outNode->time_delay =  queue->head->time_delay;
     Rs_485_Node *popNode = queue->head;
     queue->head = queue->head->next;
     free(popNode);
     return 0;
 }
 //1 means Null
 INT8U IsNull(Queue* queue)
 {
     return (queue->head == queue->tail);
 }
 void PrintQueue(Queue* queue)
 {
    if(IsNull(queue))
    {
         printf("empty queue.\n");
         return ;
     }
     Rs_485_Node* curNode= queue->head->next;
     while(curNode)
     {
         if(curNode->next !=NULL)
         {
             printf("%d==>", curNode->data);
         }else
         {
             printf("%d ", curNode->data);
 
         }
         curNode = curNode->next;
     }
     printf("\n");
 
 }*/
 
