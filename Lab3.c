#include "MKL25Z4.h"

void initialize(void);

int main(void)
{
	// Declaring values for "bAtCh 2022 "
	uint32_t val[11] = {0xFFFFFF83, 0xFFFFFF88, 0xFFFFFF87, 0xFFFFFFA6, 0xFFFFFF8B, 0xFFFFFFFF, 0xFFFFFFA4, 0xFFFFFFC0, 0xFFFFFFA4, 0xFFFFFFA4, 0xFFFFFFFF};

	// Output pin configuration
	SIM_SCGC5 |= 0x1C00; // Clock Enabled to Port  C,D,B

	PORTC_PCR0 = 0x00000100;
	PORTC_PCR1 = 0x00000100;
	PORTC_PCR2 = 0x00000100;
	PORTC_PCR3 = 0x00000100;
	PORTC_PCR4 = 0x00000100;
	PORTC_PCR5 = 0x00000100;
	PORTC_PCR6 = 0x00000100; // Declaring 7 pins as GPIO Pin : C0 to C6 (used for values of 7 Seg Display)
	GPIOC_PDDR = 0xFFFFFFFF;

	// D0-D5 and B0 Pins as TPM Pins
	PORTD_PCR0 = 0x00000400; // TPM0_CH0
	PORTD_PCR1 = 0x00000400; // TPM0_CH1
	PORTD_PCR2 = 0x00000400; // TPM0_CH2
	PORTD_PCR3 = 0x00000400; // TPM0_CH3
	PORTD_PCR4 = 0x00000400; // TPM0_CH4
	PORTD_PCR5 = 0x00000400; // TPM0_CH5
	PORTB_PCR0 = 0x00000300; // TPM1_CH0

	// TPM Settings
	SIM_SOPT2 |= 0x01000000; // Clock Source selected as MCGFLLCLK clock or MCGPLLCLK/2
	SIM_SCGC6 |= 0x07000000; // clock source to All TPM, 48MHz

	TPM0_SC = 0x8; // Counter Increments on every LPTPM Counter clock, prescaling 1
	TPM1_SC = 0x8;

	TPM0_C0SC = 0x28; // Edge Aligned and High True Pulse
	TPM0_C1SC = 0x28; // Edge Aligned and High True Pulse
	TPM0_C2SC = 0x28; // Edge Aligned and High True Pulse
	TPM0_C3SC = 0x28; // Edge Aligned and High True Pulse
	TPM0_C4SC = 0x28; // Edge Aligned and High True Pulse
	TPM0_C5SC = 0x28; // Edge Aligned and High True Pulse
	TPM1_C0SC = 0x28; // Edge Aligned and High True Pulse

	TPM0_MOD = 0x70000; // Modulo value in TPM
	TPM1_MOD = 0x70000; // Modulo value in TPM

	// Initializing values
	TPM0_C0V = 0;
	TPM0_C1V = 0;
	TPM0_C2V = 0;
	TPM0_C3V = 0;
	TPM0_C4V = 0;
	TPM0_C5V = 0;
	TPM1_C0V = 0;

	uint16_t i = 1;

	while (1)
	{
		for (i = 0; i < 11; i++)
		{

			uint32_t l = 1;
			uint32_t n = 0x70000;

			// Loop for Increasing the brightness and display
			for (l = 1; l < n; l++)
			{

				// Segment 1
				GPIOC_PDOR = val[i];
				TPM0_C0V = l;
				for (int k = 0; k < 100; k++)
					__NOP();
				initialize();

				// Segment 2
				if (i + 1 >= 11)
				{
					GPIOC_PDOR = val[(i + 1) - 11];
					TPM0_C1V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 1];
					TPM0_C1V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}

				// Segment 3
				if (i + 2 >= 11)
				{
					GPIOC_PDOR = val[i + 2 - 11];
					TPM0_C2V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 2];
					TPM0_C2V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}

				// Segment 4
				if (i + 3 >= 11)
				{
					GPIOC_PDOR = val[i + 3 - 11];
					TPM0_C3V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 3];
					TPM0_C3V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				// Segment 5
				if (i + 4 >= 11)
				{
					GPIOC_PDOR = val[i + 4 - 11];
					TPM0_C4V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 4];
					TPM0_C4V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				// Segment 6
				if (i + 5 >= 11)
				{
					GPIOC_PDOR = val[i + 5 - 11];
					TPM0_C5V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 5];
					TPM0_C5V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				// Segment 7
				if (i + 6 >= 11)
				{
					GPIOC_PDOR = val[i + 6 - 11];
					TPM1_C0V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 6];
					TPM1_C0V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
			}

			// Loop for Decreasing the brightness and display
			for (l = n; l > 0; l--)
			{

				GPIOC_PDOR = val[i];
				TPM0_C0V = l;
				for (int k = 0; k < 100; k++)
					__NOP();
				initialize();
				// Segment 2

				if (i + 1 >= 11)
				{
					GPIOC_PDOR = val[(i + 1) - 11];
					TPM0_C1V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 1];
					TPM0_C1V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}

				// Segment 3

				if (i + 2 >= 11)
				{
					GPIOC_PDOR = val[i + 2 - 11];
					TPM0_C2V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 2];
					TPM0_C2V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}

				// Segment 4
				if (i + 3 >= 11)
				{
					GPIOC_PDOR = val[i + 3 - 11];
					TPM0_C3V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 3];
					TPM0_C3V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}

				// Segment 5
				if (i + 4 >= 11)
				{
					GPIOC_PDOR = val[i + 4 - 11];
					TPM0_C4V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 4];
					TPM0_C4V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				// Segment 6
				if (i + 5 >= 11)
				{
					GPIOC_PDOR = val[i + 5 - 11];
					TPM0_C5V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 5];
					TPM0_C5V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				// Segment 7
				if (i + 6 >= 11)
				{
					GPIOC_PDOR = val[i + 6 - 11];
					TPM1_C0V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
				else
				{
					GPIOC_PDOR = val[i + 6];
					TPM1_C0V = l;
					for (int k = 0; k < 100; k++)
						__NOP();
					initialize();
				}
			}
		}
	}
}

void initialize(void)
{
	/*
		TPM0_C0V = 0;
		TPM0_C1V = 0;
		TPM0_C2V = 0;
		TPM0_C3V = 0;
		TPM0_C4V = 0;
		TPM0_C5V = 0;
		TPM1_C0V = 0;
	*/
}
