//#include<LM4F120H5QR.h>
//#include<tm4c123gh6pm.h>
//#include<stdio.h>
#include<time.h>

#define BLACK 0x00U
#define RED 0x02U
#define BLUE 0x04U
#define GREEN 0x08U
#define PURPLE 0x06U
#define YELLOW 0x0AU
#define CYAN 0x0CU
#define WHITE 0x0EU

void delay(int second)
{
  float milsec = 50 * second;
  clock_t startTime = clock();
  while(clock() < (startTime + milsec));
}

int main()
{
  
  *((unsigned int*)0x400FE608)=0x20U;
  *((unsigned int*)0x40025400)=0x0EU;
  *((unsigned int*)0x4002551C)=0x0EU;
  while(1){
    *((unsigned int*)0x400253FC)=GREEN;
    delay(5);
    *((unsigned int*)0x400253FC)=YELLOW;
    delay(2);
    *((unsigned int*)0x400253FC)=RED;
    delay(8);
  }
  return 0;
}
