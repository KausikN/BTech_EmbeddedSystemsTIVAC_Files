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

  // Q2 - Multi Button Color
  // Initlal Color
  *((unsigned int*)0x40025038) = BLACK;
  int BothPressed = GREEN;
  int LeftPressed = RED;
  int RightPressed = BLUE;
  int NonePressed = BLACK;
  
  while(1)
  {
    if (LeftButton == PressedCode &&  RightButton == PressedCode)
    {
      *((unsigned int*)0x40025038) = BothPressed;
    }
    else if (LeftButton == PressedCode && RightButton != PressedCode)
    {
      *((unsigned int*)0x40025038) = LeftPressed;
    }
    else if (LeftButton != PressedCode && RightButton == PressedCode)
    {
      *((unsigned int*)0x40025038) = RightPressed;
    }
    else 
    {
      *((unsigned int*)0x40025038) = NonePressed;
    }
  }
  
  return 0;
}
