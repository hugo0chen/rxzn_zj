#include "msp430f2272.h"
#include "define.h"
#include "flash.h"
#include "process.h"
#include "string.h"
#include "timer_a.h"
#include "init.h"
#include "cc1101.h"

extern INT8U ZJ_Ch;

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
				//Delay_nms(10);
				send_freq_request_ack();		
			}	
		}
		// 
		else if((data[2] == 0x88) && (data[3] == 0xcc)){
			for(i = 0; i < 10; i++){
				data[i] = data[i+2];	
			}
			
			for(i = 2; i < 10; i++){
				crc_sum_check += data[i];
			}
			data[10] = (INT8U)crc_sum_check;
			switch(data[3]){
				case 0x30: //start
				case 0x31: //running				
				case 0x32: //stop
				case 0x33: // heartbeat
				case 0x34: // ��������	
					UartTransmitPacket(data, 11);
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
	INT8U data_to_flash[3] = {0};
	//INT8U data_from_flash[3] = {0};

	if(len == 0){
		return 1;	
	}
	if((data[0] == 0x88) && (data[1] == 0xcc)){
		//sum ������֡ͷ
		for(i = 2; i < (len - 1); i++){
			crc_sum_check += data[i];
		}
		//if(crc_sum_check == data[len - 1])
		{
			switch(data[3]){
				case FREQ_CH_REG: 
					data_to_flash[0] = 0x55;
					data_to_flash[1] = data[6];
					data_to_flash[2] = data[6];
					ZJ_Ch = data[6];
					cc1101_set_channel(ZJ_Ch);
					RfTransmitPacket(data, 11);
					//for(i = 0; i < 3; i++)
					{
						WriteFlash(ZJ_PARA_FLASH_ADDR, data_to_flash, 3); 
						//ReadFlash(ZJ_PARA_FLASH_ADDR, data_from_flash, 3);
						//if((data_from_flash[0] == 0x55)&&(data_from_flash[1] == data_to_flash[1])){
						//	break;
						//}
					}
					data[3] = 0x11;
					data[10] = crc_sum_check + 1;
					// �ش�����λ��
					UartTransmitPacket(data, 11);
					break;
				case 0x34:
				// �·���������
				RfTransmitPacket(data, 11);				
					break;	
				default:
					break;				
			}
		}
	}
	return 0;
}