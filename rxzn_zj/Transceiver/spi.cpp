#include "spi.h"
/* MOSI  P3.1
 * MISO  P3.2
 * SCLK	 P3.3
*/
INT8U SPI_ExchangeByte(INT8U data){
	INT8U i,temp;
	_DINT(); 
	SCK_0 ;
	for(i = 0; i < 8; i++){
		if(data&0x80){
			MOSI_1;
		}
		else{
			MOSI_0;
		}
		data <<= 1;
		SCK_1;
		temp <<= 1;
		if(MISO) temp++;  //MISO
		SCK_0 ;
	}
	_EINT(); 
	return temp;
}

