#include <MKL25Z4.h>
#include <stdio.h>

void uart_init(void); // Initialize UART0 Function
void port_init(void); // Initialize PORT Function
void adc_init(void); // Initialize ADC functions

int n;
char buffer[20]; 
int main(void){
	port_init();
	uart_init();
	adc_init();

	
	
	while(1){
	
	ADC0_SC1A = 0x09;
		
	while(!(ADC0_SC1A & 0x80)){
		__NOP();
	}
	n = ADC0_RA;
	sprintf(buffer,"%d\r\n",n);
	
	for(int i=0; i<sizeof(buffer);i++)
	{UART0_D = buffer[i];
		while(!(UART0_S1 & 0x80)){
		__NOP();
		}
	}
}
}


void adc_init(void){
	SIM_SCGC6 |= 0x8000000 ; // ADC0 clock enabled
	PORTB_PCR1 = 0x00;  //  Port B1 is ADC0_SE9 
	ADC0_SC1A = 0x09;  // single ended, interrupts disabled, channel SE9 means single-ended channel 9
	// setting the channel starts the conversion 
	
	ADC0_CFG1 = 0x0;  // bus clock, 8-bit conversion, clock divide ratio 1, short sampling
	
}

void port_init(void){
	
	// Clock Settings
	SIM_SCGC5 |= 0x600; // Clock to Port A and B is enabled
	PORTA_PCR2 = 0x200; // Alternative Pin 2(UART TX0)
	
}


void uart_init(void){
	
	// Clock settings
	SIM_SCGC4 |= 0x400; // Enabling clock to UART0
	SIM_SOPT2 |= 0x4000000; // Selecting clock source to MCGFLLCLK
	
	//UART0 settings
	UART0_C2 |= 0x0; // Disable Tx and Rx
	UART0_BDH |= 0x00; // Baud Rate Setting
	UART0_BDL |= 0x89; // SBR=137 with UART Module clk 20.971 MHz, OSR=16
	UART0_C4 |= 0xF; 	//Setting Oversampling Ratio to 16
	UART0_C1 |= 0x0; // 8bit mode character, NO parit
	UART0_C2 |= 0x08; // TX Enabled;
}
