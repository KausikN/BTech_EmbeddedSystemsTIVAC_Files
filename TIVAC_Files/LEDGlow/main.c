//#include<LM4F120H5QR.h>
//#include<tm4c123gh6pm.h>
#include<stdio.h>
#include<time.h>

#define BLACK 0x00U
#define RED 0x02U
#define BLUE 0x04U
#define GREEN 0x08U
#define PURPLE 0x06U
#define YELLOW 0x0AU
#define CYAN 0x0CU
#define WHITE 0x0EU
#define PressedCode 0x00U
#define LeftButton *((unsigned int*)0x40025040)
#define RightButton *((unsigned int*)0x40025004)

int main()
{
  
  *((unsigned int*)0x400FE608)=0x20U;
  *((unsigned int*)0x40025400)=0x0EU;
  *((unsigned int*)0x4002551C)=0x1FU;
  *((unsigned int*)0x40025524)=0xFFU;
  *((unsigned int*)0x40025510)=0x11U;
  *((unsigned int*)0x40025520)=0x4C4F434BU;

// Q1 - ButtonPress Color Change
  int counter = 1;
  int Colors[] = {RED, PURPLE, BLUE, CYAN, GREEN, YELLOW};
  *((unsigned int*)0x40025038) = Colors[0];
  int buttonPressed = 0;
  while(1)
  {
    if (buttonPressed == 0 && *((unsigned int*)0x40025040) == PressedCode)
    {
      buttonPressed = 1;
      *((unsigned int*)0x40025038) = Colors[counter];
      counter = (counter + 1)%(sizeof(Colors)/sizeof(Colors[0]));
    }
    else if (buttonPressed == 1 && *((unsigned int*)0x40025040) != PressedCode)
    {
      buttonPressed = 0;
    }
  }
  return 0;
}
