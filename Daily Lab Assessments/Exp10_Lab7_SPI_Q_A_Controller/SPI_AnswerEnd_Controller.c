#include <stdint.h>
#include <stdlib.h>
#include "TM4C123GH6PM.h"

#define BLACK 0x00U
#define RED 0x02U
#define BLUE 0x04U
#define GREEN 0x08U
#define PURPLE 0x06U
#define YELLOW 0x0AU
#define CYAN 0x0CU
#define WHITE 0x0EU

void printChar(char c);
void printString(char * string);
void send_byte(char data);
void uart_ini(void){
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
}
void spi_master_ini(void){
    SYSCTL_RCGCSSI_R|=(1<<2); //selecting SSI2 module
    //SYSCTL_RCGC2_R|=(1<<1); //providing clock to PORTB
    SYSCTL_RCGCGPIO_R |= (1<<1); //enable clock to PORTA
    GPIO_PORTB_AFSEL_R|=(1<<4)|(1<<5)|(1<<6)|(1<<7);//selecting alternative fuctions
    GPIO_PORTB_PCTL_R=0x22220000;//selecting SSI as alternative function
    GPIO_PORTB_DEN_R|=(1<<4)|(1<<5)|(1<<6)|(1<<7);//enabling digital mode for PORTB 4,5,6,7
    GPIO_PORTB_PUR_R|=(1<<4)|(1<<5)|(1<<6)|(1<<7);//selecting pull ups for 4,5,6,7
    SSI2_CR1_R=0; //disabling SSI module for settings
    SSI2_CC_R=0; //using main system clock
    SSI2_CPSR_R=64; //selecting divisor 64 for SSI clock
    SSI2_CR0_R=0x7; //freescale mode, 8 bit data, steady clock low
    SSI2_CR1_R|=(1<<1)|(1<<0); //enabling SSI/LoopBack (Internal SPI Receiver )
}

void printString(char * string) {
    while(*string) {
    	printChar(*(string++));
    }
}
//function for sending each byte of string one by one
void send_str(char *buffer){
    while(*buffer!=0){
	send_byte(*buffer);
	buffer++;
    }
}
void send_byte(char data){
    while((SSI2_SR_R&(1<<0))==0); //waiting for transmission to be done
    SSI2_DR_R=data; //putting the byte to send from SSI
}
char rec_char(void) {
    char c;
    while((SSI2_SR_R&(1<<2))==0); //waiting for transmission to be done
    c=SSI2_DR_R; //putting the byte to send from SSI
    return c;
}
char* rec_str(char delimiter) {
    int stringSize = 0;
    char* string = (char*)calloc(15,sizeof(char));
    char c = rec_char();
    printChar(c);
    while(c!=delimiter) {
	*(string+stringSize) = c; // put the new character at the end of the array
	stringSize++;
	c = rec_char();
	printChar(c); // display the character the user typed
    }
    return string;
}
void printChar(char c) {
    while((UART0_FR_R & (1<<5)) != 0);
    UART0_DR_R = c;
}

// Data
// char* Questions[] = {"Are you there in your office?", "Are you happy?", "Are you hungry, want to have lunch?", "Are you thirsty, want to meet for a beverage?", "Shall I come to your office to talk?"};
// int QuestionColors[] = {RED, YELLOW, GREEN, BLUE, CYAN};

char* Answers[] = {"Yes", "Maybe", "No"};
int AnswerColors[] = {WHITE, PURPLE, BLACK};

int main(){
    spi_master_ini(); //initializing controller as master
    uart_ini();
    send_str("Hello SPI\r");//sending string
    while(1){
	char* string = rec_str('\r');
	printString("\n\r");
	printString("You typed: ");
	printString(string);
	printString("\n\r");
	free(string);
    }
    return 0;
}