//#include<LM4F120H5QR.h>
//#include<tm4c123gh6pm.h>
#include<stdint.h>
#include<tm4c123gh6pm.h>

#include<uartstdio.h>
#include<uartstdio.c>
#include<driverlib/uart.h>
#include<driverlib/uart.c>
#include<driverlib/gpio.h>
#include<driverlib/gpio.c>
#include<driverlib/sysctl.h>
#include<driverlib/sysctl.c>


// UART Defines
#define GPIO_PA0_U0RX           0x00000001
#define GPIO_PA1_U0TX           0x00000401

// Color Defines
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

// UART Defines
#define ROM_APITABLE            ((uint32_t *)0x01000010)
#define ROM_UARTTABLE           ((uint32_t *)(ROM_APITABLE[1]))
#define ROM_SYSCTLTABLE         ((uint32_t *)(ROM_APITABLE[13]))

#define ROM_UARTConfigSetExpClk                                               \
        ((void (*)(uint32_t ui32Base,                                         \
                   uint32_t ui32UARTClk,                                      \
                   uint32_t ui32Baud,                                         \
                   uint32_t ui32Config))ROM_UARTTABLE[5])
#define ROM_SysCtlClockGet                                                    \
        ((uint32_t (*)(void))ROM_SYSCTLTABLE[24])
	  
// UART Functions
char UART_SendQuestion(char ques)
{
    UARTCharPut(UART0_BASE, ques);
    char ans = UARTCharGet(UART0_BASE);
    return ans;

    //UARTCharPutNonBlocking(UART0_BASE, 'a');
    //c = UARTCharGetNonBlocking(UART0_BASE);
}

char UART_RecvQuestion()
{
    char ques = UARTCharGet(UART0_BASE);
    return ques;

    //UARTCharPutNonBlocking(UART0_BASE, 'a');
    //c = UARTCharGetNonBlocking(UART0_BASE);
}

void UART_SendAnswer(char ans)
{
    UARTCharPut(UART0_BASE, ans);

    //UARTCharPutNonBlocking(UART0_BASE, 'a');
    //c = UARTCharGetNonBlocking(UART0_BASE);
}

// Questions Functions
int QuestionsColors[] = {RED, YELLOW, GREEN, BLUE, CYAN};
char QEncodeValue[] = {(char)0x30, (char)0x31, (char)0x32, (char)0x33, (char)0x34};
int AnswersColors[] = {WHITE, PURPLE, BLACK};
char AEncodeValue[] = {(char)0x35, (char)0x36, (char)0x37};

void QController()
{
    *((unsigned int*)0x400FE608)=0x20U;
    *((unsigned int*)0x40025400)=0x0EU;
    *((unsigned int*)0x4002551C)=0x1FU;
    *((unsigned int*)0x40025524)=0xFFU;
    *((unsigned int*)0x40025510)=0x11U;
    *((unsigned int*)0x40025520)=0x4C4F434BU;

    int counter = 1;
    
    *((unsigned int*)0x40025038) = QuestionsColors[0];
    int buttonPressed_Switch = 0;
    int buttonPressed_Select = 0;
    while(1)
    {
        if (buttonPressed_Switch == 0 && LeftButton == PressedCode1)
        {
              buttonPressed_Switch = 1;
              *((unsigned int*)0x40025038) = QuestionsColors[counter];
              counter = (counter + 1)%(sizeof(QuestionsColors)/sizeof(QuestionsColors[0]));
        }
        else if (buttonPressed_Switch == 1 && LeftButton != PressedCode1)
        {
            buttonPressed_Switch = 0;
        }
        if (buttonPressed_Select == 0 && RightButton == PressedCode2)
        {
              buttonPressed_Select = 1;
              // UART Send
	      char ans = UART_SendQuestion(QEncodeValue[counter-1]);
	      for (int i=0;i<(sizeof(AEncodeValue));i++)
	      {
		if (AEncodeValue[i] == ans)
		{
		  *((unsigned int*)0x40025038) = AnswersColors[i];
		  break;
		}
	      }
        }
        else if (buttonPressed_Select == 1 && RightButton != PressedCode2)
        {
            buttonPressed_Select = 0;
        }
    }
}

void AController()
{
    *((unsigned int*)0x400FE608)=0x20U;
    *((unsigned int*)0x40025400)=0x0EU;
    *((unsigned int*)0x4002551C)=0x1FU;
    *((unsigned int*)0x40025524)=0xFFU;
    *((unsigned int*)0x40025510)=0x11U;
    *((unsigned int*)0x40025520)=0x4C4F434BU;

    int counter = 1;
    
    *((unsigned int*)0x40025038) = AnswersColors[0];
    int buttonPressed_Switch = 0;
    int buttonPressed_Select = 0;
    int waitingForQues = 1;
    char curQues;
    while(1)
    {
      if (waitingForQues == 1)
      {
	curQues = UART_RecvQuestion();
	waitingForQues = 0;
      }
      else 
      {
	if (buttonPressed_Switch == 0 && LeftButton == PressedCode1)
        {
              buttonPressed_Switch = 1;
              *((unsigned int*)0x40025038) = AnswersColors[counter];
              counter = (counter + 1)%(sizeof(AnswersColors)/sizeof(AnswersColors[0]));
        }
        else if (buttonPressed_Switch == 1 && LeftButton != PressedCode1)
        {
            buttonPressed_Switch = 0;
        }
        
        if (LeftButton != PressedCode1 && buttonPressed_Select == 0 && RightButton == PressedCode2)
        {
              buttonPressed_Select = 1;
              // UART Send Answer
	      UART_SendAnswer(AEncodeValue[counter-1]);
              waitingForQues = 1;
        }
        else if (buttonPressed_Select == 1 && RightButton != PressedCode2)
        {
            buttonPressed_Select = 0;
        }
      }
    }
}

int main()
{
    // Init UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    ROM_UARTConfigSetExpClk(
			    UART0_BASE, ROM_SysCtlClockGet(), 115200,
			    UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
			    UART_CONFIG_PAR_NONE
      );
  
    *((unsigned int*)0x400FE608)=0x20U;
    *((unsigned int*)0x40025400)=0x0EU;
    *((unsigned int*)0x4002551C)=0x1FU;
    *((unsigned int*)0x40025524)=0xFFU;
    *((unsigned int*)0x40025510)=0x11U;
    *((unsigned int*)0x40025520)=0x4C4F434BU;
    
    *((unsigned int*)0x40025038) = BLUE;
	
    char a = UART_RecvQuestion();
    if (a == 'j')
    {
	*((unsigned int*)0x40025038) = GREEN;
    }
    return 0;
    // Transmitter
    //QController();
    
    // Receiver
    AController();
    
    return 0;
}
