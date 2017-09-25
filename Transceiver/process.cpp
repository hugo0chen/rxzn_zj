#include "msp430f2272.h"
#include "define.h"
#include "flash.h"
#include "process.h"
#include "string.h"
#include "timer_a.h"
#include "init.h"
#include "cc1101.h"


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

void sch_uart_led_off(union SchdParameter p){
	uart_trx_led_off();
}

#define LED_ON_HOLD_TIME 20
void uart_communication_indicate(void){
	uart_trx_led_on();	
	Schd_After_Int(LED_ON_HOLD_TIME,  sch_uart_led_off,  1);
}

void sch_wireless_led_off(union SchdParameter p){
	wireless_trx_led_off();
}
void wireless_communicator_indicate(void){
	wireless_trx_led_on();
	Schd_After_Int(LED_ON_HOLD_TIME, sch_wireless_led_off, 1);	
	
}
void RfTransmitPacket(INT8U *buf, INT8U len){
	INT8U i;
	INT8U sendBuf[13];

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
	wireless_communicator_indicate();
}

void UartTransmitPacket(INT8U *buf, INT8U len){
	ulong timeOut_tick ;
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
	uart_communication_indicate();
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
	CC1101SendPacket(freq_ack_buf, MSG_LEN, BROADCAST);
}

void process_data_from_node(INT8U*data, INT8U len){
	INT16U crc_sum_check = 0;
	INT8U i;

	if((data[0] == WIRE_PACKET_HEAD_1)&&(data[1] == WIRE_PACKET_HEAD_2)){
		// scan freq req 
		if((data[2] == 0x5A)&&(data[3] == 0x5A)){
			for( i = 4; i < 13; i++){
				if(data[i] != (i - 3)){
					break;	
				}		
			}
			if(i == 13){
				Delay_nms(200);
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
				case 0x34: // 床号配置	
					UartTransmitPacket(data, 11);
					break;
				default:
					break;				
			}
		}
	}
}

// data from uppper monitor, 485 communication
void process_data_from_host(INT8U* data, INT8U len){
	INT8U crc_sum_check = 0;
	INT8U i;
	INT8U data_to_flash[3];
	INT8U data_from_flash[3];

	if((data[0] == 0x88) && (data[1] == 0xcc)){
		//sum 不包括帧头
		for(i = 2; i < (len - 1); i++){
			crc_sum_check += data[i];
		}
		//if(crc_sum_check == data[len - 1])
		{
			switch(data[3]){
				case 0x10: // 频点配置
			//save to flash 并且设置cc1101的频率 todo
					data_to_flash[0] = 0x55;
					data_to_flash[1] = data[6];
					cc1101_set_channel(data_to_flash[1]);
					for(i = 0; i < 3; i++){
						WriteFlash(ZJ_PARA_FLASH_ADDR, data_to_flash, 2); 
						ReadFlash(ZJ_PARA_FLASH_ADDR, data_from_flash, 2);
						if(data_from_flash[0] == 0x55){
							break;
						}
					}
					data[3] = 0x11;
					data[10] = crc_sum_check + 1;
					UartTransmitPacket(data, 11);// 回传给上位机
					break;
				case 0x34://床号配置
				// 下发给称重器
				RfTransmitPacket(data, 11);
				
					break;	
				default:
					break;				
			}
		}
	}
}
