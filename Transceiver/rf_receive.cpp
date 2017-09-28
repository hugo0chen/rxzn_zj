#include "msp430f2272.h"
#include "define.h"
#include "init.h"
#include "process.h"

extern INT8U bRfRcv;
extern INT8U tx_enable ;
extern INT8U tx_done ;
// interrupt for receiving data
#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR (void)
{
	if(RF_GDO2_INT){
		RF_GDO2_INT_D;
		RF_GDO2_INT_C;
		if(tx_enable == 1){
			tx_done = 1;	
		}
		else{
			SET_FLG(bRfRcv);	
		}
	    RF_GDO2_INT_E;	   
	}
	/*else if(RF_GDO0_INT){
		RF_GDO0_INT_D;
		RF_GDO0_INT_C;
		SET_FLG(bRfRcv);
	    RF_GDO0_INT_E;	  
	}*/
	if(RF_2_GDO2_INT){
		RF_2_GDO2_INT_D;
		RF_2_GDO2_INT_C;
		if(tx_enable == 1){
			tx_done = 1;	
		}
		else{
			SET_FLG(bRfRcv);	
		}
	    RF_2_GDO2_INT_E;
	}
	/*else if(RF_GDO0_INT){
		RF_GDO0_INT_D;
		RF_GDO0_INT_C;
		SET_FLG(bRfRcv);
	    RF_GDO0_INT_E;	  
	}*/
}
