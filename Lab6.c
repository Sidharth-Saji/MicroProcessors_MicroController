#include <MKL25Z4.h>
#include <stdio.h>

void delay_init(void);
void Push_Button_init(void); // Intialize Switch and LED Ports
void PORTD_IRQHandler(void); // Declaring Interrupt routine
void sev_seg(int val);       // Seven segment Display
int valueNotInArray(int value, volatile int *arr);
void valueAdd(int num);
int reg[6] = {-1, -1, -1, -1, -1, -1, -1};
unsigned int val_SSD[6] = {0xFFFFF4F0, 0xFFFFF7F9, 0xFFFFF2F4, 0xFFFFF3F0, 0xFFFFF1F9, 0xFFFFF1F2}; // seven segment display
int current_floor = 0;                                                                              // Floor on which you are currently in
void TPM0_IRQHandler(void);
void move(int initial, int final);
int no_req;

int main(void)
{
    Push_Button_init();
    NVIC_EnableIRQ(0x1F); // Enabling Interrupt in D
    NVIC_EnableIRQ(0x11); // Enabling Timer Interrupt
    sev_seg(0);           // initialising sev seg to 0
    delay_init();         // Initializing Timer, Startint Timer
    no_req = 0;
    while (1)
    {
    }
}

void Push_Button_init(void)
{
    // Port Configuration

    SIM_SCGC5 |= 0x01800; // Clock Enabled to Port  D and C

    PORTD_PCR0 |= 0xA0103; // Choosing the Pin D0 as enable interrupt on falling, GPIO pin, pullup resistor enabled
    PORTD_PCR1 |= 0xA0103; // Choosing the Pin D1 as enable interrupt on falling, GPIO pin, pullup resistor enabled
    PORTD_PCR2 |= 0xA0103; // Choosing the Pin D2 as enable interrupt on falling, GPIO pin, pullup resistor enabled
    PORTD_PCR3 |= 0xA0103; // Choosing the Pin D3 as enable interrupt on falling, GPIO pin, pullup resistor enabled
    PORTD_PCR4 |= 0xA0103; // Choosing the Pin D4 as enable interrupt on falling, GPIO pin, pullup resistor enabled
    PORTD_PCR5 |= 0xA0103; // Choosing the Pin D5 as enable interrupt on falling, GPIO pin, pullup resistor enabled

    PORTC_PCR0 |= 0x100; // Choosing the Pin C0 as GPIO pin
    PORTC_PCR1 |= 0x100; // Choosing the Pin C0 as GPIO pin
    PORTC_PCR2 |= 0x100; // Choosing the Pin C0 as GPIO pin
    PORTC_PCR3 |= 0x100; // Choosing the Pin C0 as GPIO pin
    PORTC_PCR4 |= 0x100; // Choosing the Pin C0 as GPIO pin
    PORTC_PCR5 |= 0x100; // Choosing the Pin C0 as GPIO pin

    GPIOC_PDDR |= 0xFF; // Choosing The Pin C as Ouput pin

    GPIOC_PDOR = 0x0; // Initialize to LED OFF by 0x0
}

void PORTD_IRQHandler(void)
{

    if (((PORTD_PCR0 >> 24) & 0x1) == 0x1)
    {
        valueAdd(0);
        GPIOC_PDOR |= 0x01; // B1
    }
    else if (((PORTD_PCR1 >> 24) & 0x1) == 0x1)
    {
        valueAdd(1);
        GPIOC_PDOR |= 0x02; // B2
    }
    else if (((PORTD_PCR2 >> 24) & 0x1) == 0x1)
    {
        valueAdd(2);

        GPIOC_PDOR |= 0x04; // B3
    }
    else if (((PORTD_PCR3 >> 24) & 0x1) == 0x1)
    {
        valueAdd(3);
        GPIOC_PDOR |= 0x08; // B4
    }
    else if (((PORTD_PCR4 >> 24) & 0x1) == 0x1)
    {
        valueAdd(4);

        GPIOC_PDOR |= 0x10; // B5
    }
    else if (((PORTD_PCR5 >> 24) & 0x1) == 0x1)
    {
        valueAdd(5);
        GPIOC_PDOR |= 0x020; // B6
    }

    PORTD_ISFR = 0xFFFFFFFF;
}

void delay_init()
{
    SIM_SOPT2 |= 0x01000000; // clock source to all Timer
    SIM_SCGC6 |= 0x01000000; // clock source to TPM0_CH1, Source
    TPM0_SC |= 0x47;
    TPM0_MOD |= 0xFFFF;
    TPM0_SC |= 0x4F; // Timer Starts
}

void sev_seg(int floor)
{
    SIM_SCGC5 |= 0x0400;

    PORTB_PCR0 = 0x00000100;
    PORTB_PCR1 = 0x00000100;
    PORTB_PCR2 = 0x00000100;
    PORTB_PCR3 = 0x00000100;
    PORTB_PCR8 = 0x00000100;
    PORTB_PCR9 = 0x00000100;
    PORTB_PCR10 = 0x00000100; // declaring as GPIO pin
    GPIOB_PDDR = 0xFFFFFFFF;  // declaring as output.
    GPIOB_PDOR = val_SSD[floor];
}

int valueNotInArray(int value, volatile int *arr)
{
    if (arr[value] != NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void valueAdd(int num)
{
    if (valueNotInArray(num, reg))
    {
        reg[num] = num;
        no_req++;
    }
}

void move(int from, int to)
{
    /*
    Display values in elevator, after reaching turning off th LED
    */
    if (from < to)
    {
        for (int j = from; j < to + 1; j++)
        {
            sev_seg(j);
            for (int k = 0; k < 10000000 / 2; k++) //  Moving Delay
            {
                __NOP();
            }
        }
    }
    else
    {
        for (int j = from; j >= to; j--)
        {
            sev_seg(j);
            for (int k = 0; k < 10000000 / 2; k++) //  Moving Delay
            {
                __NOP();
            }
        }
    }

    // Turn off LED
    if (to == 0)
    {
        GPIOC_PDOR &= ~(0x01); // B1
    }
    else if (to == 1)
    {
        GPIOC_PDOR &= ~(0x02); // B2
    }
    else if (to == 2)
    {
        GPIOC_PDOR &= ~(0x04); // B3
    }
    else if (to == 3)
    {
        GPIOC_PDOR &= ~(0x08); // B4
    }
    else if (to == 4)
    {

        GPIOC_PDOR &= ~(0x10); // B5
    }
    else if (to == 5)
    {
        GPIOC_PDOR &= ~(0x020); // B6
    }
}

void TPM0_IRQHandler(void)
{

    for (int j = 0; j < 6; j++)
    {
        if (current_floor - j >= 0)
        {
            if (reg[current_floor - j] != -1)
            {
                move(current_floor, current_floor - j);
                reg[current_floor - j] = -1;
                current_floor = current_floor - j;
                break;
            }
        }
        if (current_floor + j <= 6)
        {
            if (reg[current_floor + j] != -1)
            {
                move(current_floor, current_floor + j);
                reg[current_floor + j] = -1;
                current_floor = current_floor + j;
                break;
            }
        }
    }

    // Is any requests remaining
    for (int i = 0; i < 6; i++)
    {
        if (reg[i] != NULL)
        {
            TPM1_SC |= (1 << 7); // Timer starts again
        }
    }
}
