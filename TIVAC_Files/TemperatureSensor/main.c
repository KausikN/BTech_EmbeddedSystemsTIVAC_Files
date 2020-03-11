#include<stdint.h> 
#include<stdio.h>
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
  // Temperature Sensor Data Capture
  // Temperature sensor setup
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
    
    // Colors Setup
    *((unsigned int*)0x400FE608)=0x20U;
    *((unsigned int*)0x40025400)=0x0EU;
    *((unsigned int*)0x4002551C)=0x1FU;
    *((unsigned int*)0x40025524)=0xFFU;
    *((unsigned int*)0x40025510)=0x11U;
    *((unsigned int*)0x40025520)=0x4C4F434BU;
    *((unsigned int*)0x40025038) = RED;
    
  
  // Motor Setup
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

    GPIO_PORTF_DIR_R |= 0x08;             // set PORTF 3 pins as output (LED) pin
    GPIO_PORTF_DEN_R |= 0x08;             // set PORTF 3 pins as digital pins
    GPIO_PORTF_AFSEL_R |= 0x08;           // enable alternate function
    GPIO_PORTF_PCTL_R &= ~0x0000F000;     // clear PORTF 3 alternate function
    GPIO_PORTF_PCTL_R |= 0x00005000;      // set PORTF 3 alternate funtion to PWM

    GPIO_PORTB_DEN_R |= 0x0C;             // PORTB 3 as digital pins
    GPIO_PORTB_DIR_R |= 0x0C;             // set PORTB 3 as output
    GPIO_PORTB_DATA_R |= 0x08;            // enable PORTB 3
    
    int Values[] = {0, 25, 50, 75, 100};
    int SpeedMul = (int)(16000 / 100);
    int temperature = 0;
    
    while(1)    
    { 
	ADC0_PSSI_R |= 8;                                   // start a conversion sequence 3  
	if((ADC0_RIS_R & 8) == 0 || 0)                           // wait for conversion complete  
	{ 
	    result = ADC0_SSFIFO3_R;                          // read conversion result
	    temperature = 147 - (int)((247 * ADC0_SSFIFO3_R) / 4096) - 100;
	    //printf("R: %d\n", result);
	    if(temperature > 35)
	    {
	        *((unsigned int*)0x40025038) = RED;
    		PWM1_3_CMPB_R = SpeedMul*Values[4];
	    }
	    	
	    else if(temperature <= 35 && temperature > 30)
	    {
		//*((volatile unsigned int *)0x400253FC) = (1<<2);
		*((unsigned int*)0x40025038) = BLUE;
		PWM1_3_CMPB_R = SpeedMul*Values[3];
	    }
	    else if(temperature <= 30 && temperature > 25)
	    {
		*((unsigned int*)0x40025038) = BLACK;
		PWM1_3_CMPB_R = SpeedMul*Values[2];
	    }
	    else
	    {
		*((unsigned int*)0x40025038) = PURPLE;
		PWM1_3_CMPB_R = SpeedMul*Values[1];
	    }
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