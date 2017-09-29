#include "msp430f2272.h"
#include "define.h"
#include "string.h"
#include "process.h"
#include "queue.h"

#define  MAX_UART_BUF  32

INT8U usart_rx_buf[MAX_UART_BUF] = {0};
INT8U usart_rx_index = 0;

extern Rs_485_Node data_buf_from_rx[ MAX_NODE_NUM];

INT8U process_usart_rx_data(INT8U data);

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  INT8U temp_data;
  temp_data = UCA0RXBUF;
  process_usart_rx_data(temp_data);
}

#define PKT_LEN 13
INT8U process_usart_rx_data(INT8U data)
{
	static INT8U sync_flag;
	
	if(usart_rx_index >=  MAX_UART_BUF){
		usart_rx_index = 0;
		memset(usart_rx_buf, 0, MAX_UART_BUF);
		sync_flag = 0;
		return 0;
	}
	
	usart_rx_buf[usart_rx_index++] = data;
	
	if(sync_flag == 0){
		if(usart_rx_index >= 2){
			if((usart_rx_buf[usart_rx_index - 2] == 0x88 ) && (usart_rx_buf[usart_rx_index - 1] == 0xCC)){
				sync_flag = 1;	
			}
			else if(usart_rx_buf[usart_rx_index - 1] == 0x88){
				usart_rx_buf[usart_rx_index - 2] = 0x88;
				usart_rx_buf[usart_rx_index - 1] = 0;
				usart_rx_index--;
			}
			else{
				memset(usart_rx_buf, 0, usart_rx_index);
				usart_rx_index = 0;
			}
		}
	}
	else{
		if(usart_rx_index == PKT_LEN){
			enArray(usart_rx_buf, PKT_LEN, data_buf_from_rx);
			usart_rx_index = 0;
			memset(usart_rx_buf, 0, PKT_LEN);
			sync_flag = 0;
		}
		else if(usart_rx_index > PKT_LEN ){
			usart_rx_index = 0;
			memset(usart_rx_buf, 0, usart_rx_index);
			sync_flag = 0;
		}	
	}
	return 0;
}
