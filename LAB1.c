#include "MKL25Z4.h"

int main(void)
{

	//		uint32_t i=0;
	//		uint32_t j=0;

	//	SIM_SOPT2 |= 0x02000000;
	//	SIM_SCGC6 |= 0x01000000;

	//  GPIOB_PDDR = 0xFFFFFFFF;	// Making as GPIO Output
	//	PORTB_PCR19 = 0x00000100; // Choosing the Pin B19 as GPIO pin

	//	PORTE_GPCHR = 0xFFFF0000;
	//	PORTE_GPCLR = 0xFFFF0000;
	//	TPM0_SC = 0x0008;
	//	TPM0_MOD = 0x0064;
	//	TPM0_C0V = 0x0020;

	// Port Configuration
	SIM_SCGC5 |= 0x0400;	  // Clock Enabled to Port  B
	PORTB_PCR19 = 0x00000300; // Choosing the Pin B19 as TPM2 pin

	// PWM Settings
	SIM_SOPT2 |= 0x01000000; // clock source to all PWM
	SIM_SCGC6 |= 0x04000000; // clock source to TPM2, Source

	TPM2_SC = 0xb;		// Counter Increments on every LPTPM COunter clocks, prescaler 128
	TPM2_C1SC = 0x24;	// Edge Aligned and
	TPM2_MOD = 0x5b8d8; // Modulo value in TPM

	while (1)
	{

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
