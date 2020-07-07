// Imports
//#include<LM4F120H5QR.h>
//#include<tm4c123gh6pm.h>
//#include<stdio.h>
#include<time.h>

#define PressedCode 0x00U

// Params
int ButtonPins[] = {0x40025040, 0x40025004};
int ButtonFrequencies[] = {0x00U, 0xF0U};

// Main Functions
void delay(float second)
{
  float milsec = 10 * second;
  clock_t startTime = clock();
  while(clock() < (startTime + milsec));
}

int main()
{
  // Piano using DAC Project

  // DAC Init
  *((volatile unsigned int *)0x400FE608)=(0x04U); // Clock Gating Enable
  *((volatile unsigned int *)0x40006400)=(0xF0U); // Data Direction
  *((volatile unsigned int *)0x4000651C)=(0xF0U); // Digital Enable

  // Buttons Init
  *((unsigned int*)0x400FE608)=0x20U;
  *((unsigned int*)0x40025400)=0x0EU;
  *((unsigned int*)0x4002551C)=0x1FU;
  *((unsigned int*)0x40025524)=0xFFU;
  *((unsigned int*)0x40025510)=0x11U;
  *((unsigned int*)0x40025520)=0x4C4F434BU;


  while(1)
  {
  	for (int i=0;i<8;i++)
  	{
  	  if (*((unsigned int*)ButtonPins[i]) == PressedCode)
      {
      	*((volatile unsigned int *)(0x400063C0)) = ButtonFrequencies[i];
      	delay(5);
        break;
      }
  	}
  }

  return 0;
}