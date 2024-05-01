#include "MKL25Z4.h"

// Code for Brightness Control using Polling method and Timer PWM Method

int main(void)
{

	// Port Configuration
	SIM_SCGC5 |= 0x0400;	  // Clock Enabled to Port  B
	PORTB_PCR19 = 0x00000300; // Choosing the Pin B19 as TPM2 pin

	// GPIOB_PDDR = 0xFFFFFFFF;  // Making as GPIO everything as Output
	// PORTB_PCR19 = 0x00000100; // Choosing the Pin B19 as GPIO pin

	// Timer Clock Source Settings
	SIM_SOPT2 |= 0x01000000; // clock source to all Timer
	SIM_SCGC6 |= 0x04000000; // clock source to TPM2, Source

	TPM2_SC = 0xb;		// Counter Increments on every LPTPM COunter clocks, prescaler 128
	TPM2_C1SC = 0x24;	// Edge Aligned and
	TPM2_MOD = 0x5b8d8; // Modulo value in TPM

	while (1)
	{
		uint32_t l = 0;
		TPM2_C1V = 0;
		for (l = 0; l < 62500; l++)
		{
			TPM2_C1V = l;
			for (int k = 0; k < 100; k++)
				__NOP();
		}
		TPM2_C1V = 62500;
		for (l = 62500; l > 0; l--)
		{
			TPM2_C1V = l;
			for (int k = 0; k < 100; k++)
				__NOP();
		}
	}
}

/*

int on=0;
int off=10000;

for(j=0;j<1000;j++){

	GPIOB_PDOR = 0x00080000;
	for(i=0;i<on;i++)__NOP();

	GPIOB_PDOR = 0x00000000;
	for(i=0;i<off;i++)__NOP();

	//GPIOE_PSOR = 0xFFFFFFFF;
	//GPIOE_PCOR = 0xFFFFFFFF;
	on=on+10;
	off=off-10;

}

on=10000;
off=0;

for(j=1000;j>=0;j--){

	GPIOB_PDOR = 0x00080000;
	for(i=0;i<on;i++)__NOP();

	GPIOB_PDOR = 0x00000000;
	for(i=0;i<off;i++)__NOP();

	//GPIOE_PSOR = 0xFFFFFFFF;
	//GPIOE_PCOR = 0xFFFFFFFF;
	on=on-10;
	off=off+10;

}

*/