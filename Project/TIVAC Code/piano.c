#include "piano.h"
#include "tm4c123gh6pm.h"

// store the index value of the corresponding input
unsigned short freq_index;

/**
 * Initializes piano key inputs.
 */
void InitPiano(void) {
    volatile unsigned long delay;

    SYSCTL_RCGC2_R |= 0x10;          // unlock port E clock
    delay = SYSCTL_RCGC2_R;          // allow time for clock to start
    GPIO_PORTE_LOCK_R |= 0x4C4F434B; // unlock GPIO Port E
    GPIO_PORTE_CR_R |= 0x0F;         // allow change to PE3-PE0
    GPIO_PORTE_AMSEL_R &= ~0x0F;     // disable analog function on PE3-PE0
    GPIO_PORTE_PCTL_R = 0x00;        // clear PCTL register on PE3-PE0
    GPIO_PORTE_DIR_R &= ~0x0F;       // PE3-PE0 inputs
    GPIO_PORTE_AFSEL_R &= ~0x0F;     // disable alternate function on PE3-PE0
    GPIO_PORTE_PUR_R &= ~0x0F;       // disable pull-up resistors on PE3-PE0
    GPIO_PORTE_DEN_R |= 0x0F;        // enable digital pins on PE3-PE0

    GPIO_PORTF_LOCK_R |= 0x4C4F434B; // unlock GPIO Port F
    GPIO_PORTF_CR_R |= 0x0F;         // allow change to PF3-PF0
    GPIO_PORTF_AMSEL_R &= ~0x0F;     // disable analog function on PF3-PF0
    GPIO_PORTF_PCTL_R = 0x00;        // clear PCTL register on PF3-PF0
    GPIO_PORTF_DIR_R &= ~0x0F;       // PF3-PF0 inputs
    GPIO_PORTF_AFSEL_R &= ~0x0F;     // disable alternate function on PF3-PF0
    GPIO_PORTF_PUR_R &= ~0x0F;       // disable pull-up resistors on PF3-PF0
    GPIO_PORTF_DEN_R |= 0x0F;        // enable digital pins on PF3-PF0

}

/**
 * Reads the input from PE3-PE0 and PF3-PF0.
 *
 * @notes    Returns to freq_index with values from 0 to 8 depending on key pressed
 *            
 *            0 if key 0 = note C = PE0 is pressed
 *            1 if key 1 = note D = PE1 is pressed
 *            2 if key 2 = note E = PE2 is pressed
 *            3 if key 3 = note F = PE3 is pressed
              4 if key 4 = note G = PF0 is pressed
 *            5 if key 5 = note A = PF1 is pressed
 *            6 if key 6 = note B = PF2 is pressed
 *            7 if key 7 = note CH = PF3 is pressed
 */

void PianoIn(void) {
    if (GPIO_PORTE_DATA_R == 0x08) {        // C Note,
        freq_index = 0;                     // store "Key 0 is pressed"
    } else if (GPIO_PORTE_DATA_R == 0x04) { // D Note,
        freq_index = 1;                     // store "Key 1 is pressed"
    } else if (GPIO_PORTE_DATA_R == 0x02) { // E Note,
        freq_index = 2;                     // store "Key 2 is pressed"
    } else if (GPIO_PORTE_DATA_R == 0x01) { // F Note,
        freq_index = 3;                     // store "Key 3 is pressed"
    } else if (GPIO_PORTF_DATA_R == 0x08){  // G Note,  
        freq_index = 4;                     // store "Key 4 is pressed" 
    }
    else if (GPIO_PORTF_DATA_R == 0x04) {  // A Note,
        freq_index = 5;                     // store "Key 5 is pressed"
    } else if (GPIO_PORTF_DATA_R == 0x02) { // B Note,
        freq_index = 6;                     // store "Key 6 is pressed"
    } else if (GPIO_PORTF_DATA_R == 0x01) { // CH Note,
        freq_index = 7;                     // store "Key 7 is pressed"
    } else {                                // otherwise,
        freq_index = 8;                     // store "No key is pressed"
    }
}