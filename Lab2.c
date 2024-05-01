#include "MKL25Z4.h"



int main(void)
{
		
	
		SIM_SCGC5 |= 0x2800;	// Clock Enabled to Port  C,E
	
	//	SIM_SOPT2 |= 0x02000000;
	//	SIM_SCGC6 |= 0x01000000;
	
		
	
	
		PORTC_PCR0 = 0x00000100; 
		PORTC_PCR1 = 0x00000100; 
		PORTC_PCR2 = 0x00000100; 
		PORTC_PCR3 = 0x00000100; 
		PORTC_PCR4 = 0x00000100; 
		PORTC_PCR5 = 0x00000100; 
		PORTC_PCR6 = 0x00000100; // Declaring as GPIO Pin
		PORTE_PCR0 = 0x00000100;
		PORTE_PCR1 = 0x00000100;
	
		GPIOC_PDDR = 0xFFFFFFFF;
		GPIOE_PDDR = 0xFFFFFFFF; // Making Everythinng as Output 
	
	
	//	PORTE_GPCHR = 0xFFFF0000;
	//	PORTE_GPCLR = 0xFFFF0000;
	//	TPM0_SC = 0x0008;
	//	TPM0_MOD = 0x0064;
	//	TPM0_C0V = 0x0020;
	
	unsigned int val[10]={0xFFFFFF40,0xFFFFFF79,0xFFFFFF24,0xFFFFFF30,0xFFFFFF19,0xFFFFFF12,0xFFFFFF02,0xFFFFFF78,0xFFFFFF00,0xFFFFFF10};
	
	while(1)
	{
		int delay=2400000;
		int k;
		int j;
		for(int p=0;p<99;p++){
				
				k=p%10;
				j=p/10;
				
				
				for(int n=0;n<delay/1000;n++){
					
					for(int l=0;l<500;l++){
					GPIOE_PDOR = 0x2;
					GPIOC_PDOR = val[k];
					}
					for(int l=0;l<500;l++){
					GPIOE_PDOR = 0x1;
					GPIOC_PDOR = val[j];
					}	
				}
			}
			
			
			
			
	}
}