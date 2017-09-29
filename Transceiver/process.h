#ifndef PROCESS_H_
#define PROCESS_H_

#include "define.h"
#include "tools.h"

#define MAX_RETRY_TIMES  10

void delay(unsigned long nus);
void Delay_1ms(void);
void Delay_nms(unsigned long s);
void debug_print(INT8U* string, INT8U len);

void RfTransmitPacket(INT8U *buf, INT8U len);
void UartTransmitPacket(INT8U *buf, INT8U len);
INT8U process_data_from_node(INT8U*data, INT8U len);
INT8U process_data_from_host(void);
void send_freq_request_ack(void);
INT8U transfer_data_to485_(void);

#endif 
