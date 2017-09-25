#ifndef PROCESS_H_
#define PROCESS_H_

#include "define.h"
#include "tools.h"

void delay(unsigned long nus);
void Delay_1ms(void);
void Delay_nms(unsigned long s);

void RfTransmitPacket(INT8U *buf, INT8U len);
void UartTransmitPacket(INT8U *buf, INT8U len);
INT8U process_data_from_node(INT8U*data, INT8U len);
INT8U process_data_from_host(INT8U* data, INT8U len);
void send_freq_request_ack(void);

#endif /*PROCESS_H_*/