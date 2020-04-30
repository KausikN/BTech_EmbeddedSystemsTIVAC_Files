#define TARGET_IS_BLIZZARD_RA1
#include <stdint.h>
#include "stdlib.h"
#include <stdbool.h>
//#include "inc/hw_can.h"
//#include "inc/hw_ints.h"
//#include "driverlib/fpu.h"
//#include "driverlib/can.h"
//#include "grlib/grlib.h"
//#include "drivers/cfal96x64x16.h"
//#include "utils/uartstdio.h"
//#include "driverlib/interrupt.h"

//#define TARGET_IS_BLIZZARD_RA1
#include <stdio.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
//#include "driverlib/rom.h"
//#include "driverlib/uart.h"
//#include "driverlib/adc.h"
//#include "utils/uartstdio.h"
//#include "driverlib/pin_map.h"
//#include <inttypes.h> //se utiliza para imprimir los valores uint32_t


#include "math.h"


//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line)
{

}
#endif
//Declarations

#define LCD_DATA GPIO_PORTB_BASE //LCD data port to PORTb
#define ctrl PORTE //LCD control port to PORTE
#define rs GPIO_PIN_1 //register select signal to RE0

#define en GPIO_PIN_2 //enable signal to RE2

//Function Prototypes
void init_LCD(void); //Function to initialise the LCD
void LCD_command(unsigned char cmd); //Function to pass command to the LCD
void LCD_data(unsigned char data); //Function to write character to the LCD
void LCD_write_string(char *str);//Function to write string to the LCD
void msdelay (unsigned int time); //Function to generate delay


// DEFINICION DE PUERTOS
#define perifericoData SYSCTL_PERIPH_GPIOB
#define writeData GPIO_PORTB_BASE
#define B0 GPIO_PIN_0
#define B1 GPIO_PIN_1
#define B2 GPIO_PIN_2
#define B3 GPIO_PIN_3
#define B4 GPIO_PIN_4
#define B5 GPIO_PIN_5
#define B6 GPIO_PIN_6
#define B7 GPIO_PIN_7
#define dataPins B0|B1|B2|B3|B4|B5|B6|B7

#define perifericoControl SYSCTL_PERIPH_GPIOD
#define writeControl GPIO_PORTD_BASE
#define E GPIO_PIN_0
#define RS GPIO_PIN_1
#define controlPins E|RS

#define perifericoLed SYSCTL_PERIPH_GPIOF
#define writeLed GPIO_PORTF_BASE
#define led1 GPIO_PIN_1
#define led2 GPIO_PIN_2
#define led3 GPIO_PIN_3
#define leds led3|led2|led1
#define cian 0x0C
#define azul 0x04
#define rojo 0x02
#define verde 0x08
#define off 0x00


int delayms (int tiempo){
    int resultado = 1000 * (tiempo / (0.0000625*1000));
    return resultado;
}
int delayus (int tiempo){
    int resultado = 1000 * (tiempo / (0.0625*1000));
    return resultado;
}

//Start of Main Program
int main(void)
{
    char var1[] = "I";//Declare message to be displayed

    /*Set the clocking to directly run from the crystal at 16MHz*/
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    /* Set the clock for the GPIO Port B y D */
    SysCtlPeripheralEnable(perifericoControl);
    SysCtlPeripheralEnable(perifericoData);
    SysCtlPeripheralEnable(perifericoLed);
    /* Set the type of the GPIO Pin */
    SysCtlDelay(8000000);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, B0|B1|B2|B3|B4|B5|B6|B7);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,E|RS);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,led3|led2|led1);
    SysCtlDelay(8000000);


    init_LCD(); // call function to initialise of LCD
    SysCtlDelay(8000000);


    /*
    LCD_command(0xC0); // initiate cursor to second line 0b1100 0000
    LCD_write_string(var2);//Display message on second line
    */
    while (1){ //Loop here
        LCD_write_string(var1); //Display message on first line
        GPIOPinWrite(writeLed, led3|led2|led1 ,azul);//LED AZUL

        SysCtlDelay(delayms(1000));
        GPIOPinWrite(writeLed, led3|led2|led1 ,off);//LED AZUL
    }
} //End of Main

//Function Definitions
void msdelay (unsigned int time) //Function to generate delay
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
    for (j = 0; j < 275; j++);//Calibrated for a 1 ms delay in MPLAB
}

void init_LCD(void) // Function to initialise the LCD
{
    //16MHz ---- 62.5ns
    SysCtlDelay(8000000); // 550000 ciclos
    GPIOPinWrite(writeControl, RS | E, 0x00); //COLOCO RS Y E en 0 por las dudas Rs = 0 para instrucciones E = 1 cuando se comienza a escribir

    //clear display 0b 0 0 0 0 0 0 0 1
    //return home 0b 0 0 0 0 0 0 1 x
    //entry mode set 0b 0 0 0 0 0 1 I/D S I/D = 1 mueve el cursor a la derecha S = 1 mueve el display
    //display on/off 0b 0 0 0 0 1 D C B D display C cursor B blink
    //cursor or display shift 0b 0 0 0 1 S/C R/L x x S/C = 0 mueve cursor R/L = 1 derecha
    //function set 0b 0 0 1 DL N F x x DL = 1 - 8bits mode N = 1 - 2line display F = 1 - 5x11dots

    // FIRST 

    GPIOPinWrite(writeLed, leds ,rojo);
    LCD_command(0x3F);
    GPIOPinWrite(writeLed, leds ,off);
    SysCtlDelay(delayms(5));

    // SECOND

    GPIOPinWrite(writeLed, leds ,rojo);
    LCD_command(0x3F);
    GPIOPinWrite(writeLed, leds ,off);
    SysCtlDelay(delayus(110));

    // THIRD

    GPIOPinWrite(writeLed, leds ,rojo);
    LCD_command(0x3F);
    GPIOPinWrite(writeLed, leds ,off);
    SysCtlDelay(delayus(110));

    // FORTH

    GPIOPinWrite(writeLed, leds ,rojo);
    LCD_command(0x30);
    GPIOPinWrite(writeLed, leds ,off);
    SysCtlDelay(delayms(2));

    // FIVETH

    GPIOPinWrite(writeLed, leds ,rojo);
    LCD_command(0x08);
    GPIOPinWrite(writeLed, leds ,off);
    SysCtlDelay(delayms(2));

    //SIXTH

    GPIOPinWrite(writeLed, leds ,rojo);
    LCD_command(0x01);
    GPIOPinWrite(writeLed, leds ,off);
    SysCtlDelay(delayms(2));

    //SEVENTH

    GPIOPinWrite(writeLed, leds ,rojo);
    LCD_command(0x06);
    GPIOPinWrite(writeLed, leds ,off);
    SysCtlDelay(delayms(2));

    //EIGHTH  display on cursor on blink on

    GPIOPinWrite(writeLed, leds ,rojo);
    LCD_command(0x0F);
    GPIOPinWrite(writeLed, leds ,off);
    SysCtlDelay(delayms(2));

}

void LCD_command(unsigned char cmd) //Function to pass command to the LCD
{


    GPIOPinWrite(writeData, B7|B6|B5|B4|B3|B2|B1|B0,cmd);

    GPIOPinWrite(writeControl, RS | E, 0x00);
    SysCtlDelay(delayus(3));

    GPIOPinWrite(writeControl, RS | E, 0x01);//Generate High to low pulse on EN
    SysCtlDelay(delayus(3));
    GPIOPinWrite(writeControl, RS | E, 0x00);
    SysCtlDelay(delayus(110));
}

void LCD_data(unsigned char data)//Function to write data to the LCD
{
    /* Writing Command on Port B*///Send data on LCD data bus
    GPIOPinWrite(writeControl, RS | E, 0x02);//RS = 1 since DATA to LCD
    GPIOPinWrite(writeData, dataPins ,data);
    GPIOPinWrite(writeLed, led3|led2|led1 ,verde);//LED VERDE

    SysCtlDelay(delayus(3));


    GPIOPinWrite(writeControl, RS | E, 0x03);//RS = 1 since DATA to LCD
    SysCtlDelay(delayus(3));

    GPIOPinWrite(writeControl, RS | E,0x02);
    GPIOPinWrite(writeLed, led3|led2|led1 ,0x00);//LED
    SysCtlDelay(delayus(110));
}
//Function to write string to LCD
void LCD_write_string(char *str)
{
    int i = 0;
    while (str[i] != 0)
    {
        LCD_data(str[i]); // sending data on LCD byte by byte
        SysCtlDelay(8000000);
        i++;
    }
}