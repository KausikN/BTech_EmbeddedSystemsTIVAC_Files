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

int main()
{
  // Q3 
  // Motor Control
  
    int x = 15999;
    // Enable Peripheral Clocks
    SYSCTL_RCGCPWM_R |= 2;       // enable clock to PWM1
    SYSCTL_RCGCGPIO_R |= 0x20;   // enable clock to PORTF
    SYSCTL_RCC_R &= ~0x00100000; // no pre-divide for PWM clock
    // Enable port PF2 for PWM1 M1PWM7  
    GPIO_PORTB_AFSEL_R = 0x0E;   // PF2 uses alternate function
    GPIO_PORTB_PCTL_R |= 0x000005550; 
    GPIO_PORTB_DEN_R = 0x02;     // pin digital 
    PWM1_2_CTL_R = 0;            // stop counter  
    PWM1_2_GENB_R = 0x0000008C;  // M1PWM6 output set when reload, 
    PWM1_3_CTL_R = 0;            // stop counter  
    PWM1_3_GENA_R = 0x0000008C;  // M1PWM6 output set when reload,
    PWM1_3_GENB_R = 0x0000008C;  // M1PWM6 output set when reload, 
    // clear when match PWMCMPA  
    PWM1_2_LOAD_R = 16000;       // set load value for 1kHz (16MHz/16000)  
    PWM1_2_CMPA_R = 15999;       // set duty cycle to min  
    PWM1_2_CTL_R = 1;            // start timer  
    PWM1_3_LOAD_R = 16000;       // set load value for 1kHz (16MHz/16000)  
    PWM1_3_CMPA_R = 15999;       // set duty cycle to min  
    PWM1_3_CTL_R = 1;            // start timer  
    PWM1_ENABLE_R = 0xE0;        // start PWM1 ch7 

    *((unsigned int*)0x400FE608)=0x20U;
    *((unsigned int*)0x40025400)=0x0EU;
    *((unsigned int*)0x4002551C)=0x1FU;
    *((unsigned int*)0x40025524)=0xFFU;
    *((unsigned int*)0x40025510)=0x11U;
    *((unsigned int*)0x40025520)=0x4C4F434BU;

    *((unsigned int*)0x400FE608)=0x20U;
    *((unsigned int*)0x40025400)=0x0EU;
    *((unsigned int*)0x4002551C)=0x1FU;
    *((unsigned int*)0x40025524)=0xFFU;
    *((unsigned int*)0x40025510)=0x11U;
    *((unsigned int*)0x40025520)=0x4C4F434BU;

    int Values[] = {0, 30, 60, 100};
    int counter = 1;
    
    PWM1_2_CMPA_R = 160*Values[0];

    int buttonPressed_Switch = 0;
    while(1)
    {
        if (buttonPressed_Switch == 0 && LeftButton == PressedCode1)
        {
              buttonPressed_Switch = 1;
              PWM1_2_CMPA_R = 160*Values[counter];
              counter = (counter + 1)%(sizeof(Values)/sizeof(Values[0]));
        }
        else if (buttonPressed_Switch == 1 && LeftButton != PressedCode1)
        {
            buttonPressed_Switch = 0;
        }
    }
    
  /*
  int pw = 0;

    SYSCTL->RCGCPWM |= 0x02;        // enable clock to PWM1
    SYSCTL->RCGCGPIO |= 0x20;       // enable clock to GPIOF
    SYSCTL->RCGCGPIO |= 0x02;       // enable clock to GPIOB

    SYSCTL->RCC &= ~0x00100000;     // use system clock for PWM
    PWM1->INVERT |= 0x80;           // positive pulse
    PWM1->_3_CTL = 0;               // disable PWM1_3 during configuration
    PWM1->_3_GENB = 0x0000080C;     // output high when load and low when match
    PWM1->_3_LOAD = 3999;           // 4 kHz
    PWM1->_3_CTL = 1;               // enable PWM1_3
    PWM1->ENABLE |= 0x80;           // enable PWM1

    GPIOF->DIR |= 0x08;             // set PORTF 3 pins as output (LED) pin
    GPIOF->DEN |= 0x08;             // set PORTF 3 pins as digital pins
    GPIOF->AFSEL |= 0x08;           // enable alternate function
    GPIOF->PCTL &= ~0x0000F000;     // clear PORTF 3 alternate function
    GPIOF->PCTL |= 0x00005000;      // set PORTF 3 alternate funtion to PWM

    GPIOB->DEN |= 0x0C;             // PORTB 3 as digital pins
    GPIOB->DIR |= 0x0C;             // set PORTB 3 as output
    GPIOB->DATA |= 0x08;            // enable PORTB 3

    while(1)
    {
        for (pw = 100; pw < 3999; pw += 20)
        {
            PWM1->_3_CMPB = pw;
            delayMs(50);
        }
        for (pw = 3900; pw >100; pw -= 20)
        {
            PWM1->_3_CMPB = pw;
            delayMs(50);
        }
        GPIOB->DATA &= ~0x08;
        GPIOB->DATA |= 0x04;
        for (pw = 100; pw < 3999; pw += 20)
        {
            PWM1->_3_CMPB = pw;
            delayMs(50);
        }
        for (pw = 3900; pw >100; pw -= 20)
        {
            PWM1->_3_CMPB = pw;
            delayMs(50);
        }
        GPIOB->DATA &= ~0x04;
        GPIOB->DATA |= 0x08;
    }
    */
}
