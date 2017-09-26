#include "msp430f2272.h"
#include "define.h"
#include "flash.h"
#include "process.h"
#include "string.h"
#include "timer_a.h"
#include "init.h"
#include "cc1101.h"
#include "queue.h"
#include "stdlib.h"
#include "queue.h"

extern INT16U dev_id ;
INT8U _485_send_lock = 0;
INT8U _485_send_retry_times = 0;
INT8U _485_send_ack = 0;

extern INT8U ZJ_Ch;
extern Rs_485_Node data_buf_to_transfer[ MAX_NODE_NUM];

void delay(unsigned long nus){
	for(unsigned long i = nus; i > 0; i--){
	}
}
void Delay_1ms(void){
	unsigned int i;
	for(i = 0; i < 720; i++){
	}
}
void Delay_nms(unsigned long s){
	for(unsigned long i = s; i > 0; i--){	
		Delay_1ms();	
	}	
}

void RfTransmitPacket(INT8U *buf, INT8U len){
	INT8U i;
	INT8U sendBuf[13];
	
	wireless_trx_led_on();
	sendBuf[0] = 0x55;
	sendBuf[1] = 0xAA;
	for(i = 0; i < len; i++){
		sendBuf[i+2] = buf[i];
	}
 // crc_sum_calc
    sendBuf[len + 1] = 0;
	for(i = 0; i < (len + 2 - 1); i++){
		sendBuf[len + 1] += sendBuf[i];
	}
	CC1101SendPacket(sendBuf, len+2, BROADCAST);
	wireless_trx_led_off();
}

void UartTransmitPacket(INT8U *buf, INT8U len){
	ulong timeOut_tick ;
	
	uart_trx_led_on();
	UART485_TX_E;
	for (INT8U i = 0; i < len; i++){
		UCA0TXBUF = buf[i];
		timeOut_tick = _local_tickime();
		while(!(IFG2&UCA0TXIFG)){
			if(timeout(timeOut_tick, 500)) break;
		};
		IFG2 &= ~UCA0TXIFG;
	}
	Delay_nms(5);
	UART485_RX_E;
	uart_trx_led_off();
}

// 0x55+0xAA + 0x0b 0a 09 08---01
void send_freq_request_ack(void){
	INT8U freq_ack_buf[MSG_LEN] = {0};
	INT8U i = 0;
	
	freq_ack_buf[0] = WIRE_PACKET_HEAD_1;
	freq_ack_buf[1] = WIRE_PACKET_HEAD_2;
	freq_ack_buf[2] = 0x5A;
	freq_ack_buf[3] = 0x5A;
	for(i = 4; i < 13;i++){
		freq_ack_buf[i] = (13-i);
	}
	for(i = 0; i < 2; i++){
		Delay_nms(20);
		CC1101SendPacket(freq_ack_buf, MSG_LEN, BROADCAST);
	}
}

INT8U process_data_from_node(INT8U*data, INT8U len){
	INT16U crc_sum_check = 0;
	INT8U i;
	INT8U data_to_pc[13] = {0};

	if(len != 13){
		return 1;	
	}
	if((data[0] == WIRE_PACKET_HEAD_1)&&(data[1] == WIRE_PACKET_HEAD_2)){
		// scan freq req 
		if((data[2] == 0x5A)&&(data[3] == 0x5A)){
			for( i = 4; i < 13; i++){
				if(data[i] != (i - 3)){
					break;	
				}		
			}
			if(i == 13){
				send_freq_request_ack();		
			}	
		}
		// 
		else if((data[2] == 0x88) && (data[3] == 0xcc)){
			data_to_pc[0] = data[0];
			data_to_pc[1] = data[1];
			data_to_pc[2] = (INT8U)(dev_id >> 8);
			data_to_pc[3] = (INT8U)(dev_id);
			for(i = 4; i < 13; i++){
				data_to_pc[i] = data[i-2];
			}
			
			for(i = 2; i < 12; i++){
				crc_sum_check += data_to_pc[i];
			}
			data_to_pc[12] = (INT8U)crc_sum_check;
			switch(data_to_pc[5]){
				case 0x34: // 床号配置	
					enArray(data_to_pc, 13);
					break;
				case 0x30: //start
				case 0x31: //running				
				case 0x32: //stop
				case 0x33: // heartbeat
					UartTransmitPacket(data_to_pc, 13);
					break;
				default:
					break;				
			}
		}
	}
	return 0;
}

// data from uppper monitor, 485 communication
INT8U process_data_from_host(INT8U* data, INT8U len){
	INT8U crc_sum_check = 0;
	INT8U i;
	INT16U id;
	INT8U data_to_flash[3] = {0};
	INT8U data_to_CZ[11] = {0};

	if(len == 0){
		return 1;	
	}
	if((data[0] == 0x88) && (data[1] == 0xcc))
	{
		//sum 不包括帧头
		for(i = 2; i < (len - 1); i++){
			crc_sum_check += data[i];
		}
		
		//if(crc_sum_check == data[len - 1])
		{
			id = data[2];
			id = (id << 8) + data[3];
			if((id == 0xfefe) || (dev_id == id))
			{
				if(data[5] == FREQ_CH_REG)  //频率配置
				{			
					//set cc1101 channel	
					ZJ_Ch = data[8];
					cc1101_set_channel(ZJ_Ch);
					RfTransmitPacket(data_to_CZ, 11);
					// write flash
					data_to_flash[0] = 0x55;
					data_to_flash[1] = data[8];
					data_to_flash[2] = data[8];
					WriteFlash(ZJ_PARA_FLASH_ADDR, data_to_flash, 3); 
					// 回传给上位机
					data[4] = 0x01; //ack
					data[5] = 0x11; //cmd
					data[12] = crc_sum_check + 2;
					UartTransmitPacket(data, 13);			
				}
				if(data[5] == 0x34) //床号配置
				{
					if(data[4] == 0)
					{
						// 下发给称重器,去掉ZJ dev_id
						data_to_CZ[0] = data[0];
						data_to_CZ[1] = data[1];
						for(i = 2; i < 11; i++){
							data_to_CZ[i] = data[i+2];
						}					
						RfTransmitPacket(data_to_CZ, 11);
						// 回传给上位机
						data[4] = 0x01; //ack
						data[12] = crc_sum_check + 1;
						UartTransmitPacket(data, 13);
					}
					else
					{
						_485_send_ack = 1;					
					}								
				}
			}
		}
	}
	return 0;
}
void send_data_to485(void){
	UartTransmitPacket(data_buf_to_transfer[0].data, data_buf_to_transfer[0].data_len);
	_485_send_lock = 0;
}
void move_data_buf(void)
{
	Rs_485_Node* p1 = data_buf_to_transfer;
	Rs_485_Node* p2 = data_buf_to_transfer + 1;
	memmove(p1, p2, sizeof(Rs_485_Node) - sizeof(Rs_485_Node));
}

INT8U transfer_data_to485_(void)
{
	unsigned long time_delay;

	if(data_buf_to_transfer[0].data_len != 0)
	{
		if((_485_send_retry_times >= MAX_RETRY_TIMES) || (_485_send_ack == 1))
		{
			move_data_buf();//  move data fifo
			_485_send_lock = 0;
			_485_send_ack = 0;
			_485_send_retry_times = 0;			
			return 1;	
		}
		if(_485_send_lock == 1)
			return 1;
		UartTransmitPacket(data_buf_to_transfer[0].data, data_buf_to_transfer[0].data_len);
		_485_send_lock = 1;
		_485_send_ack = 0;
		_485_send_retry_times++;
		time_delay = 100 + rand() % 1000;
		Schd_After_Int(time_delay, send_data_to485);
		return 0;
	}	
	else
		return 1;
}
