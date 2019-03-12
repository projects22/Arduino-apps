
// Android Bluetooth Frequency Counter, by www.moty22.co.uk
//
// MPLAB, Hi-Tech C compiler or XC8 on MPLABX.
// pic16f690
   
#include <htc.h>
#include <math.h>

#if defined(__XC8)
  #pragma config WDTE=OFF, MCLRE=OFF, BOREN=OFF, FOSC=HS, CP=OFF, CPD=OFF
#else defined(COMPILER_MPLAB_PICC)
 __CONFIG(MCLRDIS & WDTDIS & UNPROTECT & HS);
#endif

#define _XTAL_FREQ 8000000
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))

//prototypes
unsigned char SPI(unsigned char val);
void main(void);
void send(unsigned char bytex);


void main(void)
{

	unsigned char timebase;
	unsigned int freq2;
		
	// PIC I/O init
	TRISA2 = 1;		//RA2 freq input
	ANSEL = 0;			//digital port
	ANSELH = 0;
	ANS8 = 1;	//analogue chan 8
		
        #if defined(__XC8)
        OPTION_REG = 0b11111000;	//tmr0 1:1
        #else
        OPTION = 0b11111000;	//tmr0 1:1
        #endif
	T1CON=0;		//timer OFF, 1:1
	CCP1CON=0b1011;		//1011 = Compare mode, trigger special event (CCP1IF bit is set; CCP1 resets TMR1 or TMR2, and starts
							//an A/D conversion, if the ADC module is enabled)
	CCPR1L=0x40;	//CCP in compare mode sets TMR1 to a period of 20 ms
    CCPR1H=0x9c;
    	//ADC
    ADCON1 = 0B1010000;		// Fosc/16.
	ADCON0 = 0B10100000;	// ref=Vdd, right just, AN8, AD off 
		//UART
//	TXSTA = 0B0010
	TXEN = 1; SYNC = 0;
	SPEN = 1;  //Serial Port Enable bit	
	CREN = 1;	//receive enabled
	BRGH = 1;
	SPBRG = 51;	//baud rate 9600bps
	
	while(1){

				//start conversion
			ADON = 1;
			#if defined __XC8
		    	GO_DONE = 1;
		    #else
		    	GODONE=1;
		    #endif	
	//		__delay_ms(1);
			
		//Frequency Counter			
			freq2 = 0;	//clear timers
			timebase=50;	//50 * 20ms = 1sec
			TMR1L=0;  TMR1H=0;			
			TMR1ON = 1;	//start count
			TMR0 = 0;
			T0IF = 0;
					    
			while(timebase){		//1 sec 
				if(T0IF){++freq2; T0IF = 0;}
				if(CCP1IF){CCP1IF=0; --timebase;}
			}
			TMR1ON = 0;	//stop count

			send(ADRESH);	//ADC 2 bytes
			send(ADRESL);
			send(freq2 >> 8);	//frequency 3 bytes
			send(freq2);
			send(TMR0);
			
			ADON = 0;
			__delay_ms(1000);
	}	
}

void send(unsigned char bytex){		//transmit bytes
	TXREG = bytex;
	while (!TRMT){}		//wait for UART to finish TRMT
		
}
