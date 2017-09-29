#include <string.h>
#include "msp430f2272.h"
#include "define.h"
#include "flash.h"
#include "init.h"
#include "cc1101.h"
#include "process.h"
#include "timer_a.h"
#include "queue.h"

INT8U   bRfRcv           = 0;
INT8U   bRfSend          = 0;
INT8U wireless_rxbuf[32];
INT8U wireless_rxlen;

INT8U ZJ_Ch     = DEFAULT_CH; 
INT16U dev_id   = 0;
Rs_485_Node data_buf_to_tx[ MAX_NODE_NUM];
Rs_485_Node data_buf_from_rx[ MAX_NODE_NUM];

void init_drivers(void){   
	_DINT(); 
	InitLed();
	InitTimerA();
	InitUCA0();
	Init485();
	init_cc1101();
	_EINT();
}

void feed_watchdog(void){
	WDTCTL = WDT_ARST_1000;
}


#define LED_PERIOD 1000

INT8U led_flash(void){
	static ulong led_time_tick ;
	
	if(timeout(led_time_tick, LED_PERIOD)){
		status_led_reverse();
		led_time_tick = _local_tickime();
		return 1;	
	}
	return 0;
}

INT8U read_para_from_flash(void){
	INT8U para[3];
	INT8U i;
	
	for(i = 0; i < 3; i++){
		ReadFlash(ZJ_PARA_FLASH_ADDR, para, 2);
		if(para[0] == 0x55){
			ZJ_Ch = para[1];
			cc1101_set_channel(ZJ_Ch, WP1);
			cc1101_set_channel(ZJ_Ch, WP2);
			return 1;
		}	
	}
	return 0;
}

int main(void){ 
	WDTCTL = WDTPW + WDTHOLD; 
	InitSysClk();
  	init_drivers();
  	dev_id = (P1IN&0xF0);
  	dev_id = dev_id >> 4;
  	init_485_data_buf(data_buf_to_tx);
  	init_485_data_buf(data_buf_from_rx);
  	if(!read_para_from_flash()){
  		cc1101_set_channel(DEFAULT_CH, WP1);
  		cc1101_set_channel(DEFAULT_CH, WP2);
  	}
	debug_print((INT8U*)"reset\n\r", sizeof("reset\n\r"));
	WDTCTL = WDT_ARST_1000;
	CC1101SetTRMode(RX_MODE, WP1 );
	CC1101SetTRMode(RX_MODE, WP2 );
	RF_GDO2_INT_E;
	
	while(1){	
		 led_flash();
		feed_watchdog();
		if (bRfRcv){
			bRfRcv = 0;
			wireless_trx_led_on();
			memset(wireless_rxbuf, 0, 32);
			wireless_rxlen = CC1101RecPacket(wireless_rxbuf, WP1);
			if(wireless_rxlen){
				//debug_print(wireless_rxbuf, wireless_rxlen);		
				process_data_from_node(wireless_rxbuf, wireless_rxlen);
			}
			CC1101SetTRMode(RX_MODE, WP1);
			wireless_trx_led_off();
		}
		if(!queue_isEmpty(data_buf_from_rx)){
			uart_trx_led_on();
			debug_print((INT8U*)"0", 1);
			process_data_from_host();
			move_data_buf(data_buf_from_rx);
			uart_trx_led_off();
		}
		if(!queue_isEmpty(data_buf_to_tx)){
			transfer_data_to485_();
		}
	}
}
