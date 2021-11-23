//#include<LM4F120H5QR.h>
//#include<tm4c123gh6pm.h>
//#include<stdio.h>
#include<time.h>

void delay(float second)
{
  float milsec = 10 * second;
  clock_t startTime = clock();
  while(clock() < (startTime + milsec));
}

int main()
{
  *((volatile unsigned int *)0x400FE608)=(0x04U); // Clock Gating Enable
  *((volatile unsigned int *)0x40006400)=(0xF0U); // Data Direction
  *((volatile unsigned int *)0x4000651C)=(0xF0U); // Digital Enable
  while(1) 
  {  
    

    *((volatile unsigned int *)(0x400063C0))=(0x00U);  delay(5);// 0000
    *((volatile unsigned int *)(0x400063C0))=(0x10U);  delay(5);// 0001
    *((volatile unsigned int *)(0x400063C0))=(0x20U);  delay(5);// 0010
    *((volatile unsigned int *)(0x400063C0))=(0x30U);  delay(5);// 0011
    
    *((volatile unsigned int *)(0x400063C0))=(0x40U);  delay(5);// 0100
    *((volatile unsigned int *)(0x400063C0))=(0x50U);  delay(5);// 0101
    *((volatile unsigned int *)(0x400063C0))=(0x60U);  delay(5);// 0110
    *((volatile unsigned int *)(0x400063C0))=(0x70U);  delay(5);// 0111
    
    *((volatile unsigned int *)(0x400063C0))=(0x80U);  delay(5);// 1000
    *((volatile unsigned int *)(0x400063C0))=(0x90U);  delay(5);// 1001
    *((volatile unsigned int *)(0x400063C0))=(0xA0U);  delay(5);// 1010
    *((volatile unsigned int *)(0x400063C0))=(0xB0U);  delay(5);// 1011
    
    *((volatile unsigned int *)(0x400063C0))=(0xC0U);  delay(5);// 1100
    *((volatile unsigned int *)(0x400063C0))=(0xD0U);  delay(5);// 1101
    *((volatile unsigned int *)(0x400063C0))=(0xE0U);  delay(5);// 1110
    *((volatile unsigned int *)(0x400063C0))=(0xF0U);  delay(5);// 1111
    
    /*
    *((volatile unsigned int *)(0x40006040))=(0x10U); delay(1); // C4
    *((volatile unsigned int *)(0x40006080))=(0x20U); delay(1); // C5
    *((volatile unsigned int *)(0x40006100))=(0x30U); delay(1); // C6
    *((volatile unsigned int *)(0x40006200))=(0x40U); delay(1); // C7  
    */
  } 
  
  return 0;
}