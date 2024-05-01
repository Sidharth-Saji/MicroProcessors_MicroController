#include <MKL25Z4.h>

void uart_init(void); // Initialize UART0 Function
void port_init(void); // Initialize PORT Function

int main(void)
{

	uart_init();
	port_init();
	while (1)
	{
		const char word[] = "Hello World ";

		for (unsigned int u = 0; u < sizeof(word); u++)
		{
			UART0_D = word[u];
			while (!(UART0_S1 & 0x80))
				;
		}
	}
}

void port_init(void)
{

	// Clock Settings
	SIM->SCGC5 |= 0x200; // Clock to Port A is enabled
	PORTA_PCR2 = 0x200;	 // Alternative Pin 2(UART TX0)
}
void uart_init(void)
{

	// Clock settings
	SIM->SCGC4 |= 0x400;	 // Enabling clock to UART0
	SIM->SOPT2 |= 0x4000000; // Selecting clock source to MCGFLLCLK

	// UART0 settings
	UART0->C2 |= 0x0;	// Disable Tx and Rx
	UART0->BDH |= 0x00; // Baud Rate Setting
	UART0->BDL |= 0x80; // SBR=137 with UART Module clk 20.971 MHz, OSR=16
	UART0->C4 |= 0xF;	// Setting Oversampling Ratio to 16
	UART0->C1 |= 0x0;	// 8bit mode character, NO parity bit
	UART0->C2 |= 0x08;	// Transmitter Enabled;
}
