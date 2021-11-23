#include <string.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include<string.h>

char readChar(void);
void printChar(char c);
void printString(char * string);
char* readString(char delimiter);

void printString(char * string) //print string function send char by char to FIFO txbuffert o comp
{
    while(*string)
    {
    	printChar(*(string++));
    }
}
void printChar(char c) // each char stored in TX FIFO buffer and transfer it computer
{
    while((UART0_FR_R & (1<<5)) != 0);
    UART0_DR_R = c;
}
char readChar(void) // read computer char by char to RX FIFO buffer
{
    char c;
    while((UART0_FR_R & (1<<4)) != 0);
    c = UART0_DR_R;
    return c;
} 
char* readString(char delimiter)
{
    int stringSize = 0;
    char* string = (char*)calloc(10,sizeof(char));
    char c = readChar();
    printChar(c);
    while(c!=delimiter)
    {
	*(string+stringSize) = c;
	stringSize++;
	c = readChar();
	printChar(c); // display the character the user typed
    }
    return string;
}

void UART_Setup()
{
    SYSCTL_RCGCUART_R|= (1<<0); //Enable the UART0 module
    SYSCTL_RCGCGPIO_R |= (1<<0); //enable clock to PORTA
    GPIO_PORTA_AFSEL_R=(1<<1)|(1<<0); //Enable PA0 and PA1 As Alternate Function PIN
    GPIO_PORTA_PCTL_R|=0x00000001|0x00000010; // make PA0 PA1 UART output pin
    GPIO_PORTA_DEN_R|=(1<<0)|(1<<1); //Enable digital on PA0 PA1
    UART0_CTL_R&= ~(1<<0); //Disable the UART by clearing the UARTEN
    UART0_IBRD_R=104; // integer portion of the BRD
    UART0_FBRD_R=11; //fractional portion of the BRD
    UART0_LCRH_R=(0x3<<5)|(1<<4); // 8-bit, no parity, 1-stop bit
    UART0_CTL_R = (1<<0)|(1<<8)|(1<<9); //Enable the UART by setting the UARTEN bit
    SYSCTL_RCGCGPIO_R |= 0x20; /* enable clock to PORTF */
    GPIO_PORTF_DEN_R=(1<<1)|(1<<2)|(1<<3); //Enable digital on PF1 PF2 PF3
    GPIO_PORTF_DIR_R=(1<<1)|(1<<2)|(1<<3); //Enable digital output on PF1 PF2 PF3
    GPIO_PORTF_DATA_R = ~((1<<1)|(1<<2)|(1<<3)); //Disable digital output on PF1 PF2 PF3 
}

char UART_SendQuestion(char ques[])
{
    printString(ques);
    char ans[] = readString(';');
    return ans;
}

char UART_RecvQuestion()
{
    char ques[] = readString(';');
    return ques;
}

void UART_SendAnswer(char ans[])
{
    printString(ans);
}

// Questions Functions
char* Questions[] = {"Are you there in your office?", "Are you happy?", "Are you hungry, want to have lunch?", "Are you thirsty, want to meet for a beverage?", "Shall I come to your office to talk?"};
int QuestionColors[] = {RED, YELLOW, GREEN, BLUE, CYAN};

char* Answers[] = {"Yes", "Maybe", "No"};
int AnswerColors[] = {WHITE, PURPLE, BLACK};

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
	      char ans = UART_SendQuestion(Questions[counter-1]);
	      for (int i=0;i<(sizeof(AEncodeValue));i++)
	      {
		if (strcmp(Answers[i], ans) == 0)
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
	      UART_SendAnswer(Answers[counter-1]);
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
    UART_Setup();
    /*
    while(1)
    {
	printString("Type something and press enter: ");
	char* string = readString('\r');
	printString("\n\r");
	printString("You typed: ");
	printString(string);
	printString("\n\r");
	if(*string=='r')
	    GPIO_PORTF_DATA_R = (1<<1)|(1<<2)|(1<<3);
	free(string);
    }
*/
    QController();
    //AController();
    return 0;
}
