/*
author: mwas
email: francismwangi152@gmail.com
	
This projects uses the inbuild swicht and bulbs to do its functionalty
	It can be used  as a test of microcontroller if its working
	
	workflow:
		when switch one is pressed blue led lights up
		when switch two is pressed red led lights up
		when both of the swith are pressed no led lights up
		when none of the seitch is pressed green led lights up
		
		NB:
			all the switches and led are inbuld in the TM4C123GH6PM (port F)
		
	
*/
#include "edxtm4c123gh6pm.h"

//function prototype for activating port f

void PortF_init(void);

//initialize input data from switch
unsigned long switch_one, switch_two;

int main(void){
	//initialize port f
	PortF_init();
	 
	while(1){
		// input from PF4
		switch_one = GPIO_PORTF_DATA_R & 0x20;
		
		// input from PF0
		switch_two = GPIO_PORTF_DATA_R & 0x1;
		
		// if switch one and swith two are pressed
		if ((switch_one != 0x00) && (switch_two != 0x00)){
			// switch off all leds
			GPIO_PORTF_DATA_R &= 0xe;
		}
		else if (switch_one != 0x00){
			// light blue led
			GPIO_PORTF_DATA_R &= 0x4;
		}
		
		else if (switch_two != 0x00){
			// light red led
			GPIO_PORTF_DATA_R &= 0x2;
			
		}
		else{
			// no switch is pressed
			// light green led
			GPIO_PORTF_DATA_R &= 0x8;
		}
	}
}

void PortF_init(void){ volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x20;												// 1. activate clock for port f
	delay = SYSCTL_RCGC2_R;												// 		allow time for clock to start
	GPIO_PORTF_LOCK_R  = 0x4C4F4343;  						// 2. PF0 needs to be unlocked
	GPIO_PORTF_CR_R  = 0x1F; 											//    allow changes after lock to take place
	GPIO_PORTF_AMSEL_R  = 0x00;										// 3. disable analog
	GPIO_PORTF_PCTL_R   = 0x00;										// 4. select regular digital function
	GPIO_PORTF_DIR_R = 0xE;       								// 5. set the directions PF3, PF2,PF1 -> output  : PF0, PF4 -> input
	GPIO_PORTF_AFSEL_R = 0x00;										// 6. disable alternate functions
	GPIO_PORTF_DEN_R = 0x1F;											// 7. enable digital I/O in PF4-0
}
