#include <stdint.h> 
#include "tm4c123gh6pm.h"

#define BLACK 0x00U
#define RED 0x02U
#define BLUE 0x04U
#define GREEN 0x08U
#define PURPLE 0x06U
#define YELLOW 0x0AU
#define CYAN 0x0CU
#define WHITE 0x0EU
#define PressedCode1 0x00U
#define PressedCode2 0x00U
#define LeftButton *((unsigned int*)0x40025040)
#define RightButton *((unsigned int*)0x40025004)

// delay n milliseconds (16 MHz CPU clock)
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++)
            {}  // do nothing for 1 ms
}

// delay n microseconds (16 MHz CPU clock)
void delayUs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3; j++)
            {}  // do nothing for 1 us
}

int main()
{
    // Init
    // Grant coprocessor access
    // This is required since TM4C123G has
    // a floating point coprocessor
    SCB_CPACR_R |= 0x00f00000;
  
    // Q3 
    // Motor Control

    int pw = 0;

    SYSCTL_RCGCPWM_R |= 0x02;        // enable clock to PWM1
    SYSCTL_RCGCGPIO_R |= 0x20;       // enable clock to GPIOF
    SYSCTL_RCGCGPIO_R |= 0x02;       // enable clock to GPIOB

    SYSCTL_RCC_R &= ~0x00100000;     // use system clock for PWM
    PWM1_INVERT_R |= 0x80;           // positive pulse
    PWM1_3_CTL_R = 0;               // disable PWM1_3 during configuration
    PWM1_3_GENB_R = 0x0000080C;     // output high when load and low when match
    PWM1_3_LOAD_R = 3999;           // 4 kHz
    PWM1_3_CTL_R = 1;               // enable PWM1_3
    PWM1_ENABLE_R |= 0x80;           // enable PWM1

    GPIOF_DIR_R |= 0x08;             // set PORTF 3 pins as output (LED) pin
    GPIOF_DEN_R |= 0x08;             // set PORTF 3 pins as digital pins
    GPIOF_AFSEL_R |= 0x08;           // enable alternate function
    GPIOF_PCTL_R &= ~0x0000F000;     // clear PORTF 3 alternate function
    GPIOF_PCTL_R |= 0x00005000;      // set PORTF 3 alternate funtion to PWM

    GPIOB_DEN_R |= 0x0C;             // PORTB 3 as digital pins
    GPIOB_DIR_R |= 0x0C;             // set PORTB 3 as output
    GPIOB_DATA_R |= 0x08;            // enable PORTB 3

    while(1)
    {
        for (pw = 100; pw < 3999; pw += 20)
        {
            PWM1_3_CMPB_R = pw;
            delayMs(50);
        }
        for (pw = 3900; pw >100; pw -= 20)
        {
            PWM1_3_CMPB_R = pw;
            delayMs(50);
        }
        GPIOB_DATA_R &= ~0x08;
        GPIOB_DATA_R |= 0x04;
        for (pw = 100; pw < 3999; pw += 20)
        {
            PWM1_3_CMPB_R = pw;
            delayMs(50);
        }
        for (pw = 3900; pw >100; pw -= 20)
        {
            PWM1_3_CMPB_R = pw;
            delayMs(50);
        }
        GPIOB_DATA_R &= ~0x04;
        GPIOB_DATA_R |= 0x08;
    }
}
