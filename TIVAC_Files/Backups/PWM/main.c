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

void delayMs(int n); 

int main(void)
{ 
  /*
  // Q1
  // PWM
  int x = 15999;
  // Enable Peripheral Clocks  
  SYSCTL_RCGCPWM_R |= 2;       // enable clock to PWM1  
  SYSCTL_RCGCGPIO_R |= 0x20;   // enable clock to PORTF  
  SYSCTL_RCC_R &= ~0x00100000; // no pre-divide for PWM clock
  // Enable port PF2 for PWM1 M1PWM7  
  GPIO_PORTF_AFSEL_R = 0x0E;   // PF2 uses alternate function  
  GPIO_PORTF_PCTL_R |= 0x000005550; 
  GPIO_PORTF_DEN_R = 0x02;     // pin digital 
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
  
  int Colors[] = {RED, GREEN, BLUE};
  int ColorIndex = 0;
  
  for(;;) 
  { 
    GPIO_PORTF_DEN_R = Colors[ColorIndex];       // pin digital 
    ColorIndex = (ColorIndex + 1) % (sizeof(Colors) / sizeof(Colors[0]));
    x = x - 50; 
    if (x <= 0) 
      for(;;)
      { 
        x = x + 50; 
        if (x>=15999) 
          break; 
        PWM1_2_CMPA_R = x; 
        PWM1_3_CMPA_R = x; 
        delayMs(5);
      } 
    PWM1_2_CMPA_R = x; 
    PWM1_3_CMPA_R = x; 
    delayMs(5);
  }
  */
  // Q2
  // ADC
  volatile int result;
  *((volatile unsigned int *)0x400FE608)=(1<<4)|(1<<5); // clock gating portE 
  *((volatile unsigned int *)0x400FE638)|=1;            // analog clock gating  
  *((volatile unsigned int *)0x40025400)=0xFFU;         // portF direction register 
  *((volatile unsigned int *)0x4002551C)=0xFFU;         // portF digital function register 
  GPIO_PORTE_AFSEL_R |= 8;                              // enable alternate function  
  GPIO_PORTE_DIR_R &= ~8;                               // disable digital function  
  GPIO_PORTE_AMSEL_R |= 8;                              // enable analog function  
  ADC0_ACTSS_R &=  ~8;                                  // disable SS3 during configuration  
  ADC0_EMUX_R &= ~0xF000;                               // software trigger conversion  
  ADC0_SSMUX3_R = 0;                                    // get input from channel 0  
  ADC0_SSCTL3_R |= 6;                                   // take one sample at a time, set flag at 1st sample  
  ADC0_ACTSS_R |= 8;                                    // enable ADC0 sequencer 3 
  while(1)    
  { 
    ADC0_PSSI_R |= 8;                                   // start a conversion sequence 3  
    if((ADC0_RIS_R & 8) == 0)                           // wait for conversion complete  
    { 
      result = ADC0_SSFIFO3_R;                          // read conversion result  
      if(result > 4000)
        *((volatile unsigned int *)0x400253FC) = (1<<1);
      else if(result < 4000 && result > 2000)
        *((volatile unsigned int *)0x400253FC) = (1<<2);
      else
        *((volatile unsigned int *)0x400253FC) = (1<<3);
    }  
    ADC0_ISC_R = 8;                                     // clear completion flag  
  }
} 

// delay n milliseconds (16 MHz CPU clock)  
void delayMs(int n)
{ 
  int i, j; 
  for(i = 0 ; i < n; i++) 
    for(j = 0; j < 3180; j++) 
    {}  // do nothing for 1 ms  
}

