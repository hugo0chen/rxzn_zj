#ifndef INIT_H_
#define INIT_H_

// RF receiving port
/*
#define RF_GDO0_INT         (!IsClr(P3IFG & BIT0))
#define RF_GDO0_INT_D       (P3IE &= ~BIT0)
#define RF_GDO0_INT_E       (P3IE |= BIT0)
#define RF_GDO0_INT_C       (P3IFG &= ~BIT0)
*/
#define RF_GDO2_INT         (!IsClr(P2IFG & BIT1))
#define RF_GDO2_INT_D       (P2IE &= ~BIT1)
#define RF_GDO2_INT_E       (P2IE |= BIT1)
#define RF_GDO2_INT_C       (P2IFG &= ~BIT1)

//system clock : 8MHz
inline void InitSysClk(void){
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;
	BCSCTL3 |= LFXT1S_2;
}

inline void InitLed(void){	
	// other leds on the side
	P1DIR |= (BIT0 + BIT1 + BIT2 + BIT3);
	P1OUT |= (BIT0 + BIT1 + BIT2 + BIT3);
	
	// status led,P2.4-debug
	P2DIR |= BIT4 + BIT5;
	P2OUT |= BIT4 + BIT5;
	P2OUT &= ~BIT4;
	 // RJ45 leds
	P4DIR |= (BIT3 + BIT4 + BIT5 + BIT6 );
	P4OUT |= (BIT3 + BIT4 + BIT5 + BIT6 );
}
inline void init_button(void){
	
	P1DIR &= ~(BIT4 + BIT5 + BIT6 + BIT7); // input
	P1REN |= (BIT4 + BIT5 + BIT6 + BIT7);
	P1OUT |= (BIT4 + BIT5 + BIT6 + BIT7);
	
	P2DIR &= ~BIT3; // input
	P2REN |= BIT3;
	P2OUT |= BIT3;
	
	P3DIR &= ~BIT7; // input
	P3REN |= BIT7;
	P3OUT |= BIT7;
}
//timer_A clock: 8/8 MHZ
//period : 10ms 
inline void InitTimerA(void)
{
	TACCTL0 = CCIE;
	TACCR0 = 10000;
	TACTL = TASSEL_2 + ID_3 + MC_1;     // SMCLK, contmode, 1/8 div
}

inline void init_cc1101_gpio(void){
	// GDO0A:P4.2 //GDO2A:P4.0
/*	P4IES |= BIT2 + BIT0;
  	P4DIR &= ~(BIT2 + BIT0) ;s
  	P4IFG &= ~(BIT2 + BIT0);
 */ 	
  	// CS_A
	P4DIR |= BIT1;
	P4OUT |= BIT1;
	
  	// GDO0B
/*	P3IES |= BIT0;
  	P3DIR &= ~BIT0;
  	P3IFG &= ~BIT0;*/
  	//GDO2B
  	P2IES &= ~BIT1;
  	P2DIR &= ~BIT1; 
  	P2IFG &= ~BIT1;
  	// CS_B
	P2DIR |= BIT2;
	P2OUT |= BIT2;
}
inline void init_spi(void){
   // P3.1->MOSI, P3.2<-MISO, P3.3->SCLK
  	P3DIR |= (BIT1 + BIT3); 
  	P3OUT |= (BIT1 + BIT3);
  	P3DIR &= ~BIT2;
}
inline void InitUCA0(void){
	P3SEL |= BIT4 + BIT5;                     // P3.4,5 = USCI_A0 TXD/RXD
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  	UCA0BR0 = 208;                            // 430 user guide,page 424 ,8Mhz 38400 208
  	UCA0BR1 = 0;                              // 
  	UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
  	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  	IE2 |= UCA0RXIE;                         // Enable USCI_A0 RX interrupt
}

inline void Init485(void){
	P4DIR |= BIT7;
	P4OUT &= ~BIT7;
}

//-------------------------------------
inline void status_led_on(void){
	P2OUT &= ~BIT5;
}
inline void status_led_off(void){
	P2OUT |= BIT5;	
}
inline void status_led_reverse(void){
	P2OUT ^= BIT5;
}
inline void uart_trx_led_on(void){
	P1OUT &= ~BIT1;	
}

inline void uart_trx_led_off(void){
	P1OUT |= BIT1;	
}
inline void uart_trx_led_reverse(void){
	P1OUT ^= BIT1;	
}

inline void wireless_trx_led_on(void){
	P1OUT &= ~BIT3;	
}
inline void wireless_trx_led_off(void){
	P1OUT |= BIT3;	
}
inline void wireless_trx_led_reverse(void){
	P1OUT ^= BIT3;	
}

#endif /*INIT_H_*/
